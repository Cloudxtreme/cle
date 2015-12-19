#include <fstream>
#include <string>

#include "ansi.hpp"
#include "config.hpp"
#include "crypt.hpp"
#include "args.hpp"
#include "io.hpp"
#include "util.hpp"

using IO::print;
using IO::printc;

using std::ifstream;
using std::ofstream;
using std::string;

int main(int argv, char** argc)
{
    if (parseArgs(argv, argc)){
        return Config::EXIT_NORMAL;
    }

    Util::init();

    string key = entry();
    if (key.empty()){
        printc("no key provided!\n", ANSI_RED);
        print("run cle --help for more information\n");
        return Config::EXIT_NO_ENTRY;
    }

    printc("cle " + Config::vn + "\n", ANSI_BLUE);

    if (verbose()){
        print("opening entry " + entry() + "\n");             
    }

    print("enter passphrase > ");
    string pass = IO::readPass();
    
    unsigned char* hash = new unsigned char[32];
    Util::fileHash((pass + key).c_str(), pass.size() + key.size(), hash);
    string path = Util::hexstr(hash, 32);

    if (verbose()){
        print("key hash:\n");
        print(path + "\n");
    }

    auto file = IO::readFile(path);
    if (file.fail()){
        print("key does not exist under passphrase.\n");
        if (IO::prompt("create it? [Y/n] > ") == "Y"){
            IO::newKey(path); 
            Crypt crypt(const_cast<char*>(pass.c_str()), pass.size());
            crypt.encrypt(path, path);
        } else{
            print("not creating key.\n");
        }
    } else{
        printc("entry for " + key + "\n\n", ANSI_BLUE);
        unsigned char* salt = Util::readSalt(path);
        Crypt crypt(const_cast<char*>(pass.c_str()), pass.size(), salt);
        crypt.decrypt(path, path);
    }
    
    return Config::EXIT_NORMAL;
}
