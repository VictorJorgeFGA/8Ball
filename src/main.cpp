#include "test.hpp"
#include "Everything.hpp"

#define TEST

int main(int argc, char * argv[])
{
#ifdef TEST
    Test::runTest();
    
#else
    Graphics::startUp("8 Ball", 720, 480, "assets/default_icon.png");
    Graphics * gr = Graphics::getInstance();

    SDL_Event event;
    bool run = true;
    SDL_Rect rect {50, 50, 100, 100};
    while (run) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym)
                {
                case SDLK_h:
                    gr->hideCursor();
                    break;
                case SDLK_s:
                    gr->showCursor();
                    break;
                case SDLK_1:
                    gr->maximizeWindow();
                    break;
                case SDLK_2:
                    gr->minimizeWindow();
                    break;
                case SDLK_3:
                    gr->setFullScreenMode();
                    break;
                case SDLK_4:
                    gr->setWindowedMode();
                    break;
                }
            } else if (event.type == SDL_QUIT) {
                run = false;
            }
        }
        gr->clearScreen();
        gr->setDrawColor(0x0, 0x0, 0x0);
        gr->drawRectangle(&rect);
        gr->updateScreen();

        SDL_Delay(36);
    }

    Graphics::shutDown();

#endif
    return 0;
}