#ifndef _GRAPHICS_HPP_
#define _GRAPHICS_HPP_

#include "SDL.hpp"
#include <stdint.h>
#include <string>

class Graphics
{
public:
    static void startUp(const char * window_title = "UNTITLED",
                        uint16_t window_width = 720,
                        uint16_t window_height = 480,
                        const char * icon_path = NULL);
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

    SDL_Texture * loadTexture(const char * img_path);
    void drawTexture(SDL_Texture * texture, SDL_Rect * drawing_area);

private:
    static Graphics * _instance;
    static bool _started_up;

    SDL_Surface * loadImage(const char * img_path) const;

    static void throw_sdl_exception(const char * msg);
    static void throw_img_exception(const char * msg);

    Graphics(const char * window_title, uint16_t window_width, uint16_t window_height, const char * icon_path);
    ~Graphics();
    SDL_Window * _window;
    SDL_Renderer * _renderer;
};

#endif