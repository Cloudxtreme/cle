#include "crypt.hpp"

#include <openssl/sha.h>

#include "ansi.hpp"
#include "io.hpp"

using IO::print;
using IO::printc;

bool Crypt::sha256(unsigned char* text, unsigned len,
                   unsigned char* out)
{
    SHA256_CTX context;
    
    if (!SHA256_Init(&context)){
        printc("failed to create SHA256 context!\n", ANSI_RED);        
        return false;
    }

    if (!SHA256_Update(&context, text, len)){
        printc("failed to update SHA256 context!\n", ANSI_RED);
        return false;
    }

    if (!SHA256_Final(out, &context)){
        printc("SHA256_final returned null pointer!\n", ANSI_RED);
        return false;
    }

    return true;
}
