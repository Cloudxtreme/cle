#include "io.hpp"

#include <iostream>

#include "ansi.hpp"
#include "args.hpp"

using std::cout;
using std::string;

//////////////////////////////////
// print a new line to std::cout
void IO::print()
{
    cout << "\n";
}

/////////////////////////////////
// print a string to std::cout
void IO::print(string str)
{
    printc(str, "");
}

/////////////////////////////////////////////////
// print a string to std::cout
//
// if colorized output is enabled, the string
// is prefixed with the provided color code and
// postfixed with ANSI_RESET
void IO::printc(string str, string color)
{
    if (colors()){
        str = color + str + ANSI_RESET;
    }
    cout << str;
}
