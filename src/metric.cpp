namespace beyond_all_repair
{
struct FuncStat
{
    u32 references = 0;
    u32 branch_count = 0;
};

struct Stats
{
    u32 instr_count[INSTR_TABLE_SIZE] = {0};
    u32 class_count[INSTR_CLASS_SIZE] = {0};
    f64 instr_percentage[INSTR_TABLE_SIZE] = {0.0};
    u32 instr_total = 0;
    std::map<u64,FuncStat> func_info;
};



void print_stats(Stats& stat)
{
    print("instr counts: \n");

    for(u32 i = 0; i < INSTR_TABLE_SIZE; i++)
    {
        if(stat.instr_count[i])
        {
            print("{}: {}: {}\n",i,INSTR_TABLE[i].name,stat.instr_count[i]);
        }
    }    
}


// dump program stats
// NOTE: we recollect references here, so that we can do it on specific sections
b32 scan_stats(Stats& stat,Program& program, u64 offset, u32 size)
{
    const u64 end = offset + size;

    u64 addr = offset;

    while(addr != end)
    {
        u32 op;

        // check read is in range
        if(!read_program(program,addr, &op))
        {
            print("Warning addr 0x{:x} out of range for block\n",addr);
            return false;
        }

        addr += MIPS_INSTR_SIZE;

        const auto opcode = make_opcode(op);  

        // how many instrs are there?
        const u32 idx = instr_idx(opcode,MIPS3);
        stat.instr_count[idx]++;
        stat.instr_total++;

        // count class
        stat.class_count[u32(class_from_opcode(opcode))]++;


        // mark branch targets for xrefs
        auto instr = decode_instr(opcode,MIPS3);

        b32 target_found = false;
        u64 target = 0;

        // Handle branch targets and counting
        // NOTE: this assumes that this is only scanning functions...
        switch(instr->fmt)
        {
            case instr_type::branch_rs: 
            {
                target = branch_addr(addr,opcode.imm);
                target_found = true;
                stat.func_info[offset].branch_count++;
                break;
            }


            case instr_type::branch_rs_rt: 
            {
                target = branch_addr(addr,opcode.imm);
                target_found = true;
                stat.func_info[offset].branch_count++;
                break;
            }

            case instr_type::branch_reg: 
            {
                // ignore ret
                if(opcode.rs != RA)
                {
                    stat.func_info[offset].branch_count++;
                }
                break;
            }

            case instr_type::jump: 
            {
                target = jump_addr(opcode.op,addr);
                target_found = true;
                stat.func_info[offset].branch_count++;
                break;
            }

            default: break;
        }

        // function found increase number of references
        if(target_found && stat.func_info.count(target))
        {
            stat.func_info[target].references++;
        }

    }

    return true;
}

Stats scan_program_stats(Program& program)
{
    Stats stat;

    // extract starting address as dummy for gap calc
    auto it = program.func_lookup.begin();
    Func start = it->second;

    // setup func references to zero!
    for(const auto& [key, func] : program.func_lookup)
    {
        // Ignore externally linked functions for this
        if(!func.external)
        {
            stat.func_info[key] = {};
        }
    }

    // do some passes back over the function to obtain instr counts etc
    for(const auto &[key, func] : program.func_lookup)
    {
        if(func.name == "")
        {
            continue;
        }

        if(func.size != 0 && func.size != SIZE_UNK)
        {
            scan_stats(stat,program,func.addr,func.size);
        }
    }
    
    // calc percentages
    for(u32 i = 0; i < INSTR_TABLE_SIZE; i++)
    {
        stat.instr_percentage[i] = (f64(stat.instr_count[i]) / f64(stat.instr_total)) * f64(100);
    }

    return stat;    
}

}