namespace beyond_all_repair
{


void print_delmit(u32 i)
{
	if((i & 0b111) == 0b000)
	{
		putchar('\n');
	}
}


void gen_blank()
{
	for(u32 i = 0; i <= 0b111'111; i++)
	{
		print_delmit(i);
		//print("{{\"unknown_opcode\",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1}}, //0b{:03b}'{:03b}\n",(i >> 2) & 0b111,(i >> 0) & 0b11);
		print("{{\"unknown_opcode\",instr_type::unk,nullptr,&unknown_disass_cop0,MIPS1}}, //0b{:03b}'{:03b}\n",(i >> 3) & 0b111,(i >> 0) & 0b111);
	}	
}

void gen_mips_table()
{
	printf("#include <n64/cpu.h>\n");
	printf("namespace nintendo64\n");
	printf("{\n");

	printf("const INSTR_FUNC INSTR_TABLE_DEBUG[] = \n");
	printf("{\n");

	// gen a dummy table
	for(u32 i = 0; i < INSTR_TABLE_SIZE; i++)
	{
		if(INSTR_TABLE[i].version <= MIPS3)
		{
			if(is_mem_access(INSTR_TABLE[i].fmt) || INSTR_TABLE[i].fmt == instr_type::mips_class)
			{
				printf("\t&instr_%s<true>,\n",INSTR_TABLE[i].name);
			}

			else
			{
				// floating point func replace '.' with '_' for name
				if(strchr(INSTR_TABLE[i].name, '.'))
				{
					std::string name = INSTR_TABLE[i].name;

					for(auto& c : name)
					{
						if(c == '.')
						{
							c = '_';
						}
					}

					printf("\t&instr_%s,\n",name.c_str());
				}

				else
				{
					printf("\t&instr_%s,\n",INSTR_TABLE[i].name);
				}
			}
		}

		else
		{
			printf("\t&instr_unknown_opcode,\n");
		}
	}

	printf("};\n");


	printf("const INSTR_FUNC INSTR_TABLE_NO_DEBUG[] = \n");
	printf("{\n");

	// gen a dummy table
	for(u32 i = 0; i < INSTR_TABLE_SIZE; i++)
	{
		if(INSTR_TABLE[i].version <= MIPS3)
		{
			if(is_mem_access(INSTR_TABLE[i].fmt) || INSTR_TABLE[i].fmt == instr_type::mips_class)
			{
				printf("\t&instr_%s<false>,\n",INSTR_TABLE[i].name);
			}

			else
			{
				// floating point func replace '.' with '_' for name
				if(strchr(INSTR_TABLE[i].name, '.'))
				{
					std::string name = INSTR_TABLE[i].name;

					for(auto& c : name)
					{
						if(c == '.')
						{
							c = '_';
						}
					}

					printf("\t&instr_%s,\n",name.c_str());
				}

				else
				{
					printf("\t&instr_%s,\n",INSTR_TABLE[i].name);
				}
			}
		}

		else
		{
			printf("\t&instr_unknown_opcode,\n");
		}
	}

	printf("};\n");

	printf("}\n");
}
}