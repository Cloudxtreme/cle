#include "util.hpp"

#include <iostream>

#include "config.hpp"

using std::cout;
using std::string;

void Util::print(string str)
{
    printc(str, ""):
}

void Util::printc(string str, string color)
{
    if (colors){
        cout << color;
    }
    cout << str;
}
