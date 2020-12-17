#include "Cursor.hpp"
#include "AssetsManager.hpp"
#include "SDL.hpp"

int32_t Cursor::_x_alignment = 0;
int32_t Cursor::_y_alignment = 0;
SolidImage * Cursor::_cursor_texture = nullptr;
std::map<std::string, SolidImage *> Cursor::_available_textures;

std::string Cursor::LIGHT_CURSOR = "light_cursor.png";
std::string Cursor::DARK_CURSOR = "dark_cursor.png";

void Cursor::setCursorTexture(const std::string & texture_name, int32_t x_alignment, int32_t y_alignment)
{
    _x_alignment = x_alignment;
    _y_alignment = y_alignment;

    if (_cursor_texture != nullptr)
        _cursor_texture->hide();

    if (_available_textures.count(texture_name) < 1)
        _available_textures[texture_name] = SolidImage::newSolidImage(texture_name, 20, 20);

    _cursor_texture = _available_textures[texture_name];
    _cursor_texture->show();
    updateTexturePosition();
}

void Cursor::setXAlignment(int32_t x_alignment)
{
    _x_alignment = x_alignment;
}

void Cursor::setYAlignment(int32_t y_alignment)
{
    _y_alignment = y_alignment;
}

void Cursor::drawCursor()
{
    if (_cursor_texture == nullptr)
        return;
    
    updateTexturePosition();
    _cursor_texture->draw();
}

void Cursor::updateTexturePosition()
{
    if (_cursor_texture != nullptr) {
        int32_t cursor_x, cursor_y;
        SDL_GetMouseState(&cursor_x, &cursor_y);

        _cursor_texture->setGlobalX(cursor_x + _x_alignment);
        _cursor_texture->setGlobalY(cursor_y + _y_alignment);
    }
}