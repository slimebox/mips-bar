namespace beyond_all_repair
{
// NOTE: this is unimpl stub 
b32 unknown_mark(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    print("    0x{:08x}: 0x{:08x} {}\n",pc - MIPS_INSTR_SIZE,opcode.op,disass_mips(program,pc,opcode));

    UNUSED(program); UNUSED(pc); UNUSED(opcode); UNUSED(func); UNUSED(block);
    assert(false);
}


b32 unknown_mark_err(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    UNUSED(program); UNUSED(pc); UNUSED(opcode); UNUSED(func); UNUSED(block);
    return true;
}

void cond_branch_exit(Program& program,Func& func, Block& block,u64 target, u64 pc)
{
    // account for delay slot
    block.size += MIPS_INSTR_SIZE;
    

    // create block exists for target + fallthrough 
    add_block(program,func,target,pc,default_loc_name(target));
    block.exit.push_back(target);
    
    const u64 fallthrough = pc + MIPS_INSTR_SIZE;

    // branch is not taken (i.e fallthrough)
    add_block(program,func,fallthrough,pc,default_loc_name(fallthrough));
    block.exit.push_back(fallthrough);
}

void branch_exit(Program& program, Func& func, Block& block, u64 target,u64 pc)
{
    add_block(program,func,target,pc,default_loc_name(target));
    block.exit.push_back(target);

    block.size += MIPS_INSTR_SIZE;   
}

b32 mark_jr(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    UNUSED(program); UNUSED(pc); UNUSED(opcode); UNUSED(func); UNUSED(block);
    // TODO: revisit this when partial evalutiaon is impl

    block.size += MIPS_INSTR_SIZE;

    return true;
}

b32 mark_jalr(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    UNUSED(program); UNUSED(pc); UNUSED(opcode); UNUSED(func); UNUSED(block);
    // TODO: revisit this when partial evalutiaon is impl

    // NOTE: no block size increment as we are going to immediatly go over the delay slot anyways

    return false;
}

b32 mark_jump(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    const u64 target = jump_addr(pc,opcode.op);

    // target for exit
    add_block(program,func,target,pc,default_loc_name(target));
    block.exit.push_back(target);

    block.size += MIPS_INSTR_SIZE;

    return true;
}

b32 mark_jal(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    UNUSED(func);

    const u64 target = jump_addr(pc,opcode.op);

    // add target as func
    add_func(program,target,pc,SIZE_UNK,default_func_name(target));

    block.size += MIPS_INSTR_SIZE;

    return true;
}

b32 mark_beq(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    const u64 target = branch_addr(pc,opcode.imm);

    // branch
    if(opcode.rs == opcode.rt)
    {
        branch_exit(program,func,block,target,pc);
    }

    // cond branch
    else
    {
        cond_branch_exit(program,func,block,target,pc);        
    }

    return true;
}


b32 mark_blez(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    const u64 target = branch_addr(pc,opcode.imm);

    // branch
    if(opcode.rs == 0)
    {
        branch_exit(program,func,block,target,pc);
    }

    // cond branch
    else
    {
        cond_branch_exit(program,func,block,target,pc);        
    }

    return true;
}


b32 mark_bgez(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    const u64 target = branch_addr(pc,opcode.imm);

    // branch
    if(opcode.rs == 0)
    {
        branch_exit(program,func,block,target,pc);
    }

    // cond branch
    else
    {
        cond_branch_exit(program,func,block,target,pc);        
    }

    return true;
}


b32 mark_bgezl(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    const u64 target = branch_addr(pc,opcode.imm);

    // branch
    if(opcode.rs == 0)
    {
        branch_exit(program,func,block,target,pc);       
    }

    // cond branch
    else
    {
        cond_branch_exit(program,func,block,target,pc);        
    }

    return true;
}


b32 mark_bne(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    const u64 target = branch_addr(pc,opcode.imm);

    cond_branch_exit(program,func,block,target,pc);        
    return true;
}

b32 mark_bgtz(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    // branch is allways false
    if(opcode.rs == 0)
    {
        return false;
    }

    const u64 target = branch_addr(pc,opcode.imm);

    cond_branch_exit(program,func,block,target,pc);        
    return true;
}


b32 mark_bgtzl(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    // branch is allways false
    if(opcode.rs == 0)
    {
        return false;
    }

    const u64 target = branch_addr(pc,opcode.imm);

    cond_branch_exit(program,func,block,target,pc);        
    return true;
}

b32 mark_bltz(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    // branch is allways false
    if(opcode.rs == 0)
    {
        return false;
    }

    const u64 target = branch_addr(pc,opcode.imm);

    cond_branch_exit(program,func,block,target,pc);        
    return true;
}


b32 mark_bltzl(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    // branch is allways false
    if(opcode.rs == 0)
    {
        return false;
    }

    const u64 target = branch_addr(pc,opcode.imm);

    cond_branch_exit(program,func,block,target,pc);        
    return true;
}




b32 mark_bnel(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    // never taken
    if(opcode.rs == opcode.rt)
    {
        return false;
    }

    const u64 target = branch_addr(pc,opcode.imm);

    cond_branch_exit(program,func,block,target,pc);        
    return true;
}


b32 mark_beql(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    const u64 target = branch_addr(pc,opcode.imm);

    // branch
    if(opcode.rs == opcode.rt)
    {
        branch_exit(program,func,block,target,pc);
    }

    // cond branch
    else
    {
        cond_branch_exit(program,func,block,target,pc);        
    }

    return true;
}


b32 mark_blezl(Program& program,Func& func,  Block& block, u64 pc, const Opcode& opcode)
{
    const u64 target = branch_addr(pc,opcode.imm);

    // branch
    if(opcode.rs == opcode.rt)
    {
        branch_exit(program,func,block,target,pc);
    }

    // cond branch
    else
    {
        cond_branch_exit(program,func,block,target,pc);        
    }

    return true;
}



b32 mark_bgezall(Program& program, Func& func, Block& block, u64 pc, const Opcode& opcode)
{
    UNUSED(func); UNUSED(block);

    // used as a condtional or non conditonal call
    const u64 target = branch_addr(pc,opcode.imm);

    add_func(program,target,pc,SIZE_UNK,default_func_name(target));

    return false;
}

b32 mark_bltzall(Program& program, Func& func, Block& block, u64 pc, const Opcode& opcode)
{
    UNUSED(func); UNUSED(block);

    // used as a condtional or non conditonal call
    const u64 target = branch_addr(pc,opcode.imm);

    add_func(program,target,pc,SIZE_UNK,default_func_name(target));

    return false;
}



b32 mark_bgezal(Program& program, Func& func, Block& block, u64 pc, const Opcode& opcode)
{
    UNUSED(func); UNUSED(block);

    // used as a condtional or non conditonal call
    const u64 target = branch_addr(pc,opcode.imm);

    if(opcode.rs == 0)
    {
        // call is within 12 bytes this is just to get the cur address
        if(abs(target - pc) <= 12)
        {
            local_call(program,func,target,target);
        }

        else
        {
            add_func(program,target,pc,SIZE_UNK,default_func_name(target));
        }
    }

    else
    {
        add_func(program,target,pc,SIZE_UNK,default_func_name(target));
    }

    return false;
}

b32 mark_bltzal(Program& program, Func& func, Block& block, u64 pc, const Opcode& opcode)
{
    UNUSED(func); UNUSED(block);

    // never taken!
    if(opcode.rs == 0)
    {
        return false;
    }

    // used as a condtional or non conditonal call
    const u64 target = branch_addr(pc,opcode.imm);

    add_func(program,target,pc,SIZE_UNK,default_func_name(target));

    return false;
}
}