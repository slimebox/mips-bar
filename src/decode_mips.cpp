
namespace beyond_all_repair
{
// base offsets
static constexpr u32 BASE_OFFSET = 0;
static constexpr u32 SPECIAL_OFFSET = BASE_OFFSET + INSTR_TYPE_MASK + 1;
static constexpr u32 REGIMM_OFFSET = SPECIAL_OFFSET + FUNCT_MASK + 1;


// cop0 offsets
static constexpr u32 COP0_RS_OFFSET = REGIMM_OFFSET + REGIMM_MASK + 1;
static constexpr u32 COP0_FUNCT_OFFSET = COP0_RS_OFFSET + COP0_RS_MASK + 1;
static constexpr u32 COP0_END = COP0_FUNCT_OFFSET + COP0_FUNCT_MASK + 1;



// cop1 offsets
static constexpr u32 COP1_RS_SHIFT = 21;
static constexpr u32 COP1_RS_MASK = 0b111'11;

static constexpr u32 COP1_BC_MASK = 0b111'11;
static constexpr u32 COP1_BC_SHIFT = 16;

static constexpr u32 COP1_FMT_SHIFT = 0;
static constexpr u32 COP1_FMT_MASK = 0b111'111;

static constexpr u32 COP1_RS_OFFSET = COP0_END;
static constexpr u32 COP1_BC_OFFSET = COP1_RS_OFFSET + COP1_RS_MASK + 1;

static constexpr u32 COP1_FMT_S_OFFSET = COP1_BC_OFFSET + COP1_BC_MASK + 1;
static constexpr u32 COP1_FMT_D_OFFSET = COP1_FMT_S_OFFSET + COP1_FMT_MASK + 1;
static constexpr u32 COP1_FMT_W_OFFSET = COP1_FMT_D_OFFSET + COP1_FMT_MASK + 1;
static constexpr u32 COP1_FMT_L_OFFSET = COP1_FMT_W_OFFSET + COP1_FMT_MASK + 1;



static constexpr u32 LAST_OFFSET = COP1_FMT_L_OFFSET;
static constexpr u32 LAST_MASK = COP1_FMT_MASK;

// NOTE: generally every 4 or 8 instrs have the same format.

// NOTE: this is kept as one contiguous table rather than seperate ones to keep it easy to dump and to avoid fracturing memory

// NOTE: extra entry for chain failure
static constexpr u32 INSTR_TABLE_SIZE = LAST_OFFSET + LAST_MASK + 2;


// NOTE: instruction class names that require further decoding are denoted with CAPS

#define INSTR(a,b,c,d,e,f) {a,b,c,d,e,f},

static constexpr Instr INSTR_TABLE[] = {
    #include <mips_table.inl>
};
#undef INSTR(a,b,c,d,e,f)

static constexpr u32 ACTUAL_TABLE_SIZE = sizeof(INSTR_TABLE) / sizeof(INSTR_TABLE[0]);

// check everything has an initalizer
static_assert(INSTR_TABLE_SIZE == ACTUAL_TABLE_SIZE);

const Instr* const VER_UNKNOWN = &INSTR_TABLE[INSTR_TABLE_SIZE - 1];

#include <mips_table.inl>

// mips1-3
static constexpr Instr const* BASE_TABLE = &INSTR_TABLE[BASE_OFFSET];
static constexpr Instr const* SPECIAL_TABLE = &INSTR_TABLE[SPECIAL_OFFSET];
static constexpr Instr const* REGIMM_TABLE = &INSTR_TABLE[REGIMM_OFFSET];



/*
    MIPS has a uniform encoding where everything are just flat indexes (i.e the instruction bits are contiguous) in the same place for every opcode
    with no weird encoding behavior with registers (this would likely prove tricky on something like RISC-V)

    therefore a simple table's lookup can be employed, naively this would be nested,
    We could opt for a flat table however, 
    because REGIMM makes a giant flat decoding table infeasible as it's instr bits dont 
    overlap with FUNCT meaing the mask would need to be atleast 17 bits on ARM32 it only needs to be 12

    however as the instr bits are contigous (rather than shotgunned across the opcode) 
    an inital decoding table to shift and mask the correct bits and provide the final encoding table directly
    can be used, this does mean that base opcodes have to go through essentially a self refernced table
    but its a worthwhile tradeoff to speed up the other opcodes
*/

struct Decode
{
    u32 shift;
    u32 mask;
    u32 offset;
};


static constexpr u32 REGIMM_SHIFT = 16;
static constexpr u32 SPECIAL_SHIFT = 0;
static constexpr u32 BASE_SHIFT = 26;

static constexpr Decode BASE_DECODE_TABLE[INSTR_TYPE_MASK + 1] =
{
    {SPECIAL_SHIFT,FUNCT_MASK,SPECIAL_OFFSET}, //0b000'000
    {REGIMM_SHIFT,REGIMM_MASK,REGIMM_OFFSET}, //0b000'001
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b000'010
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b000'011
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b000'100
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b000'101
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b000'110
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b000'111
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b001'000
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b001'001
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b001'010
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b001'011
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b001'100
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b001'101
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b001'110
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b001'111
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b010'000
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b010'001
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b010'010
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b010'011
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b010'100
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b010'101
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b010'110
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b010'111
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b011'000
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b011'001
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b011'010
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b011'011
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b011'100
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b011'101
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b011'110
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b011'111
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b100'000
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b100'001
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b100'010
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b100'011
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b100'100
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b100'101
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b100'110
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b100'111
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b101'000
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b101'001
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b101'010
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b101'011
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b101'100
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b101'101
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b101'110
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b101'111
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b110'000
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b110'001
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b110'010
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b110'011
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b110'100
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b110'101
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b110'110
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b110'111
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b111'000
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b111'001
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b111'010
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b111'011
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b111'100
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b111'101
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b111'110
    {BASE_SHIFT,INSTR_TYPE_MASK,BASE_OFFSET}, //0b111'111
};


enum class instr_class
{
    base,
    special,
    special2,
    special3,
    regimm,
    cop0,
    cop1,
    cop2,
    cop1x,
};


static constexpr u32 INSTR_CLASS_SIZE = u32(instr_class::cop1x) + 1;

static const char* INSTR_CLASS_NAMES[INSTR_CLASS_SIZE] = 
{
    "base",
    "special",
    "regimm",
    "cop0",
    "cop1",
    "cop2",
    "cop1x",
};




instr_class class_from_opcode(const Opcode& opcode)
{
    UNUSED(INSTR_CLASS_NAMES);

    const u32 type = get_opcode_type(opcode.op);

    switch(type)
    {
        case 0b000'000: return instr_class::special;


        case 0b010'000: return instr_class::cop0;
        case 0b010'001: return instr_class::cop1;
        case 0b010'010: return instr_class::cop2;
        case 0b010'011: return instr_class::cop1x;

        case 0b000'001: return instr_class::regimm;
        

        default: return instr_class::base;
    }
}



// NOTE: old decoding method kept around for comparsion
const Instr* decode_instr_chained(const Opcode& opcode, u32 version)
{
    const u32 type = get_opcode_type(opcode.op);
    const Instr* instr = &INSTR_TABLE[type];

    // opcode not supported on this version of the architecture
    if(instr->version > version)
    {
        return VER_UNKNOWN;
    }

    if(instr->chain)
    {
        return instr->chain(opcode,version);
    }

    return instr;    
}

u32 calc_base_table_offset(const Opcode& opcode)
{
    const u32 type = get_opcode_type(opcode.op);
    const auto decode = BASE_DECODE_TABLE[type];

    const u32 table_offset = (opcode.op >> decode.shift) & decode.mask;

    return decode.offset + table_offset;
}

const Instr* decode_instr(const Opcode& opcode, u32 version)
{
    const u32 offset = calc_base_table_offset(opcode);
    const Instr* instr = &INSTR_TABLE[offset];

    // opcode not supported on this version of the architecture
    if(instr->version > version)
    {
        return VER_UNKNOWN;
    }

    if(instr->chain)
    {
        return instr->chain(opcode,version);
    }

    return instr;
}

u32 instr_idx(const Opcode& opcode, u32 version)
{
    const Instr* instr = decode_instr(opcode,version);

    return instr - &INSTR_TABLE[0];
}

Opcode make_opcode(const u32 op)
{
    Opcode opcode;

    opcode.op = op;
    opcode.rd = (op >> 11) & REG_MASK;
    opcode.rt = (op >> 16) & REG_MASK;
    opcode.rs = (op >> 21) & REG_MASK;
    opcode.imm = (op  >> 0) & 0xffff;

    return opcode;
}




const Instr* decode_special(const Opcode& opcode,u32 version)
{
    const u32 idx = (opcode.op >> SPECIAL_SHIFT) & FUNCT_MASK;

    const Instr* instr = &SPECIAL_TABLE[idx];

    if(instr->chain)
    {
        return instr->chain(opcode,version); 
    }

    return instr;
}

const Instr* decode_regimm(const Opcode& opcode,u32 version)
{
    const u32 idx = (opcode.op >> REGIMM_SHIFT) & REGIMM_MASK;

    const Instr* instr = &REGIMM_TABLE[idx];

    if(instr->chain)
    {
        return instr->chain(opcode,version); 
    }

    return instr;
}

static constexpr u32 C0_BIT = 25;
static constexpr u32 BC = 0b01'000; 

static constexpr u32 COP0_RS_SHIFT = 21;

u32 calc_cop0_table_offset(const Opcode& opcode)
{
    // NOTE: we probably could defer this futher at the top but only chain
    // if we hit BC or C0, and get instant access to the COP0_RS opcodes
    // but im not 100% sure on this encoding yet as ive never written a decoder for it 

    
    // we should probably revist this after we have looked at cop1 (which is worth optmising?)

    // TODO: do we need to check that the zero's exist for this?
    if(is_set(opcode.op,C0_BIT))
    {
        const u32 type = opcode.op & COP0_FUNCT_MASK;
        return type + COP0_FUNCT_OFFSET;
    }

    const u32 type = opcode.rs;

    // TODO: handle this
    if(type == BC)
    {
        assert(false);
    }

    else
    {
        return type + COP0_RS_OFFSET;
    }    
}

const Instr* decode_cop0(const Opcode& opcode, u32 version)
{
    UNUSED(version);

    const u32 offset = calc_cop0_table_offset(opcode);
    return &INSTR_TABLE[offset];
}



static constexpr Decode COP1_DECODE_TABLE[COP1_RS_MASK + 1] =
{
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b000'00
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b000'01
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b000'10
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b000'11
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b001'00
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b001'01
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b001'10
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b001'11

    {COP1_BC_SHIFT,COP1_BC_MASK,COP1_BC_OFFSET}, //0b010'00
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b010'01
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b010'10
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b010'11
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b011'00
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b011'01
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b011'10
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b011'11

    {COP1_FMT_SHIFT,COP1_FMT_MASK,COP1_FMT_S_OFFSET}, //0b100'00
    {COP1_FMT_SHIFT,COP1_FMT_MASK,COP1_FMT_D_OFFSET}, //0b100'01
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b100'10
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b100'11
    {COP1_FMT_SHIFT,COP1_FMT_MASK,COP1_FMT_W_OFFSET}, //0b101'00
    {COP1_FMT_SHIFT,COP1_FMT_MASK,COP1_FMT_L_OFFSET}, //0b101'01
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b101'10
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b101'11

    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b110'00
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b110'01
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b110'10
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b110'11
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b111'00
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b111'01
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b111'10
    {COP1_RS_SHIFT,COP1_RS_MASK,COP1_RS_OFFSET}, //0b111'11
};


u32 calc_cop1_table_offset(const Opcode& opcode)
{
    const u32 type = opcode.rs;
    const auto decode = COP1_DECODE_TABLE[type];

    const u32 table_offset = (opcode.op >> decode.shift) & decode.mask;

    return decode.offset + table_offset;
}

const Instr* decode_cop1(const Opcode& opcode, u32 version)
{
    UNUSED(version);

    const u32 offset = calc_cop1_table_offset(opcode);
    return &INSTR_TABLE[offset];
}

}