#ifndef INSTR
#define INSTR(a,b,c,d,e,f)
#endif


// BASE, i.e the table circles back around
INSTR("SPECIAL",instr_type::mips_class,nullptr,nullptr,MIPS1,&decode_special) //0b000'000 
INSTR("REGIMM",instr_type::mips_class,nullptr,nullptr,MIPS1,&decode_regimm) //0b000'001
INSTR("j",instr_type::jump,&mark_jump,nullptr,MIPS1,nullptr) //0b000'010
INSTR("jal",instr_type::jump,&mark_jal,nullptr,MIPS1,nullptr) //0b000'011
INSTR("beq",instr_type::branch_rs_rt,&mark_beq,&disass_beq,MIPS1,nullptr) //0b000'100
INSTR("bne",instr_type::branch_rs_rt,&mark_bne,nullptr,MIPS1,nullptr) //0b000'101
INSTR("blez",instr_type::branch_rs,&mark_blez,nullptr,MIPS1,nullptr) //0b000'110
INSTR("bgtz",instr_type::branch_rs,&mark_bgtz,nullptr,MIPS1,nullptr) //0b000'111

INSTR("addi",instr_type::imm_signed,nullptr,nullptr,MIPS1,nullptr) //0b001'000
INSTR("addiu",instr_type::imm_signed,nullptr,&disass_li,MIPS1,nullptr) //0b001'001
INSTR("slti",instr_type::imm_signed,nullptr,nullptr,MIPS1,nullptr) //0b001'010
INSTR("sltiu",instr_type::imm_signed,nullptr,nullptr,MIPS1,nullptr) //0b001'011
INSTR("andi",instr_type::imm_unsigned,nullptr,nullptr,MIPS1,nullptr) //0b001'100
INSTR("ori",instr_type::imm_unsigned,nullptr,&disass_li,MIPS1,nullptr) //0b001'101
INSTR("xori",instr_type::imm_unsigned,nullptr,nullptr,MIPS1,nullptr) //0b001'110
INSTR("lui",instr_type::imm_unsigned,nullptr,&disass_lui,MIPS1,nullptr) //0b001'111
    
INSTR("COP0",instr_type::mips_class,nullptr,&unknown_disass_cop0,MIPS1,&decode_cop0) //0b010'000
INSTR("COP1",instr_type::mips_class,nullptr,&unknown_disass_cop1,MIPS1,&decode_cop1) //0b010'001
INSTR("COP2",instr_type::mips_class,nullptr,&unknown_disass_cop2,MIPS1,nullptr) //0b010'010
INSTR("COP1X",instr_type::mips_class,nullptr,&unknown_disass_cop1x,MIPS4,nullptr) //0b010'011
INSTR("beql",instr_type::branch_rs_rt,&mark_beql,nullptr,MIPS2,nullptr) //0b010'100
INSTR("bnel",instr_type::branch_rs_rt,&mark_bnel,nullptr,MIPS2,nullptr) //0b010'101
INSTR("blezl",instr_type::branch_rs,&mark_blezl,nullptr,MIPS2,nullptr) //0b010'110
INSTR("bgtzl",instr_type::branch_rs,&mark_bgtzl,nullptr,MIPS2,nullptr) //0b010'111

INSTR("daddi",instr_type::imm_signed,nullptr,nullptr,MIPS3) //0b011'000
INSTR("daddiu",instr_type::imm_signed,nullptr,nullptr,MIPS3) //0b011'001
INSTR("ldl",instr_type::load,nullptr,nullptr,MIPS3) //0b011'010
INSTR("ldr",instr_type::load,nullptr,nullptr,MIPS3) //0b011'011
INSTR("unknown_opcode",instr_type::unk,nullptr,nullptr,MIPS1,nullptr) //0b011'100
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b011'101
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b011'110
INSTR("unknown_opcode",instr_type::unk,nullptr,nullptr,MIPS1,nullptr) //0b011'111

INSTR("lb",instr_type::load,nullptr,nullptr,MIPS1,nullptr) //0b100'000
INSTR("lh",instr_type::load,nullptr,nullptr,MIPS1,nullptr)  //0b100'001
INSTR("lwl",instr_type::load,nullptr,nullptr,MIPS1,nullptr)  //0b100'010
INSTR("lw",instr_type::load,nullptr,nullptr,MIPS1,nullptr) //0b100'011
INSTR("lbu",instr_type::load,nullptr,nullptr,MIPS1,nullptr) //0b100'100
INSTR("lhu",instr_type::load,nullptr,nullptr,MIPS1,nullptr) //0b100'101
INSTR("lwr",instr_type::load,nullptr,nullptr,MIPS1,nullptr) //0b100'110
INSTR("lwu",instr_type::load,nullptr,nullptr,MIPS3) //0b100'111

