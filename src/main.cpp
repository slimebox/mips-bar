
#include <lib.h>
#include <destoer.cpp>

using namespace destoer;

#include <config.cpp>
#include <disass.cpp>


int main(int argc, char* argv[])
{
	// TODO: add a proper config but just keep a simple read in the whole ELF
	// and disassemble the entire thing
	if(argc < 2 || *argv[1] != '-')
	{
		print("{}: unknown command, exiting.\n",argv[0]);
		return 0;
	}

	auto config = parse_config(argv[1]);

	if(config.gen)
	{
		gen_mips_table();
		return 0;
	}

	
	else
	{
		std::vector<u8> buf;
		if(argc >= 3)
		{
			if(read_bin(argv[2],buf))
			{
				print("could not open file: {}\n",argv[2]);
				exit(1);
			}
		}

		if(config.disassemble)
		{
			if(argc == 3)
			{
				auto program = disass_elf(buf);

				// finally disassemble the program
				disassemble_console(program,config);
			}

			else
			{
				print("usage:{} -d <file to disassemble>\n",argv[0]);
			}
		}
		
	}

	return 0;
}
