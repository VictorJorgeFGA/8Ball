#include "Graphics.hpp"
#include "SDL.hpp"
#include <stdexcept>
#include <iostream>

Graphics * Graphics::_instance = NULL;
bool Graphics::_started_up = false;

void Graphics::startUp(const char * window_title, uint16_t window_width, uint16_t window_height, const char * icon_path)
{
    if (_started_up)
        return;

    _started_up = true;
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
        throw_sdl_exception("Unable to initialize SDL video subsystem.");

    int img_flags = (IMG_INIT_JPG | IMG_INIT_PNG);
    if (IMG_Init(img_flags) != img_flags)
        throw_img_exception("Unable to initialize PNG or JPG image system");

    _instance = new Graphics(window_title, window_width, window_height, icon_path);
}

void Graphics::shutDown()
{
    _started_up = false;
    delete _instance;
    SDL_Quit();
}

Graphics * Graphics::getInstance()
{
    startUp();
    return _instance;
}

void Graphics::clearScreen()
{
    setDrawColor(0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);
}

void Graphics::updateScreen()
{
    SDL_RenderPresent(_renderer);
}

void Graphics::setDrawColor(uint8_t r, uint8_t g, uint8_t b)
{
    SDL_SetRenderDrawColor(_renderer, r, g, b, 0xFF);
}

void Graphics::drawRectangle(const SDL_Rect * rectangle)
{
    SDL_RenderFillRect(_renderer, rectangle);
}

void Graphics::hideCursor() const
{
    SDL_ShowCursor(SDL_DISABLE);
}

void Graphics::showCursor() const
{
    SDL_ShowCursor(SDL_ENABLE);
}

void Graphics::maximizeWindow()
{
    SDL_MaximizeWindow(_window);
}

void Graphics::minimizeWindow()
{
    SDL_MinimizeWindow(_window);
}

void Graphics::setFullScreenMode()
{
    if (SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN) != 0)
        throw_sdl_exception("Unable to set full screen mode");
}

void Graphics::setWindowedMode()
{
    if (SDL_SetWindowFullscreen(_window, 0) != 0)
        throw_sdl_exception("Unable to set windowed mode");
}

uint16_t Graphics::getWindowWidth() const
{
    int _w, _h;
    SDL_GetWindowSize(_window, &_w, &_h);
    return uint16_t(_w);
}

uint16_t Graphics::getWindowHeight() const
{
    int _w, _h;
    SDL_GetWindowSize(_window, &_w, &_h);
    return uint16_t(_h);
}

SDL_Surface * Graphics::loadImage(const char * img_path) const
{
    SDL_Surface * image = IMG_Load(img_path);
    if (image == NULL) {
        std::cerr << "Unable to load the image " << img_path << ". Error: " << IMG_GetError() << std::endl;
        throw std::runtime_error("Graphics Exception");
    }
    return image;
}

void Graphics::throw_sdl_exception(const char * msg)
{
    std::cerr << msg << " Error: " << SDL_GetError() << std::endl;
    throw std::runtime_error("Graphics Exception");
}

void Graphics::throw_img_exception(const char * msg)
{
    std::cerr << msg << " Error: " << IMG_GetError() << std::endl;
    throw std::runtime_error("Graphics Exception");
}

Graphics::Graphics(const char * window_title, uint16_t window_width, uint16_t window_height, const char * icon_path)
{
    _window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
    if (_window == NULL)
        throw_sdl_exception("Unable to create SDL_window.");

    if (icon_path != NULL) {
        SDL_Surface * icon = loadImage(icon_path);
        SDL_SetWindowIcon(_window, icon);
        SDL_FreeSurface(icon);
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL)
        throw_sdl_exception("Unable to create SDL_renderer.");

    setDrawColor(0xFF, 0xFF, 0xFF);
    clearScreen();
}

Graphics::~Graphics()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}