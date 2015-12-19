#ifndef UTIL_
#define UTIL_

#include <string>

namespace Util
{
    void init();
    
    int randInt();
    
    unsigned char* randSalt();
    
    void wipeArray(unsigned char* array, unsigned len);

    bool fileHash(const char* str, unsigned strlen, unsigned char* out); 

    std::string hexstr(unsigned char* data, unsigned len);

    unsigned char* readSalt(std::string path);
}

#endif
