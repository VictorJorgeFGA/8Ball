#ifndef _VISUAL_COMPONENT_HPP_
#define _VISUAL_COMPONENT_HPP_

#include <SDL2/SDL.h>
#include <vector>
#include <string>

class VisualComponent
{
public:
    static void setVerboseMode();

    static void startUp();
    static void shutDown();
    static void drawComponents();
    static VisualComponent * getScreenObject();

    static VisualComponent * newVisualComponent(SDL_Texture * texture = nullptr, int32_t relative_x = 0, int32_t relative_y = 0, int32_t width = 0, int32_t height = 0, VisualComponent * parent = SCREEN);

    void setParent(VisualComponent * new_parent);
    VisualComponent * getParent();

    std::vector<VisualComponent *> getChildren() const;
    int32_t countChildren() const;

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
    static VisualComponent * SCREEN;
    static bool VERBOSE;

    void draw();

    VisualComponent();
    ~VisualComponent();

    void addChild(VisualComponent * child);
    void removeChild(VisualComponent * child);

    VisualComponent * _parent;
    std::vector<VisualComponent *> _children;
    SDL_Texture * _texture;
    SDL_Rect _body;
    bool _is_hide;
};

#endif