INSTR("sb",instr_type::store,nullptr,nullptr,MIPS1,nullptr) //0b101'000
INSTR("sh",instr_type::store,nullptr,nullptr,MIPS1,nullptr) //0b101'001
INSTR("swl",instr_type::store,nullptr,nullptr,MIPS1,nullptr) //0b101'010
INSTR("sw",instr_type::store,nullptr,nullptr,MIPS1,nullptr) //0b101'011
INSTR("sdl",instr_type::store,nullptr,nullptr,MIPS3) //0b101'100
INSTR("sdr",instr_type::store,nullptr,nullptr,MIPS3) //0b101'101
INSTR("swr",instr_type::store,nullptr,nullptr,MIPS1,nullptr) //0b101'110
INSTR("cache",instr_type::unk,nullptr,&disass_cache,MIPS2,nullptr) //0b101'111

INSTR("ll",instr_type::load,nullptr,nullptr,MIPS2,nullptr) //0b110'000
INSTR("lwc1",instr_type::load_float,nullptr,nullptr,MIPS1,nullptr) //0b110'001
INSTR("lwc2",instr_type::load_cop2,nullptr,nullptr,MIPS1,nullptr) //0b110'010 TODO: i think reg names are system specific so leave for now
INSTR("pref",instr_type::unk,nullptr,&disass_pref,MIPS4) //0b110'011
INSTR("lld",instr_type::load,nullptr,nullptr,MIPS3) //0b110'100
INSTR("ldc1",instr_type::load_float,nullptr,nullptr,MIPS2,nullptr) //0b110'101
INSTR("ldc2",instr_type::load_cop2,nullptr,nullptr,MIPS2,nullptr) //0b110'110
INSTR("ld",instr_type::load,nullptr,nullptr,MIPS3) //0b110'111

INSTR("sc",instr_type::store,nullptr,nullptr,MIPS2,nullptr) //0b111'000
INSTR("swc1",instr_type::store_float,nullptr,nullptr,MIPS1,nullptr) //0b111'001
INSTR("swc2",instr_type::store_cop2,nullptr,nullptr,MIPS1,nullptr) //0b111'010 TODO: i think reg names are system specific so leave for now
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS3) //0b111'011
INSTR("scd",instr_type::store,nullptr,nullptr,MIPS3) //0b111'100
INSTR("sdc1",instr_type::store_float,nullptr,nullptr,MIPS2,nullptr)  //0b111'101
INSTR("ldc2",instr_type::store_cop2,nullptr,nullptr,MIPS2,nullptr) //0b111'110
INSTR("sd",instr_type::store,nullptr,nullptr,MIPS3) //0b111'111

    // SPECIAL opcode i.e 000'000
INSTR("sll",instr_type::shift,nullptr,&disass_sll,MIPS1,nullptr) //0b000'000
INSTR("unknown_opcode",instr_type::unk,nullptr,nullptr,MIPS1,nullptr) //0b000'001
INSTR("srl",instr_type::shift,nullptr,nullptr,MIPS1,nullptr) //0b000'010
INSTR("sra",instr_type::shift,nullptr,nullptr,MIPS1,nullptr) //0b000'011
INSTR("sllv",instr_type::reg_rd_rt_rs,nullptr,nullptr,MIPS1,nullptr) //0b000'100
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b000'101
INSTR("srlv",instr_type::reg_rd_rt_rs,nullptr,nullptr,MIPS1,nullptr) //0b000'110
INSTR("srav",instr_type::reg_rd_rt_rs,nullptr,nullptr,MIPS1,nullptr) //0b000'111

INSTR("jr",instr_type::branch_reg,&mark_jr,&disass_jr,MIPS1,nullptr) //0b001'000
INSTR("jalr",instr_type::branch_reg,&mark_jalr,&disass_jalr,MIPS1,nullptr) //0b001'001
INSTR("movz",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS4) //0b001'010 
INSTR("movn",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS4) //0b001'011 
INSTR("syscall",instr_type::trap,nullptr,nullptr,MIPS1,nullptr) //0b001'100
INSTR("break",instr_type::trap,nullptr,&disass_break,MIPS1,nullptr) //0b001'101
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b001'110
INSTR("sync",instr_type::trap,nullptr,&disass_sync,MIPS2,nullptr) //0b001'111

