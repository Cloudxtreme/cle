#include "args.hpp"

#include <string>

#include "ansi.hpp"
#include "config.hpp"
#include "io.hpp"
#include "util.hpp"

using IO::print;
using IO::printc;

using std::string;

////////////////////////
// internal functions //
////////////////////////
bool arg(char* argc, string str);

void printUsage();
void printVersion();

void renameKey();
void deleteKey();

////////////////////////
// internal variables //
////////////////////////
bool colors_ = Config::colors;
bool verbose_ = false;

string entry_;

////////////////////////////////////////////////
// parse and act on program arguments
// returns 0 if the program should continue,
// or a non-zero value if it should stop
int parseArgs(int argv, char** argc)
{
    if (argv < 2) {
        return 0;
    }

    entry_ = string(argc[1]);

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

        else if (arg(argc[i], "-v") || arg(argc[i], "--verbose")){
            verbose_ = true;
        }

        else if (arg(argc[i], "-r") || arg(argc[i], "--rename")){
            renameKey();
            return 1;
        }

        else if (arg(argc[i], "-d") || arg(argc[i] , "--delete")){
            deleteKey(); 
            return 1;
        }

        else if (i != 1){
            printc("unknown argument '" + string(argc[i]) + "'\n", 
                    ANSI_RED);
            print("run cle --help for more information\n");
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

////////////////////////////////////////
// return if verbose output is enabled
bool verbose()
{
    return verbose_;
}

//////////////////////////////////////////////////
// return the entry name provided to the program
string entry()
{
    return entry_;
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
    print("-d, --delete -> delete the given key\n");  
    print("-nc, --no-color -> disable colorized output\n");
    print("-r, --rename -> rename the given key\n");
    print("-v, --verbose   -> enable verbose output\n");
    print();
}

//////////////////////////////////////
// print program version information
void printVersion()
{
    printc("cle " + Config::vn + "\n", ANSI_BLUE);
    printc("(C) 2015 phillip-h\n", ANSI_BLUE);
}

////////////////////////////////
// interactivly rename the key
void renameKey()
{
    Util::hideText();
    print("enter passphrase > ");
    string pass = IO::readPass();
    Util::showText();
    print();

    string key = entry();
    unsigned char* hash = new unsigned char[32];
    Util::fileHash((pass + key).c_str(), pass.size() + key.size(), hash);
    string path = Util::hexstr(hash, 32);

    auto file = IO::readFile(path);
    if (file.fail()){ 
        printc("key does not exist under passphrase.\n", ANSI_RED);
        return;
    }

    if (IO::prompt("rename key? [Y/n] > ") != "Y"){
        print("not renaming.\n");
        return;
    }

    string newKey = IO::prompt("enter new key name > ");
    unsigned char* newHash = new unsigned char[32];
    Util::fileHash((pass + newKey).c_str(), pass.size() + newKey.size(),
                   newHash);
    string newPath = Util::hexstr(newHash, 32);

    if (verbose()){
        print("new key hash:\n");  
        print(newPath + "\n");
    }

    auto temp = IO::readFile(newPath);
    if (!temp.fail()){
        printc("new key name already exists!\n", ANSI_RED);
        print("maybe remove it first?\n");
        return;
    }
    IO::writeBytes(IO::readBytes(path), newPath);
    print("key renamed.\n");
    
    IO::deleteFile(false, path);
}

//////////////////////////////////////
// prompt the user for confirmation,
// then delete the key
void deleteKey()
{
    Util::hideText();
    print("enter passphrase > ");
    string pass = IO::readPass();
    Util::showText();
    print();

    string key = entry();
    unsigned char* hash = new unsigned char[32];
    Util::fileHash((pass + key).c_str(), pass.size() + key.size(), hash);
    string path = Util::hexstr(hash, 32);
    
    auto file = IO::readFile(path);
    if (file.fail()){ 
        printc("key does not exist under passphrase.\n", ANSI_RED);
        return;
    }

    IO::deleteFile(true, path);
}
