#include <disass.h>


enum class instr_type
{
    reg_rd_rs_rt,
    reg_rd_rt_rs,
    reg_rs_rt,
    reg_rd_rs,
    reg_rd_rt,
    reg_rt_rd,
    reg_rd,
    reg_rs,
    shift,

    trap,

    imm_signed,
    imm_unsigned,
    imm_rs,

    store,
    store_float,
    store_cop2,

    load,
    load_float,
    load_cop2,

    branch_rs_rt,
    branch_rs,
    branch_reg,
    jump,

    bit_op,

    unk,
};




struct Opcode
{
    u32 op = 0;
    u32 type = 0;
    u32 rd = 0;
    u32 rs = 0;
    u32 rt = 0;
    s16 imm = 0;
};


static constexpr u32 REG_MASK = 0b111'11;

static const char *REG_NAMES[REG_MASK + 1]
{
    "$zero", 
    "$at", // assembler tempoary
    "$v0", // return value or expression evaluation
    "$v1",
    "$a0", // args
    "$a1",
    "$a2",
    "$a3",
    "$t0",
    "$t1", // temp
    "$t2",
    "$t3",
    "$t4",
    "$t5",
    "$t6",
    "$t7",
    "$s0",
    "$s1", // saved regs
    "$s2",
    "$s3",
    "$s4",
    "$s5",
    "$s6",
    "$s7",
    "$t8",
    "$t9",
    "$k0", // kernel reserved
    "$k1",
    "$gp", // global pointer 
    "$sp", // stack pointer 
    "$fp", // frame pointer
    "$ra", // return address 
};


static constexpr u32 REG_RA = 31;


static constexpr u32 MIPS_INSTR_SIZE = sizeof(u32);



using DISASS_FUNC = std::string (*)(Program& program, u64 addr, const Opcode& opcode);

// return true if block is finished!
using MARK_FUNC = b32 (*)(Program& program,Func& func,  Block& block, u64 addr, const Opcode& opcode);



u64 branch_addr(u64 pc, s16 imm)
{
    return pc  + (sign_extend_type<s32,s16>(imm) << 2);
}


u64 jump_addr(u64 pc, u32 opcode)
{
    const u64 jump_mask = u64(0x03ff'ffff);

    return (u64(opcode & jump_mask) << u64(2)) | (pc & ~jump_mask);
}

u32 read_sa(u32 opcode)
{
    return (opcode >> 6) & 0b11'111;
}  


struct Instr;
using CHAIN_FUNC = const Instr* (*)(const Opcode& opcode, u32 version);

struct Instr
{
    const char *name;
    instr_type fmt;
    MARK_FUNC mark_func;
    DISASS_FUNC disass_func;

    // what version was this added in
    u32 version;

    // fptr that will give back the correct instr field
    CHAIN_FUNC chain = nullptr;
};

const Instr* decode_instr(const Opcode& opcode, u32 version);
const Instr* decode_regimm(const Opcode& opcode,u32 version);
const Instr* decode_special(const Opcode& opcode,u32 version);
const Instr* decode_bshfl(const Opcode& opcode, u32 version);
const Instr* decode_dbshfl(const Opcode& opcode,u32 version);

const Instr* decode_srl(const Opcode& opcode,u32 version);
const Instr* decode_srlv(const Opcode& opcode,u32 version);
const Instr* decode_dsrl(const Opcode& opcode,u32 version);
const Instr* decode_dsrlv(const Opcode& opcode,u32 version);


static constexpr u32 INSTR_TYPE_MASK = 0b111'111;
static constexpr u32 FUNCT_MASK = 0b111'111;
static constexpr u32 REGIMM_MASK = 0b111'11;

// chain
static constexpr u32 BSHFL_MASK = 0b111'11;
static constexpr u32 DBSHFL_MASK = 0b111'11;

static constexpr u32 SHIFT_R_MASK = 0b1;

enum MIPS_VER
{
    MIPS1,
    MIPS2,
    MIPS3,
    MIPS4,
};


#include <disass_mips.cpp>
#include <mark_mips.cpp>
#include <decode_mips.cpp>


// TODO: make this cache the section

// TODO: how do we deal with delay slots?
void mark_block_mips(Program& program,Func& func,Block& block)
{
    u64 addr = block.addr;
    b32 done = false;
    
    while(!done)
    {
        u32 op;

        // check read is in range
        if(!read_program(program,addr, &op))
        {
            print("Warning addr 0x{:x} out of range for block\n",addr);
            done = true;
            break;
        }

        else
        {
            addr += MIPS_INSTR_SIZE;
            block.size += MIPS_INSTR_SIZE;
        }

        const auto opcode = make_opcode(op);
        const Instr* instr = decode_instr(opcode,MIPS3);

        if(instr->mark_func)
        {
            done = instr->mark_func(program,func,block,addr,opcode);
        }

        // we have hit the start of another basic block due to a branch over another
        if(block_exists(program,addr))
        {
            done = true;
            break;
        }
    }
}

void print_console_mips(Program& program, Config& config)
{

    for(const auto &[key, func] : program.func_lookup)
    {
        if(!config.print_external && func.external)
        {
            continue;
        }

        for(u64 block_start : func.block_list)
        {
            const auto& block = program.block_lookup[block_start];

            print("{}:\n",block.name);

            // print the block
            for(u64 addr = block.addr; addr != block.addr + block.size; )
            {
                u32 op;

                // check read is in range
                if(!read_program(program,addr, &op))
                {
                    print("Warning addr 0x{:x} out of range for block\n",addr);
                    exit(1);
                }

                addr += MIPS_INSTR_SIZE;

                const auto opcode = make_opcode(op);    

                print("   ");

                if(config.print_addr)
                {
                    print("0x{:08x}: ",(addr - MIPS_INSTR_SIZE));
                }

                if(config.print_opcodes)
                {
                    print("0x{:08x} \n",op);
                }

                // print the actual instruction
                print("{}\n",disass_mips(program,addr,opcode));
            }
        }

        puts("\n");
    }
}

void print_console_linear_mips(Program& program, Config& config)
{
    for(const auto &[key, func] : program.func_lookup)
    {
        if(!config.print_external && func.external)
        {
            continue;
        }


        print("{}:\n",func.name);

        // print the block
        for(u64 addr = func.addr; addr != func.addr + func.size; )
        {
            u32 op;

            // check read is in range
            if(!read_program(program,addr, &op))
            {
                print("Warning addr 0x{:x} out of range for block\n",addr);
                exit(1);
            }

            addr += MIPS_INSTR_SIZE;

            const auto opcode = make_opcode(op);    

            print("   ");

            if(config.print_addr)
            {
                print("0x{:08x}: ",(addr - MIPS_INSTR_SIZE));
            }

            if(config.print_opcodes)
            {
                print("0x{:08x} \n",op);
            }

            // print the actual instruction
            print("{}\n",disass_mips(program,addr,opcode));
        }
    
        puts("\n");
    }    
}