#ifndef _TEST_HPP_
#define _TEST_HPP_

#include <string>

class Test
{
public:
    static void runTest();

private:
    static void graphicsTest();
    static void timerTest();
    static void assetsManagerTest();
    static void visualComponentTest();
    static void interactiveComponentTest();
    static void soundManagerTest();
    static void physicsTest();

    static const std::string COMPONENT_TEST_MSG;
    static const std::string FUNCTIONALITY_TEST_MSG;
};

#endif