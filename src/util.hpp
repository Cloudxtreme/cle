#ifndef UTIL_
#define UTIL_

#include <string>

namespace Util
{

    bool fileHash(const char* str, unsigned strlen, unsigned char* out); 

    std::string hexstr(unsigned char* data, unsigned len);
}

#endif
