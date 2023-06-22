#pragma once
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <set>
#include <unordered_map>
#include <string_view>
#include <format>
#include <iterator>
#include <iostream>


namespace beyond_all_repair
{

// we dont have std::print yet
// so make a wrapper
template<typename... Args>
inline void print(const char* fmt, Args... args)
{
    printf("%s",std::vformat(fmt, std::make_format_args(args...)).c_str());
}
}