#include <lib.cpp>
#include <mips.cpp>
#include <elf.cpp>
#include <table_gen.cpp>
#include <metric.cpp>





Program make_program(u64 entry_point,b32 is_be, READ_FUNC func,std::vector<Section>& section)
{
    Program program;
    program.entry_point = entry_point;
    program.section = section;
    program.is_be = is_be;
    program.read_func = func;

    return program;
}


Section make_section(u64 base,u32 size,u8* ptr)
{
    Section section;
    section.base = base;
    section.size = size;
    section.ptr = ptr;

    return section;
}

// defualt section lookup (SLOW!)
b32 lookup_section(Program& program, u64 addr, Section* out)
{
    for(const auto& section : program.section)
    {
        if(section.base <= addr && section.base + section.size  >= addr)
        {
            *out = section;
            return true;
        }
    }

    return false;
}

// Function that is fallen into from another block 
void local_call(Program& program,Func& func,u64 target, u64 pc)
{
    program.block_lookup.erase(target);
    program.func_lookup.erase(target);

    add_block(program,func,target,pc,default_loc_name(target));
}

void add_func(Program& program,u64 target,u64 pc,u32 size,const std::string& name,b32 external)
{
    // if we allready have this is a function dont bother adding it
    if(!program.func_lookup.count(target))
    {
        program.func_target.push_back(target);

        // create function entry
        Func func;
        func.name = name;
        func.addr = target;
        func.size = size;
        func.external = external;

        add_block(program,func,target,pc,func.name);

        program.func_lookup[func.addr] = func; 

        program.func_name_lookup[func.name] = func.addr;
    }

    if(pc != PC_UNK)
    {
        Func& func = program.func_lookup[target];

        func.references.push_back(pc - MIPS_INSTR_SIZE);
    }
}


std::optional<u64> lower_block(Program& program, u64 addr)
{
    auto upper_bound = program.block_lookup.upper_bound(addr);

    if(upper_bound == program.block_lookup.begin())
    {
        return std::nullopt;
    }

    upper_bound--;

    return std::optional<u64>(upper_bound->first);
}

void add_block_internal(Program& program, Func& func, u64 target, const std::string& name, u32 size)
{
    func.block_list.insert(target);

    Block block;

    block.func = func.addr;
    block.addr = target;
    block.name = name;
    block.size = size;

    program.block_lookup[target] = block;    
}

void add_block(Program& program,Func& func, u64 target, u64 pc, const std::string& name)
{
    if(!block_exists(program,target))
    {
        // split block if one allready exists within the target
        auto block_opt = lower_block(program,target);

        if(block_opt)
        {
            auto& block = program.block_lookup[block_opt.value()];

            // This cuts an existing block in half
            // so we need to slice the sizes up!
            if(block.addr + block.size > target)
            {
                //print("split: {} @{:x} {:x} {:x} {:x}\n",func.name,pc,block.addr,target,block.addr + block.size);

                // clip old basic block
                const u32 size_old = block.size;
                block.size = target - block.addr;

                // make new basic block out of the remains
                const u32 new_size = size_old - block.size;

                // NOTE: dont insert for scanning as it is allready parsed 
                // we are only redifining its bounds
                add_block_internal(program,func,target,name,new_size);
            }

            // does not cut an existing block, insert as normal
            else
            {
                add_block_internal(program,func,target,name,0);
                func.branch_target.push_back(target);
            }
        }

        // ordinary insertion
        else
        {
            add_block_internal(program,func,target,name,0);
            func.branch_target.push_back(target);
        }
    }

    if(pc != PC_UNK)
    {
        Block& block = program.block_lookup[target];

        block.references.push_back(pc - MIPS_INSTR_SIZE);
    }
}



// TODO: how do we pull what function an arbitary adress belongs to?
b32 block_exists(Program& program, u64 addr)
{
    return program.block_lookup.count(addr) != 0;
}

b32 func_exists(Program& program, u64 addr)
{
    return program.func_lookup.count(addr) != 0;
}

b32 func_exists(Program& program, std::string name)
{
    return program.func_name_lookup.count(name) != 0;
}

Func& func_from_name(Program& program, std::string name)
{
    const u64 addr = program.func_name_lookup[name];

    return program.func_lookup[addr];
}

void disassemble_func(Program& program, Func& func)
{
    while(func.branch_target.size())
    {
        const u64 addr = func.branch_target.back();
        func.branch_target.pop_back();

        Block& block = program.block_lookup[addr];

        // TODO: add dispatch on this but for now just keep it hard coded
        mark_block_mips(program,func,block);
    }

    // deduce size from our disassembly
    if(func.size == SIZE_UNK)
    {
        func.size = 0;

        for(u64 block_start : func.block_list)
        {
            const auto& block = program.block_lookup[block_start];

            func.size += block.size;
        }
    }
}


void disassemble_program(Program& program)
{
    // grab a new function to disassemble until their and none left
    while(program.func_target.size())
    {
        // grab a new function
        const u64 addr = program.func_target.back();
        program.func_target.pop_back();

        auto& func = program.func_lookup[addr];

        disassemble_func(program,func);
    }
}

void disassemble_console(Program& program,Config& config)
{
    // TODO: this is hard coded for now
    if(!config.linear)
    {
        print_console_mips(program,config);
    }

    else
    {
        print_console_linear_mips(program,config);
    }
}

std::string default_loc_name(u64 addr)
{
    return std::format("LOC_{:08X}",addr);
}

std::string default_func_name(u64 addr)
{
    return std::format("FUN_{:08X}",addr);
}

// TODO: this wont produce marked label names yet!
std::string loc_name(Program& program, u64 addr)
{
    if(block_exists(program,addr))
    {
        auto& block = program.block_lookup[addr];
        return block.name;
    }

    return default_loc_name(addr);
}