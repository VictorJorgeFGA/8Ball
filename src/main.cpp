#include "test.hpp"
#include "GeneralSystem.hpp"
#include <iostream>
#include <ios>

#define TEST

int main(int argc, char * argv[])
{
#ifdef TEST
    Test::runTest();
#else
    
#endif
    return 0;
}