INSTR("mfhi",instr_type::reg_rd,nullptr,nullptr,MIPS1,nullptr) //0b010'000
INSTR("mthi",instr_type::reg_rs,nullptr,nullptr,MIPS1,nullptr) //0b010'001
INSTR("mflo",instr_type::reg_rd,nullptr,nullptr,MIPS1,nullptr) //0b010'010
INSTR("mtlo",instr_type::reg_rs,nullptr,nullptr,MIPS1,nullptr) //0b010'011
INSTR("dsllv",instr_type::reg_rd_rt_rs,nullptr,nullptr,MIPS3) //0b010'100
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b010'101
INSTR("dsrlv",instr_type::reg_rd_rt_rs,nullptr,nullptr,MIPS3) //0b010'110
INSTR("dsrav",instr_type::reg_rd_rt_rs,nullptr,nullptr,MIPS3) //0b010'111

INSTR("mult",instr_type::reg_rs_rt,nullptr,nullptr,MIPS1,nullptr) //0b011'000
INSTR("multu",instr_type::reg_rs_rt,nullptr,nullptr,MIPS1,nullptr) //0b011'001
INSTR("div",instr_type::reg_rs_rt,nullptr,nullptr,MIPS1,nullptr) //0b011'010
INSTR("divu",instr_type::reg_rs_rt,nullptr,nullptr,MIPS1,nullptr)//0b011'011
INSTR("dmult",instr_type::reg_rs_rt,nullptr,nullptr,MIPS3) //0b011'100
INSTR("dmultu",instr_type::reg_rs_rt,nullptr,nullptr,MIPS3) //0b011'101
INSTR("ddiv",instr_type::reg_rs_rt,nullptr,nullptr,MIPS3) //0b011'110
INSTR("ddivu",instr_type::reg_rs_rt,nullptr,nullptr,MIPS3) //0b011'111

INSTR("add",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS1,nullptr) //0b100'000
INSTR("addu",instr_type::reg_rd_rs_rt,nullptr,&disass_addu,MIPS1,nullptr) //0b100'001
INSTR("sub",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS1,nullptr) //0b100'010
INSTR("subu",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS1,nullptr) //0b100'011
INSTR("and",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS1,nullptr) //0b100'100
INSTR("or",instr_type::reg_rd_rs_rt,nullptr,&disass_or,MIPS1,nullptr) //0b100'101
INSTR("xor",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS1,nullptr) //0b100'110
INSTR("nor",instr_type::reg_rd_rs_rt,nullptr,&disass_nor,MIPS1,nullptr) //0b100'111

INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b101'000
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b101'001
INSTR("slt",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS1,nullptr) //0b101'010
INSTR("sltu",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS1,nullptr) //0b101'011
INSTR("dadd",instr_type::reg_rd_rs_rt,nullptr, nullptr,MIPS3) //0b101'100
INSTR("daddu",instr_type::reg_rd_rs_rt,nullptr, nullptr,MIPS3) //0b101'101
INSTR("dsub",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS3) //0b101'110
INSTR("dsubu",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS3) //0b101'111

INSTR("tge",instr_type::reg_rs_rt,nullptr,nullptr,MIPS2,nullptr) //0b110'000
INSTR("tgeu",instr_type::reg_rs_rt,nullptr,nullptr,MIPS2,nullptr) //0b110'001
INSTR("tlt",instr_type::reg_rs_rt,nullptr,nullptr,MIPS2,nullptr) //0b110'010
INSTR("tltu",instr_type::reg_rs_rt,nullptr,nullptr,MIPS2,nullptr) //0b110'011
INSTR("teq",instr_type::reg_rs_rt,nullptr,nullptr,MIPS2,nullptr) //0b110'100
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS2,nullptr) //0b110'101
INSTR("tne",instr_type::reg_rs_rt,nullptr,nullptr,MIPS2,nullptr) //0b110'110
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS2,nullptr) //0b110'111

INSTR("dsll",instr_type::shift,nullptr,nullptr,MIPS3) //0b111'000
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b111'001
INSTR("dsrl",instr_type::shift,nullptr,nullptr,MIPS3) //0b111'010
INSTR("dsra",instr_type::shift,nullptr,nullptr,MIPS3) //0b111'011
INSTR("dsll32",instr_type::shift,nullptr,nullptr,MIPS3) //0b111'100
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS3) //0b111'101
INSTR("dsrl32",instr_type::shift,nullptr,nullptr,MIPS3) //0b111'110
INSTR("dsra32",instr_type::shift,nullptr,nullptr,MIPS3) //0b111'111

    // REGIMM opcode
