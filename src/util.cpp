#include "util.hpp"

#include <sstream>

#include "ansi.hpp"
#include "config.hpp"
#include "crypt.hpp"
#include "io.hpp"

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
