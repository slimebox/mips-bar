namespace beyond_all_repair
{
	struct Config
	{
		b32 disassemble = false;
		b32 print_external = false;
		b32 print_addr = false;
		b32 print_opcodes = false;
		b32 gen = false;
		b32 linear = false;
	};

	Config parse_config(const char* flags)
	{
		Config config;

		while(*flags)
		{
			auto c = *flags;

			switch(c)
			{
				case 'd': config.disassemble = true; break;
				case 'g': config.gen = true; break;
				case 'a': config.print_addr = true; break;
				case 'o': config.print_opcodes = true; break;
				case 'e': config.print_external = true; break;
				case 'l': config.linear = true; break;
				default: break;
			}

			flags++;
		}

		return config;
	}
}