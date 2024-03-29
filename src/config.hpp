#ifndef CONFIG_
#define CONFIG_

#include <string>

// various global settings
namespace Config
{

// program version string
const std::string vn = "v0.2";

// default state of colorized output
const bool colors = true;

// number of SHA256 rounds used when hashing files
const int HASH_ROUNDS = 2048;

// location of files
const std::string FILE_DIR = ".cle";

// exit codes
const int EXIT_NORMAL = 0;
const int EXIT_NO_ENTRY = 1;

const std::string checksumText = "checksum_:";
const std::string saltText = "salted_:";

}
#endif
