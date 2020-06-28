#include "Everything.hpp"
#include "test.hpp"
#include <iostream>

void Test::runTest()
{
    try {
        graphicsTest();
        std::cout << "\t\033[0;32mTests passed!\033[0m" << std::endl;
    }
    catch (std::runtime_error & e) {
        std::cerr << e.what() << std::endl;
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "\t\033[0;31mTests failed!\033[0m" << std::endl; 
    }
}

void Test::graphicsTest()
{
    std::cout << "Graphics tests:" << std::endl;
    
    Graphics::startUp("Test");

    Graphics * graphics = Graphics::getInstance(); 
    
    SDL_Rect rectangle {graphics->getWindowWidth() / 2 - 25, graphics->getWindowHeight() / 2 - 25, 50, 50};
    
    graphics->clearScreen();
    graphics->setDrawColor(0xFF, 0x0, 0x0);
    graphics->drawRectangle(&rectangle);
    graphics->updateScreen();
    SDL_Delay(1000);

    graphics->clearScreen();
    graphics->setDrawColor(0x0, 0xFF, 0x0);
    graphics->drawRectangle(&rectangle);
    graphics->updateScreen();
    SDL_Delay(1000);

    graphics->clearScreen();
    graphics->setDrawColor(0x0, 0x0, 0xFF);
    graphics->drawRectangle(&rectangle);
    graphics->updateScreen();
    SDL_Delay(1000);

    graphics->clearScreen();
    graphics->setDrawColor(0xFF, 0xFF, 0x0);
    graphics->drawRectangle(&rectangle);
    graphics->updateScreen();
    SDL_Delay(1000);

    graphics->clearScreen();
    graphics->setDrawColor(0xFF, 0x0, 0xFF);
    graphics->drawRectangle(&rectangle);
    graphics->updateScreen();
    SDL_Delay(1000);

    graphics->clearScreen();
    graphics->updateScreen();
    graphics->minimizeWindow();
    SDL_Delay(1000);

    graphics->maximizeWindow();
    graphics->clearScreen();
    graphics->updateScreen();
    SDL_Delay(2000);

    graphics->setFullScreenMode();
    graphics->clearScreen();
    graphics->updateScreen();
    SDL_Delay(2000);

    graphics->setWindowedMode();
    graphics->clearScreen();
    graphics->updateScreen();
    SDL_Delay(2000);

    graphics->hideCursor();
    SDL_Delay(3000);

    graphics->showCursor();
    SDL_Delay(1000);

    Graphics::shutDown();

    std::cout << '\t' << "Ok" << std::endl;
}