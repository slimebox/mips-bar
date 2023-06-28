namespace beyond_all_repair
{
// TODO: add abilitly to disable pseudo ops

// default instr formatter
// overrides defined to handle psuedo instrs
std::string disass_mips_default(Program& program, u64 addr, const Opcode &opcode,const Instr* instr)
{

    switch(instr->fmt)
    {
        case instr_type::imm_signed:
        {
            return std::format("{} {}, {}, {}",instr->name,REG_NAMES[opcode.rt],REG_NAMES[opcode.rs],opcode.imm);
        }

        case instr_type::imm_unsigned:
        {
            return std::format("{} {}, {}, 0x{:04x}",instr->name,REG_NAMES[opcode.rt],REG_NAMES[opcode.rs],u16(opcode.imm));
        }

        case instr_type::imm_rs:
        {
            return std::format("{} {}, 0x{:04x}",instr->name,REG_NAMES[opcode.rs],u16(opcode.imm));
        }

        // NOTE: these are all special cased so just ignore them for now!
        case instr_type::branch_reg:
        {
            assert(false);
        }

        // NOTE: these have no defualt handling they all require special decoding for size and pos
        case instr_type::bit_op:
        {
            assert(false);
        }

        case instr_type::branch_rs_rt:
        {
            const u64 target = branch_addr(addr,opcode.imm);
            return std::format("{} {}, {}, {}",instr->name,REG_NAMES[opcode.rs],REG_NAMES[opcode.rt],loc_name(program,target));
        }

        case instr_type::branch_rs:
        {
            const u64 target = branch_addr(addr,opcode.imm);
            return std::format("{} {}, {}",instr->name,REG_NAMES[opcode.rs],loc_name(program,target));            
        }

        case instr_type::jump:
        {
            const u64 target = jump_addr(addr,opcode.op);

            return std::format("{} {}",instr->name,loc_name(program,target));
        }

        case instr_type::store:
        {
            return std::format("{} {}, {}({})",instr->name,REG_NAMES[opcode.rt],opcode.imm,REG_NAMES[opcode.rs]);
        }

        case instr_type::store_float:
        {
            return std::format("{} $f{}, {}({})",instr->name,get_ft(opcode),opcode.imm,REG_NAMES[opcode.rs]);
        }

        // TODO: add options to fmt custom register names
        // by setting a system...
        case instr_type::store_cop2:
        {
            return std::format("{} {}, {}({})",instr->name,REG_NAMES[opcode.rt],opcode.imm,REG_NAMES[opcode.rs]);
        }


        case instr_type::load:
        {
            return std::format("{} {}, {}({})",instr->name,REG_NAMES[opcode.rt],u16(opcode.imm),REG_NAMES[opcode.rs]);
        }

        case instr_type::load_float:
        {
            return std::format("{} $f{}, {}({})",instr->name,get_ft(opcode),opcode.imm,REG_NAMES[opcode.rs]);
        }

        // TODO: add options to fmt custom register names
        // by setting a system...
        case instr_type::load_cop2:
        {
            return std::format("{} {}, {}({})",instr->name,REG_NAMES[opcode.rt],opcode.imm,REG_NAMES[opcode.rs]);
        }


        case instr_type::reg_rd_rs_rt:
        {
            return std::format("{} {}, {}, {}",instr->name,REG_NAMES[opcode.rd],REG_NAMES[opcode.rs],REG_NAMES[opcode.rt]);
        }

        case instr_type::reg_rd_rt_rs:
        {
            return std::format("{} {}, {}, {}",instr->name,REG_NAMES[opcode.rd],REG_NAMES[opcode.rt],REG_NAMES[opcode.rs]);
        }

        case instr_type::reg_rd:
        {
            return std::format("{} {}",instr->name,REG_NAMES[opcode.rd]);
        }

        case instr_type::reg_rs:
        {
            return std::format("{} {}",instr->name,REG_NAMES[opcode.rs]);
        }

        case instr_type::reg_rs_rt:
        {
            return std::format("{} {}, {}",instr->name,REG_NAMES[opcode.rs],REG_NAMES[opcode.rt]);
        }

        case instr_type::reg_rd_rs:
        {
            return std::format("{} {}, {}",instr->name,REG_NAMES[opcode.rd],REG_NAMES[opcode.rs]);
        }

        case instr_type::reg_rd_rt:
        {
            return std::format("{} {}, {}",instr->name,REG_NAMES[opcode.rd],REG_NAMES[opcode.rt]);
        }

        case instr_type::reg_rt_rd:
        {
            return std::format("{} {}, {}",instr->name,REG_NAMES[opcode.rt],REG_NAMES[opcode.rd]);
        }

        case instr_type::shift:
        {
            const u32 sa = read_sa(opcode.op);    
            return std::format("{} {}, {}, {}",instr->name,REG_NAMES[opcode.rd],REG_NAMES[opcode.rt],sa);
        }

        case instr_type::trap:
        {
            const u32 code = (opcode.op >> 6) & 0x000f'ffff;
            return std::format("{} 0x{:08x}",instr->name,code);
        }

        case instr_type::float_rt_fs:
        {
            const u32 fs = get_fs(opcode);
            return std::format("{} {}, $f{}",instr->name,REG_NAMES[opcode.rt],fs);
        }

        case instr_type::float_fd_fs:
        {
            const u32 fd = get_fd(opcode);
            const u32 fs = get_fs(opcode);
            return std::format("{} $f{}, $f{}",instr->name,fd,fs);
        }

        case instr_type::float_fd_fs_ft:
        {
            const u32 fd = get_fd(opcode);
            const u32 fs = get_fs(opcode);
            const u32 ft = get_ft(opcode);
            return std::format("{} $f{}, $f{}, $f{}",instr->name,fd,fs,ft);     
        }

        case instr_type::float_fs_ft:
        {
            const u32 fs = get_fs(opcode);
            const u32 ft = get_ft(opcode);
            return std::format("{} $f{}, $f{}",instr->name,fs,ft);            
        }

        case instr_type::branch_cop_cond:
        {
            const u64 target = branch_addr(addr,opcode.imm);
            return std::format("{} {}",instr->name,loc_name(program,target));
        }

        // we hit an actual unknown opcode!
        case instr_type::unk:
        {
            return std::format("{}",instr->name);
        }

        // NOTE: this should not get triggered
        case instr_type::mips_class: return "unknown_opcode";
    }

    // silence GCC
      
    assert(false);      
}

std::string disass_mips(Program& program, u64 addr, const Opcode &opcode)
{
    const Instr* instr = decode_instr(opcode,MIPS3);

    // opcode has a decoding override
    if(instr->disass_func)
    {
        return instr->disass_func(program,addr,opcode);
    }

    // decode in switch
    else
    {
        return disass_mips_default(program,addr,opcode,instr);
    }
}

std::string fmt_opcode(const Opcode& opcode)
{
    const u32 type = get_opcode_type(opcode.op);

    return std::format("op: 0x{:x}, rt: 0x{:x}, rs 0x{:x}, rd 0x{:x}, imm, 0x{:04x}, type: 0b{:06b}",opcode.op, opcode.rt, opcode.rs,
        opcode.rd, opcode.imm, type);
}

// TODO: note this is a debugging handler when we hit an actual unknown up
// we will just mark it!
std::string unknown_disass(Program& program, u64 addr, const Opcode& opcode)
{
    print("[UNKNOWN BASE OPCODE] 0x{:08x}: {}\n",addr, fmt_opcode(opcode));

    UNUSED(program); UNUSED(addr); UNUSED(opcode);
    assert(false);
}

std::string unknown_disass_cop0(Program& program, u64 addr, const Opcode& opcode)
{
    UNUSED(program); UNUSED(addr); UNUSED(opcode);

    return "cop0_unknown";
}


std::string unknown_disass_cop1(Program& program, u64 addr, const Opcode& opcode)
{
    UNUSED(program); UNUSED(addr); UNUSED(opcode);

    return "cop1_unknown";
}

std::string unknown_disass_cop1x(Program& program, u64 addr, const Opcode& opcode)
{
    UNUSED(program); UNUSED(addr); UNUSED(opcode);

    return "cop1x_unknown";
}

std::string unknown_disass_cop2(Program& program, u64 addr, const Opcode& opcode)
{
    UNUSED(program); UNUSED(addr); UNUSED(opcode);

    return "cop2_unknown";
}

std::string unknown_disass_special(Program& program, u64 addr, const Opcode& opcode)
{
    print("[UNKNOWN SPECIAL OPCODE] 0x{:08x}: {}, funct: 0b{:06b}\n",addr, fmt_opcode(opcode), (opcode.op >> 0) & FUNCT_MASK);

    UNUSED(program); UNUSED(addr); UNUSED(opcode);
    assert(false);
}

std::string unknown_disass_regimm(Program& program, u64 addr, const Opcode& opcode)
{
    print("[UNKNOWN REGIMM OPCODE] 0x{:08x}: {}, regimm: 0b{:05b}\n",addr, fmt_opcode(opcode), (opcode.op >> 16) & REGIMM_MASK);

    UNUSED(program); UNUSED(addr); UNUSED(opcode);
    assert(false);
}

std::string disass_lui(Program& program, u64 addr, const Opcode& opcode)
{
    UNUSED(program); UNUSED(addr);

    return std::format("lui {}, 0x{:04x}",REG_NAMES[opcode.rt],u16(opcode.imm));
}


std::string disass_cache(Program& program, u64 addr, const Opcode& opcode)
{
    UNUSED(program); UNUSED(addr);

    return std::format("cache {}, {}({})",opcode.rt,opcode.imm,REG_NAMES[opcode.rs]);
}

std::string disass_sync(Program& program, u64 addr, const Opcode& opcode)
{
    UNUSED(program); UNUSED(addr); UNUSED(opcode);

    return std::format("sync");
}


std::string disass_jalr(Program& program, u64 addr, const Opcode& opcode)
{
    UNUSED(program); UNUSED(addr);

    if(opcode.rd == RA)
    {
        return std::format("jalr {}",REG_NAMES[opcode.rs]);
    }

    else
    {
        return std::format("jalr {}, {}",REG_NAMES[opcode.rd],REG_NAMES[opcode.rs]);
    }
}

std::string disass_bgezal(Program& program, u64 addr, const Opcode& opcode)
{
    UNUSED(program); UNUSED(addr);
    const u64 target = branch_addr(addr,opcode.imm);

    if(opcode.rs == 0)
    {
        return std::format("bal {}",loc_name(program,target));
    }

    else
    {
        return std::format("bgezal {}, {}",REG_NAMES[opcode.rs],loc_name(program,target));
    }
}

std::string disass_sll(Program& program, u64 addr, const Opcode& opcode)
{
    if(opcode.op == 0)
    {
        return "nop";
    }

    const Instr* instr = decode_instr(opcode,MIPS3);
    return disass_mips_default(program,addr,opcode,instr);
}

std::string disass_jr(Program& program, u64 addr, const Opcode& opcode)
{
    UNUSED(program); UNUSED(addr);

    return std::format("jr {}",REG_NAMES[opcode.rs]);
}



std::string disass_beq(Program& program, u64 addr, const Opcode& opcode)
{
    const u64 target = branch_addr(addr,opcode.imm);

    // resolve pseudo instrs using zero reg
    if(opcode.rs == opcode.rt)
    {
        return std::format("b {}",loc_name(program,target));
    }

    else
    {
        return std::format("beq {}, {}, {}",REG_NAMES[opcode.rs],REG_NAMES[opcode.rt],loc_name(program,target));
    }
}

std::string disass_pref(Program& program, u64 addr, const Opcode& opcode)
{
    UNUSED(program); UNUSED(addr); 

    const u32 hint = opcode.rt;

    return std::format("pref {}, {}({})",hint,u16(opcode.imm),REG_NAMES[opcode.rs]);
}

std::string disass_or(Program& program, u64 addr, const Opcode& opcode)
{
    UNUSED(program); UNUSED(addr); 

    if(opcode.rs == 0)
    {
        return std::format("move {}, {}",REG_NAMES[opcode.rd],REG_NAMES[opcode.rt]);
    }

    else if(opcode.rt == 0)
    {
        return std::format("move {}, {}",REG_NAMES[opcode.rd],REG_NAMES[opcode.rs]);
    }

    const Instr* instr = decode_instr(opcode,MIPS1);
    return disass_mips_default(program,addr,opcode,instr);
}

// NOTE: this is pseudo op and not actual instr
std::string disass_li(Program& program, u64 addr, const Opcode& opcode)
{
    UNUSED(program); UNUSED(addr); 

    if(opcode.rs == 0)
    {
        return std::format("li {}, 0x{:04x}",REG_NAMES[opcode.rt],u16(opcode.imm));
    }


    const Instr* instr = decode_instr(opcode,MIPS3);
    return disass_mips_default(program,addr,opcode,instr);
}


std::string fmt_bit_op(const char *name,const Opcode& opcode, u32 size, u32 pos)
{
    return std::format("{} {}, {}, {}, {}",name,REG_NAMES[opcode.rs],REG_NAMES[opcode.rd],pos,size);
}


std::string disass_break(Program& program, u64 addr, const Opcode& opcode)
{
    UNUSED(program); UNUSED(addr);  UNUSED(opcode);

    return std::format("break");
}

std::string disass_mfc0(Program& program, u64 addr, const Opcode& opcode)
{
    UNUSED(program); UNUSED(addr);

    return std::format("mfc0 {}, {}",REG_NAMES[opcode.rt],COP0_NAMES[opcode.rd]);

}

std::string disass_mtc0(Program& program, u64 addr, const Opcode& opcode)
{
    UNUSED(program); UNUSED(addr);

    return std::format("mfc0 {}, {}",REG_NAMES[opcode.rt],COP0_NAMES[opcode.rd]);

}

}