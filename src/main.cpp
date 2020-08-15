#include "test.hpp"
#include "GeneralSystem.hpp"

#include <iostream>
#include <ios>

int main(int argc, char * argv[])
{
#ifdef TEST
    Test::runTest();
#else
    GeneralSystem::INIT_SUBSYSTEMS();
    RunningManager::getInstance()->runProgram();
    GeneralSystem::QUIT_SUBSYSTEMS();
#endif
    return 0;
}