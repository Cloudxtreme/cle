#include "args.hpp"

#include <iostream>
#include <string>

#include "ansi.hpp"

using std::cout;
using std::string;

////////////////////////
// internal functions //
////////////////////////
bool arg(char* argc, string str);

void printUsage();
void printVersion();

////////////////////////////////////////////////
// parse and act on program arguments
// returns 0 if the program should continue,
// or a non-zero value if it should stop
int parseArgs(int argv, char** argc)
{
    if (argv < 2) {
        return 0;
    }

    for (int i = 1; i < argv; i++)
    {
        if (arg(argc[i], "-h") || arg(argc[i], "--help")){
            printUsage();
            return 1;
        }

        else if (arg(argc[i], "-version") || arg(argc[i], "--version")){
            printVersion();
            return 1;
        }

        else{
            cout << ANSI_RED;
            cout << "unknown argument '" << argc[i] << "'\n";
            cout << ANSI_RESET;
            cout << "run pass --help for more information\n";
        }
    }

    return 0;
}

//////////////////////////////////////////
// returns true if the C-str matches the 
// string
bool arg(char* argc, string str)
{
    return string(str) == argc;
}

/////////////////////////////////////
// print program usage information
void printUsage()
{

}

//////////////////////////////////////
// print program version information
void printVersion()
{
    cout << ANSI_BLUE;
    cout << "cle v0.1\n";
    cout << "(C) 2015 phillip-h\n";
    cout << ANSI_RESET;
}