INSTR("bltz",instr_type::branch_rs,&mark_bltz,nullptr,MIPS1,nullptr) //0b000'00
INSTR("bgez",instr_type::branch_rs,&mark_bgez,nullptr,MIPS1,nullptr) //0b000'01
INSTR("bltzl",instr_type::branch_rs,&mark_bltzl,nullptr,MIPS2,nullptr) //0b000'10
INSTR("bgezl",instr_type::branch_rs,&mark_bgezl,nullptr,MIPS2,nullptr) //0b000'11
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b001'00
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b001'01
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b001'10
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b001'11

INSTR("tgei",instr_type::imm_rs,nullptr,nullptr,MIPS2,nullptr) //0b010'00
INSTR("tgeiu",instr_type::imm_rs,nullptr,nullptr,MIPS2,nullptr) //0b010'01
INSTR("tlti",instr_type::imm_rs,nullptr,nullptr,MIPS2,nullptr) //0b010'10
INSTR("tltiu",instr_type::imm_rs,nullptr,nullptr,MIPS2,nullptr) //0b010'11
INSTR("teqi",instr_type::imm_rs,nullptr,nullptr,MIPS2,nullptr) //0b011'00
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b011'01
INSTR("tnei",instr_type::imm_rs,nullptr,nullptr,MIPS2,nullptr) //0b011'10
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b011'11

INSTR("bltzal",instr_type::branch_rs,&mark_bltzal,nullptr,MIPS1,nullptr) //0b100'00
INSTR("bgezal",instr_type::branch_rs,&mark_bgezal,disass_bgezal,MIPS1,nullptr) //0b100'01
INSTR("bltzall",instr_type::branch_rs,&mark_bltzall,nullptr,MIPS2,nullptr) //0b100'10
INSTR("bgezall",instr_type::branch_rs,&mark_bgezall,nullptr,MIPS2,nullptr) //0b100'11
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b101'00
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b101'01
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b101'10
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b101'11

INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b110'00
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b110'01
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b110'10
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b110'11
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b111'00
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b111'01
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b111'10
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b111'11

    // COP0 RS
    // TODO: we havent done any versioning numbers for coprocessors
INSTR("mfc0",instr_type::reg_rt_rd,nullptr,&disass_mfc0,MIPS1,nullptr) //0b000'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b000'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b000'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b000'11
INSTR("mtc0",instr_type::reg_rt_rd,nullptr,&disass_mtc0,MIPS1,nullptr) //0b001'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b001'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b001'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b001'11

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b010'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b010'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b010'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b010'11
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b011'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b011'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b011'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b011'11

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b100'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b100'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b100'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b100'11
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b101'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b101'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b101'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b101'11

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b110'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b110'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b110'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b110'11
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b111'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b111'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b111'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b111'11  

    // COP0 FUNC
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b000'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b000'001
INSTR("tlbwi",instr_type::unk,nullptr,nullptr,MIPS1,nullptr) //0b000'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b000'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b000'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b000'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b000'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b000'111

INSTR("tlbp",instr_type::unk,nullptr,nullptr,MIPS1,nullptr) //0b001'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b001'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b001'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b001'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b001'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b001'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b001'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b001'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b010'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b010'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b010'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b010'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b010'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b010'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b010'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b010'111

INSTR("eret",instr_type::unk,nullptr,nullptr,MIPS1,nullptr) //0b011'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b011'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b011'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b011'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b011'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b011'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b011'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b011'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b100'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b100'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b100'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b100'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b100'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b100'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b100'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b100'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b101'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b101'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b101'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b101'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b101'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b101'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b101'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b101'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b110'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b110'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b110'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b110'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b110'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b110'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b110'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b110'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b111'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b111'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b111'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b111'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b111'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b111'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b111'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1,nullptr) //0b111'111


    // COP1 RS
INSTR("mfc1",instr_type::float_rt_fs,nullptr,nullptr,MIPS1,nullptr) //0b000'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'01
INSTR("cfc1",instr_type::float_rt_fs,nullptr,nullptr,MIPS1,nullptr) //0b000'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'11
INSTR("mtc1",instr_type::float_rt_fs,nullptr,nullptr,MIPS1,nullptr) //0b001'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'01
INSTR("ctc1",instr_type::float_rt_fs,nullptr,nullptr,MIPS1,nullptr) //0b001'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'11

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'11
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'11

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'11
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'11

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'11
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'11

    // COP1 BC
