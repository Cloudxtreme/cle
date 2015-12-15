#ifndef IO_
#define IO_

#include <fstream>
#include <string>

namespace IO
{
    void print();
    void print(std::string str);
    void printc(std::string str, std::string color);

    std::string readPass();

    std::ifstream readFile(std::string path);

    std::string prompt(std::string prompt_);

    void newKey(std::string path);
}

#endif
