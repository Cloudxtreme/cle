#include "util.hpp"

#include <sstream>
#include <stdlib.h>
#include <time.h>

#include "ansi.hpp"
#include "config.hpp"
#include "crypt.hpp"
#include "io.hpp"

using std::string;

////////////////////////////////////
// Util initilization, seed random 
void Util::init()
{
    srand(time(nullptr));
}

////////////////////////////
// return a random integer
int Util::randInt()
{
    return rand();
}

///////////////////////////
// generate a random salt
unsigned char* Util::randSalt()
{
    unsigned char* salt = new unsigned char[8];
    for (unsigned i = 0; i < 8; i++){
        salt[i] = (unsigned char) randInt();
    }
    return salt;
}

//////////////////////////////////
// fill an array with random data
void Util::wipeArray(unsigned char* array, unsigned len)
{
    for (unsigned i = 0; i < len; i++){
        array[i] = (unsigned char) randInt();
    }
}

///////////////////////////////////////////////
// hash a string using SHA256 for HASH_ROUNDS
bool Util::fileHash(const char* str, unsigned strlen, unsigned char* out)
{
    for (unsigned i = 0; i < Config::HASH_ROUNDS; i++){
        if (!Crypt::sha256((unsigned char*) str, strlen, 
                           (unsigned char*) out)){
            IO::printc("sha256 hash failed!\n", ANSI_RED);          
            return false;
        }
    }
    return true;
}

////////////////////////////////////////////////
// convert an array of bytes into a hex string
std::string Util::hexstr(unsigned char* data, unsigned len)
{
    std::stringstream ss;
    for (unsigned i = 0; i < len; i++)
    {
        ss << std::hex << (short) data[i];
    }
    return ss.str();
}

////////////////////////////////////////////
// read in the salt from an encrypted file
unsigned char* Util::readSalt(string path)
{
    unsigned char* salt = new unsigned char[8];
    auto vec = IO::readBytes(path);
    for (unsigned i = 0; i < 8; i++){
        salt[i] = vec.at(Config::saltText.size() + i);
    }
    return salt;
}
