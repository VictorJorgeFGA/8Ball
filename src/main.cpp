#include "test.hpp"
#include "GeneralSystem.hpp"
#include <iostream>
#include <ios>

//#define TEST

Button * button;

void grow()
{
    std::cout << "Button pressed" << std::endl;
    button->setWidth(button->getWidth()+6);
    button->setGlobalX(button->getGlobalX()-3);
    button->setHeight(button->getHeight()+6);
    button->setGlobalY(button->getGlobalY()-3);
}

int main(int argc, char * argv[])
{
#ifdef TEST
    Test::runTest();
    
#else
    GeneralSystem::INIT_SUBSYSTEMS(true);
    std::cout.tie(0);

    button = Button::newButton("Button test");
    button->setClickReaction(grow);
    button->untie();
    button->setRelativeX(20);
    button->setRelativeY(20);

    SDL_Event event;
    bool run = true;
    while (run) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                run = false;
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int32_t x, y;
                SDL_GetMouseState(&x, &y);
                InteractiveComponent::processMouseButtonDown({x,y});
            }
            else if (event.type == SDL_MOUSEMOTION) {
                int32_t x, y;
                SDL_GetMouseState(&x, &y);
                InteractiveComponent::processMouseMotion({x,y});
            }
            else if (event.type == SDL_MOUSEBUTTONUP) {
                int32_t x, y;
                SDL_GetMouseState(&x, &y);
                InteractiveComponent::processMouseButtonUp({x,y});
            }
        }
        VisualComponent::drawComponents();
        SDL_Delay(16);
    }

    GeneralSystem::QUIT_SUBSYSTEMS();
#endif
    return 0;
}