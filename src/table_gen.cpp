namespace beyond_all_repair
{
void print_delmit(u32 i)
{
	if((i & 0b111) == 0b000)
	{
		putchar('\n');
	}
}

// used for generating a blank dummy table
void gen_mips_table()
{
	for(u32 i = 0; i <= 0b111'111; i++)
	{
		print_delmit(i);
		print("{{\"unknown opcode\",instr_type::reg,&unknown_mark,&unknown_disass}}, //0b{:03b}'{:03b}\n",(i >> 3) & 0b111,(i >> 0) & 0b111);
	}

	for(u32 i = 0; i <= 0b111'111; i++)
	{
		print_delmit(i);
		print("{{26,INSTR_TYPE_MASK,BASE_TABLE}}, //0b{:03b}'{:03b}\n",(i >> 3) & 0b111,(i >> 0) & 0b111);
	}

	for(u32 i = 0; i <= 0b111'111; i++)
	{
		print_delmit(i);
		print("{{\"unknown opcode\",instr_type::reg,&unknown_mark,&unknown_disass_special}}, //0b{:03b}'{:03b}\n",(i >> 3) & 0b111,(i >> 0) & 0b111);
	}


	for(u32 i = 0; i <= 0b111'11; i++)
	{
		print_delmit(i);
		print("{{\"unknown opcode\",instr_type::reg,&unknown_mark,&unknown_disass_regimm}}, //0b{:03b}'{:02b}\n",(i >> 2) & 0b111,(i >> 0) & 0b11);
	}
}
}