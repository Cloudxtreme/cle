#ifndef ANSI
#define ANSI

// various ANSI escape codes for colorized output

// reset to normal state
const std::string ANSI_RESET = "\u001B[0m";

// "bright" colors
const std::string ANSI_BLACK = "\u001B[1;30m";
const std::string ANSI_RED = "\u001B[1;31m";
const std::string ANSI_GREEN = "\u001B[1;32m";
const std::string ANSI_YELLOW = "\u001B[1;33m";
const std::string ANSI_BLUE = "\u001B[1;34m";
const std::string ANSI_PURPLE = "\u001B[1;35m";
const std::string ANSI_CYAN = "\u001B[1;36m";
const std::string ANSI_WHITE = "\u001B[1;37m";

// "dull" colors
const std::string ANSI_DBLACK = "\u001B[0;30m";
const std::string ANSI_DRED = "\u001B[0;31m";
const std::string ANSI_DGREEN = "\u001B[0;32m";
const std::string ANSI_DYELLOW = "\u001B[0;33m";
const std::string ANSI_DBLUE = "\u001B[0;34m";
const std::string ANSI_DPURPLE = "\u001B[0;35m";
const std::string ANSI_DCYAN = "\u001B[0;36m";
const std::string ANSI_DWHITE = "\u001B[0;37m";

// background colors
const std::string ANSI_BLACK_B = "\u001B[1;340m";
const std::string ANSI_RED_B = "\u001B[1;41m";
const std::string ANSI_GREEN_B = "\u001B[1;42m";
const std::string ANSI_YELLOW_B = "\u001B[1;43m";
const std::string ANSI_BLUE_B = "\u001B[1;44m";
const std::string ANSI_PURPLE_B = "\u001B[1;45m";
const std::string ANSI_CYAN_B = "\u001B[1;46m";
const std::string ANSI_WHITE_B = "\u001B[1;47m";

#endif
