#include "AssetsManager.hpp"
#include "Graphics.hpp"
#include "SDL.hpp"
#include <string>
#include <iostream>

AssetsManager * AssetsManager::_instance = nullptr;

AssetsManager * AssetsManager::getInstance()
{
    if (_instance == nullptr)
        _instance = new AssetsManager();
    return _instance;
}

void AssetsManager::shutDown()
{
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

SDL_Texture * AssetsManager::getTexture(const std::string & img_name)
{
    std::string texture_key = img_name;

    if (_textures.count(texture_key) < 1) {
        Graphics * graphics = Graphics::getInstance();
        std::string img_path = "assets/" + img_name;
        
        _textures[texture_key] = graphics->loadTexture(img_path);
    }
    return _textures[texture_key];
}

SDL_Texture * AssetsManager::getTextTexture(const std::string & font_name, uint8_t font_size, const std::string & text, SDL_Color color)
{
    std::string text_texture_key = font_name + std::to_string(font_size) + text;
    text_texture_key.append(std::to_string(color.r) + std::to_string(color.g) + std::to_string(color.b));
    

    if (_textures.count(text_texture_key) < 1) {
        TTF_Font * font = getFont(font_name, font_size);
        Graphics * graphics = Graphics::getInstance();
        _textures[text_texture_key] = graphics->createTextTexture(font, text, color);
    }
    return _textures[text_texture_key];
}

TTF_Font * AssetsManager::getFont(const std::string & font_name, uint8_t font_size)
{
    std::string font_key = font_name + std::to_string(font_size);

    if (_fonts.count(font_key) < 1) {
        Graphics * graphics = Graphics::getInstance();
        _fonts[font_key] = graphics->loadFont("assets/" + font_name, font_size);
    }
    return _fonts[font_key];
}

AssetsManager::AssetsManager()
{

}

AssetsManager::~AssetsManager()
{
    Graphics * graphics = Graphics::getInstance();
    for (auto texture : _textures) {
        std::cout << "\tDestroying texture " << texture.first << std::endl;
        graphics->unloadTexture(texture.second);
    }
    for (auto font : _fonts) {
        std::cout << "\tDestroying font " << font.first << std::endl;
        graphics->unloadFont(font.second);
    }
}