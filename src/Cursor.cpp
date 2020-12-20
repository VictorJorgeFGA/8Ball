#include "Cursor.hpp"
#include "AssetsManager.hpp"
#include "SDL.hpp"

int32_t Cursor::_cursor_side = 35;
Cursor::CursorType Cursor::_cursor_type = Cursor::NORMAL_SELECT;
std::vector<SolidImage *> Cursor::_cursors;

void Cursor::startUp()
{
    SDL_ShowCursor(SDL_DISABLE);

    _cursors.push_back(SolidImage::newSolidImage("cursor_normal_select.png", _cursor_side, _cursor_side));
    
    _cursors.push_back(SolidImage::newSolidImage("cursor_link_select.png", _cursor_side, _cursor_side));
    _cursors.back()->hide();
    
    _cursors.push_back(SolidImage::newSolidImage("cursor_unavailable.png", _cursor_side, _cursor_side));
    _cursors.back()->hide();
    
    _cursors.push_back(SolidImage::newSolidImage("cursor_text_select.png", _cursor_side, _cursor_side));
    _cursors.back()->hide();
    
    _cursors.push_back(SolidImage::newSolidImage("cursor_move.png", _cursor_side, _cursor_side));
    _cursors.back()->hide();
    
    _cursors.push_back(SolidImage::newSolidImage("cursor_precision_select.png", _cursor_side, _cursor_side));
    _cursors.back()->hide();
}

void Cursor::setCursorType(CursorType cursor_type)
{
    _cursors[int32_t(_cursor_type)]->hide();
    _cursor_type = cursor_type;
    _cursors[int32_t(_cursor_type)]->show();
    updateTexturePosition();
}

void Cursor::drawCursor()
{    
    updateTexturePosition();
    _cursors[int32_t(_cursor_type)]->draw();
}

void Cursor::updateTexturePosition()
{
    int32_t x, y;
    SDL_GetMouseState(&x, &y);

    if (_cursor_type == Cursor::MOVE || _cursor_type == Cursor::PRECISION_SELECT) {
        _cursors[int32_t(_cursor_type)]->setGlobalX(x-(_cursor_side/2));
        _cursors[int32_t(_cursor_type)]->setGlobalY(y-(_cursor_side/2));
    } else {
        _cursors[int32_t(_cursor_type)]->setGlobalX(x);
        _cursors[int32_t(_cursor_type)]->setGlobalY(y);
    }
}