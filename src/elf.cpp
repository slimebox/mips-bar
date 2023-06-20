#include <disass.h>


struct SectionHeader
{
    // size of each entry
    u64 size = 0;

    u64 offset = 0;
    u64 end = 0;

    u64 vaddr = 0;
};

struct Symbol
{
    std::string name;
    u64 addr = 0;
    u64 size = 0;
};


static constexpr u32 STT_FUNC = 2;

static constexpr u32 PROGBITS_SECTION = 1;
static constexpr u32 SYMBOL_SECTION = 2;
static constexpr u32 STRTAB_SECTION = 3;
static constexpr u32 DYNSYM_SECTION = 11;

static constexpr u32 SHF_EXECINSTR = 4;

// https://www.cr0.org/paper/mips.elf.external.resolution.txt
static constexpr u32 OFFSET_GP_GOT = 0x7ff0;

void disassemble_program(Program& program);

SectionHeader read_section_header(const u8* section_header, b32 is_64, b32 is_be)
{
    SectionHeader header;

    header.offset = is_64? read<u64>(&section_header[0x18],is_be) : read<u32>(&section_header[0x10],is_be);

    const u64 size =  is_64? read<u64>(&section_header[0x20],is_be) : read<u32>(&section_header[0x14],is_be);
    header.end = header.offset + size;

    header.size = is_64? read<u64>(&section_header[0x38],is_be) : read<u32>(&section_header[0x24],is_be);

    header.vaddr = is_64? read<u64>(&section_header[0x10],is_be) : read<u32>(&section_header[0xc],is_be);

    return header;
}


// how to read program out of a elf bin
b32 read_elf(Program& program, u64 addr, void* out, u32 size)
{
    Section section;
    if(!lookup_section(program,addr,&section))
    {
        return false;
    }

    // transform the address
    addr -= section.base;

    if(addr + size >= section.size)
    {
        return false;
    }

    // read out the data
    memcpy(out,&section.ptr[addr],size);
    

    return true;
}

void read_sym_table(std::map<u64,Symbol> &symbols,const u8* sym_tab, const u8* sym_tab_end, 
    const char* string_table, const char* string_table_end, b32 is_64, b32 is_be, u32 size)
{
    // pull every symbol that is a function
    while(sym_tab != sym_tab_end)
    {
        Symbol sym;

        
        const u8 info = is_64? sym_tab[0x4] : sym_tab[0xc];
        sym.addr = is_64? read<u64>(&sym_tab[0x8],is_be) : read<u32>(&sym_tab[0x4],is_be);


        if((info & 0xf) == STT_FUNC && sym.addr != 0)
        {
            const u32 idx = read<u32>(&sym_tab[0],is_be);
        
            if(&string_table[idx] > string_table_end)
            {
                print("String idx is out of range {:x} : {:x} : {:x}\n",idx,string_table_end - string_table,sym.addr);
                exit(1);
            }


            // pull it with our own string count to make sure its in bounds
            const char* str = &string_table[idx];
            while(*str && str != string_table_end)
            {
                str++;
            }

            const u32 len = str - &string_table[idx];
            sym.name = std::string(&string_table[idx],len);
            sym.size = is_64? read<u64>(&sym_tab[0x10],is_be) : read<u32>(&sym_tab[0x8],is_be);


            if(sym.size == 0)
            {
                sym.size = SIZE_UNK;
            }


            symbols[sym.addr] = sym;
        }

        sym_tab += size;
    }
}

std::pair<SectionHeader,b32> scan_header(const u8* section_header, const char* name,const char* expected_name, 
    b32 is_64, b32 is_be, u32 str_len, u64 size)
{
    b32 found = false;
    SectionHeader header;

    // check the table entry by name to make sure we have the correct one
    if(str_len != 0 && strncmp(name,expected_name,str_len) == 0)
    {
        header = read_section_header(section_header,is_64,is_be);

        if(header.end > size)
        {
            print("Elf file is too small for string table header entry {} {} : {}\n",expected_name,header.end,size);
            exit(1);                
        }

        found = true;
    }

    return std::pair<SectionHeader,b32>(header,found);   
}

// TODO: get a rough set of programs to test this on (a compiler test suite along with a couple unix tools is probably the easiest to come by)

