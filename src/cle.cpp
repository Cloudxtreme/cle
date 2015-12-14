#include "args.hpp"

int main(int argv, char** argc)
{
    if (parseArgs(argv, argc)){
        return 1;
    }
}