INSTR("bc1f",instr_type::branch_cop_cond,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b000'00
INSTR("bc1t",instr_type::branch_cop_cond,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b000'01
INSTR("bc1fl",instr_type::branch_cop_cond,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b000'10
INSTR("bc1tl",instr_type::branch_cop_cond,&unknown_mark_err,nullptr,MIPS1,nullptr) //0b000'11
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'11

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'11
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'11

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'11
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'11

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'11
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'00
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'01
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'10
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'11   

    // COP1 FMT S
INSTR("add.s",instr_type::float_fd_fs_ft,nullptr,nullptr,MIPS1,nullptr) //0b000'000
INSTR("sub.s",instr_type::float_fd_fs_ft,nullptr,nullptr,MIPS1,nullptr) //0b000'001
INSTR("mul.s",instr_type::float_fd_fs_ft,nullptr,nullptr,MIPS1,nullptr) //0b000'010
INSTR("div.s",instr_type::float_fd_fs_ft,nullptr,nullptr,MIPS1,nullptr) //0b000'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'101
INSTR("mov.s",instr_type::float_fd_fs,nullptr,nullptr,MIPS1,nullptr) //0b000'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'000
INSTR("trunc.l.s",instr_type::float_fd_fs_ft,nullptr,nullptr,MIPS1,nullptr) //0b001'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'100
INSTR("trunc.w.s",instr_type::float_fd_fs,nullptr,nullptr,MIPS1,nullptr) //0b001'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'000
INSTR("cvt.d.s",instr_type::float_fd_fs,nullptr,nullptr,MIPS1,nullptr) //0b100'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'011
INSTR("cvt.w.s",instr_type::float_fd_fs,nullptr,nullptr,MIPS1,nullptr) //0b100'100
INSTR("cvt.l.s",instr_type::float_fd_fs,nullptr,nullptr,MIPS1,nullptr) //0b100'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'101
INSTR("c.le.s",instr_type::float_fs_ft,nullptr,nullptr,MIPS1,nullptr) //0b111'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'111 

    // COP1 FMT D
INSTR("add.d",instr_type::float_fd_fs_ft,nullptr,nullptr,MIPS1,nullptr) //0b000'000
INSTR("sub.d",instr_type::float_fd_fs_ft,nullptr,nullptr,MIPS1,nullptr) //0b000'001
INSTR("mul.d",instr_type::float_fd_fs_ft,nullptr,nullptr,MIPS1,nullptr) //0b000'010
INSTR("div.d",instr_type::float_fd_fs_ft,nullptr,nullptr,MIPS1,nullptr) //0b000'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'101
INSTR("mov.d",instr_type::float_fd_fs,nullptr,nullptr,MIPS1,nullptr) //0b000'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'000
INSTR("trunc.l.d",instr_type::float_fd_fs_ft,nullptr,nullptr,MIPS1,nullptr) //0b001'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'100
INSTR("trunc.w.d",instr_type::float_fd_fs,nullptr,nullptr,MIPS1,nullptr) //0b001'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'111

INSTR("cvt.s.d",instr_type::float_fd_fs,nullptr,nullptr,MIPS1,nullptr) //0b100'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'011
INSTR("cvt.w.d",instr_type::float_fd_fs,nullptr,nullptr,MIPS1,nullptr) //0b100'100
INSTR("cvt.l.d",instr_type::float_fd_fs,nullptr,nullptr,MIPS1,nullptr) //0b100'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'011
INSTR("c.lt.d",instr_type::float_fs_ft,nullptr,nullptr,MIPS1,nullptr) //0b111'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'101
INSTR("c.le.d",instr_type::float_fs_ft,nullptr,nullptr,MIPS1,nullptr) //0b111'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'111  

    // COP1 FMT W
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'111

INSTR("cvt.s.w",instr_type::float_fd_fs,nullptr,nullptr,MIPS1,nullptr) //0b100'000
INSTR("cvt.d.w",instr_type::float_fd_fs,nullptr,nullptr,MIPS1,nullptr) //0b100'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'111 

    // COP1 FMT L
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b000'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b001'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b010'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b011'111

INSTR("cvt.s.l",instr_type::float_fd_fs,nullptr,nullptr,MIPS1,nullptr) //0b100'000
INSTR("cvt.d.l",instr_type::float_fd_fs,nullptr,nullptr,MIPS1,nullptr) //0b100'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b100'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b101'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b110'111

INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'000
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'001
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'010
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'011
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'100
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'101
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'110
INSTR("unknown_opcode",instr_type::unk,nullptr,&unknown_disass_cop1,MIPS1,nullptr) //0b111'111 

    // VERSION UNK - used as a dummy value for version failure 
INSTR("unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS3,nullptr)
