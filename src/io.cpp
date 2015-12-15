#include "io.hpp"

#include <iostream>

#include "ansi.hpp"
#include "args.hpp"

using std::cout;
using std::string;

void IO::print()
{
    cout << "\n";
}

void IO::print(string str)
{
    printc(str, "");
}

void IO::printc(string str, string color)
{
    if (colors()){
        str = color + str + ANSI_RESET;
    }
    cout << str;
}
