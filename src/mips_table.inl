
// NOTE: instruciton classes are specified by UPPER CASE
static constexpr Instr INSTR_TABLE[INSTR_TABLE_SIZE] = 
{
    // BASE, i.e the table circles back around
    {"SPECIAL",instr_type::mips_class,nullptr,nullptr,MIPS1,&decode_special}, //0b000'000
    {"REGIMM",instr_type::mips_class,nullptr,nullptr,MIPS1,&decode_regimm}, //0b000'001
    {"j",instr_type::jump,&mark_jump,nullptr,MIPS1}, //0b000'010
    {"jal",instr_type::jump,&mark_jal,nullptr,MIPS1}, //0b000'011
    {"beq",instr_type::branch_rs_rt,&mark_beq,&disass_beq,MIPS1}, //0b000'100
    {"bne",instr_type::branch_rs_rt,&mark_bne,nullptr,MIPS1}, //0b000'101
    {"blez",instr_type::branch_rs,&mark_blez,nullptr,MIPS1}, //0b000'110
    {"bgtz",instr_type::branch_rs,&mark_bgtz,nullptr,MIPS1}, //0b000'111

    {"addi",instr_type::imm_signed,nullptr,nullptr,MIPS1}, //0b001'000
    {"addiu",instr_type::imm_signed,nullptr,&disass_li,MIPS1}, //0b001'001
    {"slti",instr_type::imm_signed,nullptr,nullptr,MIPS1}, //0b001'010
    {"sltiu",instr_type::imm_signed,nullptr,nullptr,MIPS1}, //0b001'011
    {"andi",instr_type::imm_unsigned,nullptr,nullptr,MIPS1}, //0b001'100
    {"ori",instr_type::imm_unsigned,nullptr,&disass_li,MIPS1}, //0b001'101
    {"xori",instr_type::imm_unsigned,nullptr,nullptr,MIPS1}, //0b001'110
    {"lui",instr_type::imm_unsigned,nullptr,&disass_lui,MIPS1}, //0b001'111
    
    // TODO: we should impl coprocessor instrucitons but skip for now as they are not relevant
    {"COP0",instr_type::mips_class,nullptr,&unknown_disass_cop0,MIPS1,&decode_cop0}, //0b010'000
    {"COP1",instr_type::mips_class,nullptr,&unknown_disass_cop1,MIPS1}, //0b010'001
    {"COP2",instr_type::mips_class,nullptr,&unknown_disass_cop2,MIPS1}, //0b010'010
    {"COP1X",instr_type::mips_class,nullptr,&unknown_disass_cop1x,MIPS4}, //0b010'011
    {"beql",instr_type::branch_rs_rt,&mark_beql,nullptr,MIPS2}, //0b010'100
    {"bnel",instr_type::branch_rs_rt,&mark_bnel,nullptr,MIPS2}, //0b010'101
    {"blezl",instr_type::branch_rs,&mark_blezl,nullptr,MIPS2}, //0b010'110
    {"bgtzl",instr_type::branch_rs,&mark_bgtzl,nullptr,MIPS2}, //0b010'111

    {"daddi",instr_type::imm_signed,nullptr,nullptr,MIPS3}, //0b011'000
    {"daddiu",instr_type::imm_signed,nullptr,nullptr,MIPS3}, //0b011'001
    {"ldl",instr_type::load,nullptr,nullptr,MIPS3}, //0b011'010
    {"ldr",instr_type::load,nullptr,nullptr,MIPS3}, //0b011'011
    {"unknown_opcode",instr_type::unk,nullptr,nullptr,MIPS1}, //0b011'100
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b011'101
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b011'110
    {"unknown_opcode",instr_type::unk,nullptr,nullptr,MIPS1}, //0b011'111

    {"lb",instr_type::load,nullptr,nullptr,MIPS1}, //0b100'000
    {"lh",instr_type::load,nullptr,nullptr,MIPS1},  //0b100'001
    {"lwl",instr_type::load,nullptr,nullptr,MIPS1},  //0b100'010
    {"lw",instr_type::load,nullptr,nullptr,MIPS1}, //0b100'011
    {"lbu",instr_type::load,nullptr,nullptr,MIPS1}, //0b100'100
    {"lhu",instr_type::load,nullptr,nullptr,MIPS1}, //0b100'101
    {"lwr",instr_type::load,nullptr,nullptr,MIPS1}, //0b100'110
    {"lwu",instr_type::load,nullptr,nullptr,MIPS3}, //0b100'111

    {"sb",instr_type::store,nullptr,nullptr,MIPS1}, //0b101'000
    {"sh",instr_type::store,nullptr,nullptr,MIPS1}, //0b101'001
    {"swl",instr_type::store,nullptr,nullptr,MIPS1}, //0b101'010
    {"sw",instr_type::store,nullptr,nullptr,MIPS1}, //0b101'011
    {"sdl",instr_type::store,nullptr,nullptr,MIPS3}, //0b101'100
    {"sdr",instr_type::store,nullptr,nullptr,MIPS3}, //0b101'101
    {"swr",instr_type::store,nullptr,nullptr,MIPS1}, //0b101'110
    {"cache",instr_type::unk,nullptr,&disass_cache,MIPS2}, //0b101'111

    {"ll",instr_type::load,nullptr,nullptr,MIPS2}, //0b110'000
    {"lwc1",instr_type::load_float,nullptr,nullptr,MIPS1}, //0b110'001
    {"lwc2",instr_type::load_cop2,nullptr,nullptr,MIPS1}, //0b110'010 TODO: i think reg names are system specific so leave for now
    {"pref",instr_type::unk,nullptr,&disass_pref,MIPS4}, //0b110'011
    {"lld",instr_type::load,nullptr,nullptr,MIPS3}, //0b110'100
    {"ldc1",instr_type::load_float,nullptr,nullptr,MIPS2}, //0b110'101
    {"ldc2",instr_type::load_cop2,nullptr,nullptr,MIPS2}, //0b110'110
    {"ld",instr_type::load,nullptr,nullptr,MIPS3}, //0b110'111

    {"sc",instr_type::store,nullptr,nullptr,MIPS2}, //0b111'000
    {"swc1",instr_type::store_float,nullptr,nullptr,MIPS1}, //0b111'001
    {"swc2",instr_type::store_cop2,nullptr,nullptr,MIPS1}, //0b111'010 TODO: i think reg names are system specific so leave for now
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS3}, //0b111'011
    {"scd",instr_type::store,nullptr,nullptr,MIPS3}, //0b111'100
    {"sdc1",instr_type::store_float,nullptr,nullptr,MIPS2},  //0b111'101
    {"ldc2",instr_type::store_cop2,nullptr,nullptr,MIPS2}, //0b111'110
    {"sd",instr_type::store,nullptr,nullptr,MIPS3}, //0b111'111

    // SPECIAL opcode i.e 000'000
    {"sll",instr_type::shift,nullptr,&disass_sll,MIPS1}, //0b000'000
    {"unknown_opcode",instr_type::unk,nullptr,nullptr,MIPS1}, //0b000'001
    {"srl",instr_type::shift,nullptr,nullptr,MIPS1}, //0b000'010
    {"sra",instr_type::shift,nullptr,nullptr,MIPS1}, //0b000'011
    {"sllv",instr_type::reg_rd_rt_rs,nullptr,nullptr,MIPS1}, //0b000'100
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b000'101
    {"srlv",instr_type::reg_rd_rt_rs,nullptr,nullptr,MIPS1}, //0b000'110
    {"srav",instr_type::reg_rd_rt_rs,nullptr,nullptr,MIPS1}, //0b000'111

    {"jr",instr_type::branch_reg,&mark_jr,&disass_jr,MIPS1}, //0b001'000
    {"jalr",instr_type::branch_reg,&mark_jalr,&disass_jalr,MIPS1}, //0b001'001
    {"movz",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS4}, //0b001'010 
    {"movn",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS4}, //0b001'011 
    {"syscall",instr_type::trap,nullptr,nullptr,MIPS1}, //0b001'100
    {"break",instr_type::trap,nullptr,&disass_break,MIPS1}, //0b001'101
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b001'110
    {"sync",instr_type::trap,nullptr,&disass_sync,MIPS2}, //0b001'111

    {"mfhi",instr_type::reg_rd,nullptr,nullptr,MIPS1}, //0b010'000
    {"mthi",instr_type::reg_rs,nullptr,nullptr,MIPS1}, //0b010'001
    {"mflo",instr_type::reg_rd,nullptr,nullptr,MIPS1}, //0b010'010
    {"mtlo",instr_type::reg_rs,nullptr,nullptr,MIPS1}, //0b010'011
    {"dsllv",instr_type::reg_rd_rt_rs,nullptr,nullptr,MIPS3}, //0b010'100
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b010'101
    {"dsrlv",instr_type::reg_rd_rt_rs,nullptr,nullptr,MIPS3}, //0b010'110
    {"dsrav",instr_type::reg_rd_rt_rs,nullptr,nullptr,MIPS3}, //0b010'111

    {"mult",instr_type::reg_rs_rt,nullptr,nullptr,MIPS1}, //0b011'000
    {"multu",instr_type::reg_rs_rt,nullptr,nullptr,MIPS1}, //0b011'001
    {"div",instr_type::reg_rs_rt,nullptr,nullptr,MIPS1}, //0b011'010
    {"divu",instr_type::reg_rs_rt,nullptr,nullptr,MIPS1},//0b011'011
    {"dmult",instr_type::reg_rs_rt,nullptr,nullptr,MIPS3}, //0b011'100
    {"dmultu",instr_type::reg_rs_rt,nullptr,nullptr,MIPS3}, //0b011'101
    {"ddiv",instr_type::reg_rs_rt,nullptr,nullptr,MIPS3}, //0b011'110
    {"ddivu",instr_type::reg_rs_rt,nullptr,nullptr,MIPS3}, //0b011'111

    {"add",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS1}, //0b100'000
    {"addu",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS1}, //0b100'001
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b100'010
    {"subu",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS1}, //0b100'011
    {"and",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS1}, //0b100'100
    {"or",instr_type::reg_rd_rs_rt,nullptr,&disass_or,MIPS1}, //0b100'101
    {"xor",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS1}, //0b100'110
    {"nor",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS1}, //0b100'111

    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b101'000
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b101'001
    {"slt",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS1}, //0b101'010
    {"sltu",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS1}, //0b101'011
    {"dadd",instr_type::reg_rd_rs_rt,nullptr, nullptr,MIPS3}, //0b101'100
    {"daddu",instr_type::reg_rd_rs_rt,nullptr, nullptr,MIPS3}, //0b101'101
    {"dsub",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS3}, //0b101'110
    {"dsubu",instr_type::reg_rd_rs_rt,nullptr,nullptr,MIPS3}, //0b101'111

    {"tge",instr_type::reg_rs_rt,nullptr,nullptr,MIPS2}, //0b110'000
    {"tgeu",instr_type::reg_rs_rt,nullptr,nullptr,MIPS2}, //0b110'001
    {"tlt",instr_type::reg_rs_rt,nullptr,nullptr,MIPS2}, //0b110'010
    {"tltu",instr_type::reg_rs_rt,nullptr,nullptr,MIPS2}, //0b110'011
    {"teq",instr_type::reg_rs_rt,nullptr,nullptr,MIPS2}, //0b110'100
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS2}, //0b110'101
    {"tne",instr_type::reg_rs_rt,nullptr,nullptr,MIPS2}, //0b110'110
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS2}, //0b110'111

    {"dsll",instr_type::shift,nullptr,nullptr,MIPS3}, //0b111'000
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b111'001
    {"dsrl",instr_type::shift,nullptr,nullptr,MIPS3}, //0b111'010
    {"dsra",instr_type::shift,nullptr,nullptr,MIPS3}, //0b111'011
    {"dsll32",instr_type::shift,nullptr,nullptr,MIPS3}, //0b111'100
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS3}, //0b111'101
    {"dsrl32",instr_type::shift,nullptr,nullptr,MIPS3}, //0b111'110
    {"dsra32",instr_type::shift,nullptr,nullptr,MIPS3}, //0b111'111

    // REGIMM opcode
    {"bltz",instr_type::branch_rs,&mark_bltz,nullptr,MIPS1}, //0b000'00
    {"bgez",instr_type::branch_rs,&mark_bgez,nullptr,MIPS1}, //0b000'01
    {"bltzl",instr_type::branch_rs,&mark_bltzl,nullptr,MIPS2}, //0b000'10
    {"bgezl",instr_type::branch_rs,&mark_bgezl,nullptr,MIPS2}, //0b000'11
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b001'00
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b001'01
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b001'10
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b001'11

    {"tgei",instr_type::imm_rs,nullptr,nullptr,MIPS2}, //0b010'00
    {"tgeiu",instr_type::imm_rs,nullptr,nullptr,MIPS2}, //0b010'01
    {"tlti",instr_type::imm_rs,nullptr,nullptr,MIPS2}, //0b010'10
    {"tltiu",instr_type::imm_rs,nullptr,nullptr,MIPS2}, //0b010'11
    {"teqi",instr_type::imm_rs,nullptr,nullptr,MIPS2}, //0b011'00
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b011'01
    {"tnei",instr_type::imm_rs,nullptr,nullptr,MIPS2}, //0b011'10
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b011'11

    {"bltzal",instr_type::branch_rs,&mark_bltzal,nullptr,MIPS1}, //0b100'00
    {"bgezal",instr_type::branch_rs,&mark_bgezal,disass_bgezal,MIPS1}, //0b100'01
    {"bltzall",instr_type::branch_rs,&mark_bltzall,nullptr,MIPS2}, //0b100'10
    {"bgezall",instr_type::branch_rs,&mark_bgezall,nullptr,MIPS2}, //0b100'11
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b101'00
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b101'01
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b101'10
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b101'11

    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b110'00
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b110'01
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b110'10
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b110'11
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b111'00
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b111'01
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b111'10
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b111'11

    // COP0 RS
    // TODO: we havent done any versioning numbers of this section yet...
    {"mfc0",instr_type::reg_rt_rd,nullptr,&disass_mfc0,MIPS1}, //0b000'00
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b000'01
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b000'10
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b000'11
    {"mtc0",instr_type::reg_rt_rd,nullptr,&disass_mtc0,MIPS1}, //0b001'00
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b001'01
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b001'10
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b001'11

    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b010'00
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b010'01
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b010'10
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b010'11
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b011'00
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b011'01
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b011'10
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b011'11

    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b100'00
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b100'01
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1},//0b100'10
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1},//0b100'11
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b101'00
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b101'01
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b101'10
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b101'11

    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b110'00
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b110'01
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b110'10
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b110'11
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b111'00
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b111'01
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b111'10
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS1}, //0b111'11

    // VERSION UNK - used as a dummy value for version failure 
    {"unknown_opcode",instr_type::unk,&unknown_mark_err,nullptr,MIPS3},
};

const Instr* const VER_UNKNOWN = &INSTR_TABLE[INSTR_TABLE_SIZE - 1];