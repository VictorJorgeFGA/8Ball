#ifndef _CURSOR_HPP_
#define _CURSOR_HPP_

#include "SolidImage.hpp"

#include <string>
#include <cstdint>
#include <map>

class Cursor
{
public:
    static std::string LIGHT_CURSOR;
    static std::string DARK_CURSOR;

    static void setCursorTexture(const std::string & texture_name, int32_t x_alignment = 0, int32_t y_alignment = 0);
    static void setXAlignment(int32_t x_alignment);
    static void setYAlignment(int32_t y_alignment);
    static void drawCursor();

private:
    Cursor();
    ~Cursor();

    static void updateTexturePosition();

    static int32_t _x_alignment;
    static int32_t _y_alignment;
    static SolidImage * _cursor_texture;
    static std::map<std::string, SolidImage *> _available_textures;

protected:

};

#endif