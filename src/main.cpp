#include "test.hpp"
#include "GeneralSystem.hpp"
#include <iostream>
#include <ios>

//#define TEST

int main(int argc, char * argv[])
{
#ifdef TEST
    Test::runTest();
    
#else
    GeneralSystem::INIT_SUBSYSTEMS(true);
    std::cout.tie(0);

    Button * button = Button::newButton(
        SolidImage::newSolidImage("background_test.png", 150, 100),
        SolidText::newSolidText("BUTTON TEST", "sony_sketch.ttf", 18, {0xff, 0xff, 0xff, 0xff})
    );
    button->setClickReaction([] {
        std::cout << "Button pressed" << std::endl;
        SDL_Event e;
        e.type = SDL_QUIT;
        SDL_PushEvent(&e);
    });

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