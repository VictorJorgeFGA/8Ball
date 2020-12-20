#ifndef _CURSOR_HPP_
#define _CURSOR_HPP_

#include "SolidImage.hpp"

#include <cstdint>
#include <vector>

class Cursor
{
public:
    enum CursorType {
        // DEFAULT CURSOR
        NORMAL_SELECT = 0,
        // Used while hovering clickable components
        LINK_SELECT,
        // Used while hovering locked/forbidden components
        UNAVAILABLE,
        // Used while hovering editable text
        TEXT_SELECT,
        // Used while dragging components
        MOVE,
        // Used while aiming
        PRECISION_SELECT
    };

    static void startUp();
    static void setCursorType(CursorType cursor_type);
    static void drawCursor();

private:
    Cursor();
    ~Cursor();

    static void updateTexturePosition();

    static int32_t _cursor_side;
    static CursorType _cursor_type;
    static std::vector<SolidImage *> _cursors;

protected:

};

#endif