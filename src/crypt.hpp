#ifndef CRYPT_
#define CRYPT_

#include <openssl/evp.h> 

class Crypt
{
private:
    EVP_CIPHER_CTX context; 

public:
    Crypt(char* passphrase);

    static bool sha256(unsigned char* text, unsigned len,
                       unsigned char* out);
};

#endif
