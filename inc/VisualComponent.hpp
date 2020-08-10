#ifndef _VISUAL_COMPONENT_HPP_
#define _VISUAL_COMPONENT_HPP_

#include <SDL2/SDL.h>

class VisualComponent
{
public:
    VisualComponent();
    ~VisualComponent();

    void setParent(VisualComponent * parent);
    VisualComponent * getParent();

    void setTexture(SDL_Texture * texture);
    SDL_Texture * getTexture();

    SDL_Rect getBody() const;

    int32_t getX() const;
    void setX(int32_t x);

    int32_t getY() const;
    void setY(int32_t y);

    int32_t getWidth() const;
    void setWidth(int32_t width);

    int32_t getHeight() const;
    void setHeight(int32_t height);

private:

    VisualComponent * _parent;
    SDL_Texture * _texture;
    SDL_Rect _body;
};

#endif