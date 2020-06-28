#ifndef _GRAPHICS_HPP_
#define _GRAPHICS_HPP_

#include "SDL.hpp"
#include <stdint.h>

class Graphics
{
public:
    static void startUp(const char * window_title = "UNTITLED", uint16_t window_width = 720, uint16_t window_height = 480);
    static void shutDown();
    static Graphics * getInstance();

    void clearScreen();
    void updateScreen();
    void setDrawColor(uint8_t r, uint8_t g, uint8_t b);
    void drawRectangle(const SDL_Rect * rectangle);
    void hideCursor() const;
    void showCursor() const;
    void maximizeWindow();
    void minimizeWindow();
    void setFullScreenMode();
    void setWindowedMode();

    uint16_t getWindowWidth() const;
    uint16_t getWindowHeight() const;

private:
    static Graphics * _instance;
    static bool _started_up;

    static void throw_exception(const char * msg);

    Graphics(const char * window_title, uint16_t window_width, uint16_t window_height);
    ~Graphics();
    SDL_Window * _window;
    SDL_Renderer * _renderer;
};

#endif