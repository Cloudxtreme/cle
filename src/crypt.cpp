#include "crypt.hpp"

#include <iostream>
#include <openssl/sha.h>
#include <vector>

#include "ansi.hpp"
#include "config.hpp"
#include "io.hpp"
#include "util.hpp"

using namespace Config;

using IO::print;
using IO::printc;
using std::string;
using std::vector;

Crypt::Crypt(char* passphrase, unsigned passLen)
: Crypt(passphrase, passLen, Util::randSalt()) 
{}

Crypt::Crypt(char* passphrase, unsigned passLen, unsigned char* salt)
{
    unsigned char* encKey = new unsigned char[32];
    unsigned char* encIV = new unsigned char[32];

    salt_ = salt;
    
    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt, 
                   (unsigned char*) passphrase, passLen, 12, 
                   encKey, encIV);

    EVP_CIPHER_CTX_init(&dContext);
    EVP_DecryptInit_ex(&dContext, EVP_aes_256_cbc(), NULL, 
                       encKey, encIV);
    EVP_CIPHER_CTX_init(&eContext);
    EVP_EncryptInit_ex(&eContext, EVP_aes_256_cbc(), NULL, 
                       encKey, encIV);
    
    Util::wipeArray(encKey, 32);
    Util::wipeArray(encIV, 32);
    Util::wipeArray((unsigned char*) passphrase, passLen);
}

Crypt::~Crypt()
{
    EVP_CIPHER_CTX_cleanup(&dContext);
    EVP_CIPHER_CTX_cleanup(&eContext);
    Util::wipeArray(salt_, 8);
}

void Crypt::encrypt(string src, string dest)
{
    auto vec = IO::readBytes(src); 
    for (unsigned i = 0; i < 16; i++){
            vec.insert(vec.begin() + i, 0);
    }
    for (unsigned i = 0; i < checksumText.size(); i++){
        vec.insert(vec.begin() + i, checksumText.at(i));
    }
    
    unsigned len = vec.size();
    unsigned char* data = vec.data();

    int clen = len + 128;
    int flen = 0;
    unsigned char *newData = new unsigned char[clen];
    
    EVP_EncryptUpdate(&eContext, newData, &clen, data, len);
    EVP_EncryptFinal_ex(&eContext, newData + clen, &flen);

    len = clen + flen;
    auto outData = std::vector<unsigned char>(newData, newData + len);

    for (unsigned i = 0; i < 8; i++){
        outData.insert(outData.begin() + i, salt_[i]);
    }
    for (unsigned i = 0; i < saltText.size(); i++){
        outData.insert(outData.begin() + i, saltText.at(i));   
    }
    IO::writeBytes(outData, dest);
}

void Crypt::decrypt(string src, string dest)
{
    auto vec = IO::readBytes(src);
    unsigned start = saltText.size();
    if (vec.size() < start + 8){
        printc("data too small to contain salt!\n", ANSI_RED);
        print("the file may be corrupted!\n");
    } else{
        vec = vector<unsigned char>(vec.begin() + start + 8, vec.end());
    }
    
    unsigned len = vec.size();
    unsigned char* data = vec.data();

    int clen = len;
    int flen = 0;
    unsigned char *newData = new unsigned char[clen];

    EVP_DecryptUpdate(&dContext, newData, &clen, data, len);
    EVP_DecryptFinal(&dContext, newData + clen, &flen);

    len = clen + flen;
    vec = vector<unsigned char>(newData, newData + len);

    start = checksumText.size();
    if (vec.size() < start + 16){
        printc("data too small to contain checksum!\n", ANSI_RED);
        print("the file may be corrupt!\n");
    } else{
        for (unsigned i = 0; i < 16; i++){
            if (vec.at(start + i)){
                printc("failed to validate checksum!\n", ANSI_RED);
                print("the file may corrupt!\n");
                break;
            }
        }
        vec = vector<unsigned char>(vec.begin() + start + 16, vec.end());
    }
    
    for (unsigned i = 0; i < vec.size(); i++){
        std::cout << vec.at(i);
    }
    std::cout << "\n";
}

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
