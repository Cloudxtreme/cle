#ifndef CRYPT_
#define CRYPT_

#include <openssl/evp.h> 
#include <string>

class Crypt
{
private:
    EVP_CIPHER_CTX dContext;
    EVP_CIPHER_CTX eContext; 

    unsigned char* salt_;

public:
    Crypt(char* passphrase, unsigned passLen);
    Crypt(char* passphrase, unsigned passLen, unsigned char* salt);
    ~Crypt();

    void decrypt(std::string src, std::string dest);
    void encrypt(std::string src, std::string dest);

    static bool sha256(unsigned char* text, unsigned len,
                       unsigned char* out);
};

#endif
