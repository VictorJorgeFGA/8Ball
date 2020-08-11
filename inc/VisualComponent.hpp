#ifndef _VISUAL_COMPONENT_HPP_
#define _VISUAL_COMPONENT_HPP_

#include <SDL2/SDL.h>
#include <vector>

class VisualComponent
{
public:
    VisualComponent();
    ~VisualComponent();

    void setParent(VisualComponent * parent);
    VisualComponent * getParent();

    void addChild(VisualComponent * child);
    std::vector<VisualComponent *> getChildren() const;

    void hide();
    void show();
    bool isHide() const;

    void setTexture(SDL_Texture * texture);
    SDL_Texture * getTexture();

    SDL_Rect getGlobalBody() const;
    SDL_Rect getRelativeBody() const;

    int32_t getGlobalX() const;
    int32_t getRelativeX() const;
    void setGlobalX(int32_t x);
    void setRelativeX(int32_t x);

    int32_t getGlobalY() const;
    int32_t getRelativeY() const;
    void setGlobalY(int32_t y);
    void setRelativeY(int32_t y);

    int32_t getWidth() const;
    void setWidth(int32_t width);

    int32_t getHeight() const;
    void setHeight(int32_t height);

private:

    VisualComponent * _parent;
    std::vector<VisualComponent *> _children;
    SDL_Texture * _texture;
    SDL_Rect _body;
    bool _is_hide;
};

#endif