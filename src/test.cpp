#include "Everything.hpp"
#include "test.hpp"
#include <iostream>
#include <vector>
#include <functional>

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
    
    Graphics::startUp("Test", 720, 480, "assets/default_icon.png");
    Graphics * graphics = Graphics::getInstance(); 
    SDL_Rect rectangle {graphics->getWindowWidth() / 2 - 25, graphics->getWindowHeight() / 2 - 25, 50, 50};
    
    SDL_Texture * texture_example = graphics->loadTexture("assets/default_icon.png");
    TTF_Font * font = graphics->loadFont("assets/sony_sketch.ttf", 64);
    SDL_Texture * text = graphics->createTextTexture(font, "Test");

    std::vector<std::function<void()>> micro_tests {
        [&]() {
            graphics->setDrawColor(0x0, 0xFF, 0x0);
            graphics->drawRectangle(&rectangle);
        },
        [&]() {
            graphics->setDrawColor(0x0, 0x0, 0xFF);
            graphics->drawRectangle(&rectangle);
        },
        [&]() {
            graphics->setDrawColor(0xFF, 0x0, 0x0);
            graphics->drawRectangle(&rectangle);
        },
        [&]() {
            graphics->setDrawColor(0xFF, 0xFF, 0x0);
            graphics->drawRectangle(&rectangle);
        },
        [&]() {
            graphics->drawTexture(texture_example, &rectangle);
        },
        [&]() {
            graphics->drawTexture(text, NULL);
        }
    };
    
    for (auto test : micro_tests) {
        int32_t initial_ticks = SDL_GetTicks();
        while (int32_t(SDL_GetTicks()) - initial_ticks <= 1000) {
            graphics->clearScreen();
            test();
            graphics->updateScreen();
            SDL_Delay(16);
        }
    }

    graphics->unloadTexture(text);
    graphics->unloadTexture(texture_example);
    graphics->unloadFont(font);
    Graphics::shutDown();
    std::cout << '\t' << "Ok" << std::endl;
}