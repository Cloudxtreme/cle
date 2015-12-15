#include "args.hpp"

#include <string>

#include "ansi.hpp"
#include "config.hpp"
#include "io.hpp"

using IO::print;
using IO::printc;

using std::string;

////////////////////////
// internal functions //
////////////////////////
bool arg(char* argc, string str);

void printUsage();
void printVersion();

////////////////////////
// internal variables //
////////////////////////
bool colors_ = Config::colors;

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

        else if (arg(argc[i], "-nc") || arg(argc[i], "--no-color")){
            colors_ = false;
        }

        else if (i != 1){
            printc("unknown argument '" + string(argc[i]) + "'\n", 
                    ANSI_RED);
            print("run pass --help for more information\n");
        }
    }

    return 0;
}

//////////////////////////////////////////
// return if colorized output is enabled
bool colors()
{
    return colors_;
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
    printc("cle " + Config::vn + "\n", ANSI_BLUE);
    print();
    printc("syntax\n", ANSI_BLUE);
    printc("cle <key> [arguments]\n", ANSI_WHITE);
    print();
    printc("arguments\n", ANSI_BLUE);
    print("-h, --help          -> print usage and exit\n");
    print("-version, --version -> print version information and exit\n");
    print();
    print("-nc, --no-color -> disable colorized output\n");
    print();
}

//////////////////////////////////////
// print program version information
void printVersion()
{
    printc("cle " + Config::vn + "\n", ANSI_BLUE);
    printc("(C) 2015 phillip-h\n", ANSI_BLUE);
}