Program disass_elf(std::vector<u8>& buf)
{
    // check we atleast have a valid elf headers worth of bytes to read out
    // https://man7.org/linux/man-pages/man5/elf.5.html
    if(buf.size() <= 0x40)
    {
        print("Elf file is too small expected at least 0x40 bytes got {:x}",buf.size());
        exit(1);
    }


    // Parse out the headers of the ELF file
    // magic number & assembly checker
    // get section header offset

    const u32 magic = read<u32>(&buf[0],false);

    // 0x7f, "ELF"
    static constexpr u32 ELF_MAGIC = 0x464c457f;

    if(magic != ELF_MAGIC)
    {
        print("not a valid elf file: expected magic {:8x} != {:8x}",magic,ELF_MAGIC);
        exit(1);
    }


    const b32 is_64 = buf[4] == 2;
    const b32 is_be = buf[5] == 2;

    const u64 entry_point = is_64? read<u64>(&buf[0x18],is_be) : read<u32>(&buf[0x18],is_be);


    // grab program header entry size, number, offset so we can scan it for the symbol table
    const u16 shentsize = read<u16>(&buf[is_64? 0x3a : 0x2E],is_be);
    const u16 shnum = read<u16>(&buf[is_64? 0x3c : 0x30],is_be);
    const u64 shoff = is_64? read<u64>(&buf[0x28],is_be) : read<u32>(&buf[0x20],is_be);

    // section names
    const u32 shstrndx = read<u16>(&buf[is_64? 0x3E : 0x32],is_be);
    

    const u64 sh_end = shoff + (shnum * shentsize);

    // check the file actually has the right size for this number of entries
    if(sh_end  > buf.size())
    {
        print("Elf file is too small for section header entries {:x} {:x} {:x} {:x} : {:x}\n",sh_end,shentsize,shnum,shoff,buf.size());
        exit(1);
    }

    const u8* section_header = &buf[shoff];
    const u8* section_header_end = &buf[sh_end];


    b32 symbol_table_found = false;
    SectionHeader sym_header;

    SectionHeader string_header;
    b32 string_table_found = false;

    b32 dyn_symbol_table_found = false;
    SectionHeader dyn_sym_header;

    SectionHeader dyn_string_header;
    b32 dyn_string_table_found = false;

    std::vector<Section> sections;
    u64 gp = 0;

    // pull the section name header so that we can get the correct string table later
    const u8* names_header_ptr = &section_header[shstrndx * shentsize];

    if(&names_header_ptr[shentsize] > &buf[buf.size()])
    {
        print("Elf file is too small for section name entry {:x} : {:x}\n",shstrndx,buf.size());
        exit(1);        
    }

    SectionHeader names_header = read_section_header(names_header_ptr,is_64,is_be);
    const char* section_names = (char*)&buf[names_header.offset];
    const char* section_names_end = (char*)&buf[names_header.end];

    // scan the section header table for the symbool table
    while(section_header != section_header_end)
    {
        const u32 name = read<u32>(&section_header[0x0],is_be);

        if(&section_names[name] >= section_names_end)
        {
            print("String idx for section names out of range {} : {}\n",name,buf.size());
            exit(1);                               
        }

        const char* str = &section_names[name];
        const char* header_name = str;

        while(*str && str != section_names_end)
        {
            str++;
        }

        const u32 len = str - header_name;


        const u32 type = read<u32>(&section_header[0x4],is_be);
        //const u32 flags = read<u32>(&section_header[0x8],is_be);

        // symbol table found
        if(type == SYMBOL_SECTION && !symbol_table_found)
        {
            std::tie(sym_header,symbol_table_found) = scan_header(section_header,header_name,".symtab",is_64,is_be,len,buf.size());
        }

        // str tables
        else if(type == STRTAB_SECTION)
        {
            if(!string_table_found)
            {
                std::tie(string_header,string_table_found) = scan_header(section_header,header_name,".strtab",is_64,is_be,len,buf.size());
            }

            if(!dyn_string_table_found)
            {
                std::tie(dyn_string_header,dyn_string_table_found) = scan_header(section_header,header_name,".dynstr",is_64,is_be,len,buf.size());
            }
        }

        // dynamic symbol table
        else if(type == DYNSYM_SECTION && !dyn_symbol_table_found)
        {
            std::tie(dyn_sym_header,dyn_symbol_table_found) = scan_header(section_header,header_name,".dynsym",is_64,is_be,len,buf.size()); 
        }


        // any text section
        else if(type == PROGBITS_SECTION)
        {
            // rip any other header we can get our hands on
            auto text_header = read_section_header(section_header,is_64,is_be);

            if(text_header.end > buf.size())
            {
                print("Elf file is too small for string table header entry {} {} : {}\n",header_name,text_header.end,buf.size());
                exit(1);                
            }

            if(text_header.offset < buf.size())
            {
                // NOTE: we currently overapproximate the size
                auto section = make_section(text_header.vaddr,buf.size() - text_header.offset,&buf[text_header.offset]);
                sections.push_back(section);
            }

            if(strncmp(header_name,".got",len) == 0)
            {
                gp = OFFSET_GP_GOT + text_header.vaddr;
            }                  
        }


        section_header += shentsize;
    }



    std::map<u64,Symbol> symbols;

    // symtab
    if(symbol_table_found && string_table_found)
    {
        const char* string_table = (char*)&buf[string_header.offset];
        const char* string_table_end = (char*)&buf[string_header.end];

        const u8* sym_tab = &buf[sym_header.offset];
        const u8* sym_tab_end = &buf[sym_header.end];

        read_sym_table(symbols,sym_tab,sym_tab_end,string_table,string_table_end,is_64,is_be,sym_header.size);
    }

    // dynsymtab
    if(dyn_symbol_table_found && dyn_string_table_found)
    {
        const char* string_table = (char*)&buf[dyn_string_header.offset];
        const char* string_table_end = (char*)&buf[dyn_string_header.end];

        const u8* sym_tab = &buf[dyn_sym_header.offset];
        const u8* sym_tab_end = &buf[dyn_sym_header.end];

        read_sym_table(symbols,sym_tab,sym_tab_end,string_table,string_table_end,is_64,is_be,dyn_sym_header.size);
    }

    if(!symbols.size())
    {
        print("Error no symbols to process is this binary stripped?\n");
        exit(1);
    }




    // disassemble all the sections
    Program program = make_program(entry_point,is_be,read_elf,sections);

    // TODO: replace this with proper emulation
    program.gp = gp;


    // add each function to begin marking
#if 1
    // NOTE: we do this in revese order so when we pop address of the stack
    // we are parsing the program in order
    for(auto it = symbols.rbegin(); it != symbols.rend(); ++it)
    {
        auto& sym = it->second;
        add_func(program,sym.addr,PC_UNK,sym.size,sym.name,sym.size == SIZE_UNK);
    }
    
#else 

    // with no symbols
    add_func(program,entry_point,PC_UNK,SIZE_UNK,"start");

#endif

    disassemble_program(program);

    return program;
}