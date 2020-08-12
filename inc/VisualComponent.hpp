#ifndef _VISUAL_COMPONENT_HPP_
#define _VISUAL_COMPONENT_HPP_

#include "Graphics.hpp"
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

    double getRotationAngle() const;
    void setRotationAngle(double rotation_angle);

private:
    static VisualComponent * SCREEN;
    static bool VERBOSE;
    static const std::string VERBOSE_MSG;
    static Graphics * graphics;

    void draw();

    void addChild(VisualComponent * child);
    void removeChild(VisualComponent * child);

    VisualComponent * _parent;
    std::vector<VisualComponent *> _children;
    SDL_Texture * _texture;
    SDL_Rect _body;
    bool _is_hide;
    double _rotation_angle;

protected:
    VisualComponent();
    ~VisualComponent();
};

#endif