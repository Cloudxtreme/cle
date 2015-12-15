#include "io.hpp"

#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <vector>

#include "ansi.hpp"
#include "args.hpp"
#include "config.hpp"

using std::cout;
using std::string;
using std::vector;

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

//////////////////////////////////////////
// read a passphrase in from the console
string IO::readPass()
{
    string pass;
    std::getline(std::cin, pass);
    return pass;
}

////////////////////////////////////////////////////
// open a file with the given path relative to the
// save directory
std::ifstream IO::readFile(string path)
{
    path = string(getenv("HOME")) + "/" + Config::FILE_DIR + "/" + path;
    return std::ifstream(path);
}

//////////////////////////////////////////////////
// print the provided prompt to the string, then
// read and return the user's input
string IO::prompt(string prompt_)
{
    print(prompt_);
    string in;
    std::getline(std::cin, in);
    return in;
}

//////////////////////////////////////////
// create a new key and write it to disk
void IO::newKey(string path)
{
    string password;
    string email;
    vector<string> comment;
    
    print();
    printc("new key\n", ANSI_BLUE);
    password = prompt("password > ");
    email = prompt("email > ");

    print("comment (two newlines to finish):\n");
    while (true){
        comment.push_back(prompt(""));
        if (comment.size() > 1){
            if (comment.at(comment.size() - 1).empty()){
                if (comment.at(comment.size() - 2).empty()){
                    break;
                }
            }
        }
    }
    comment = vector<string>(&comment[0], &comment[comment.size() - 2]);

    path = string(getenv("HOME")) + "/" + Config::FILE_DIR + "/" + path;
    std::ofstream file(path);
    
    if (file.fail()){
        mkdir((string(getenv("HOME")) + "/" + Config::FILE_DIR).c_str(),
              S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        file = std::ofstream(path);
        if (file.fail()){
            printc("failed to open output file!\n", ANSI_RED);
        }
        return;
    }
    
    file << password << "\n";
    file << email << "\n";
    for (unsigned i = 0; i < comment.size(); i++){
        file << comment.at(i) << "\n";
    }
}
