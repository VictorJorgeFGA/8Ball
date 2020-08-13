#ifndef _INTERACTIVECOMPONENT_HPP_
#define _INTERACTIVECOMPONENT_HPP_

#include "SDL.hpp"
#include "VisualComponent.hpp"
#include <vector>
#include <functional>

// Allow click detection, dragging events and state changes
class InteractiveComponent : public VisualComponent
{
public:
    static void processMouseButtonDown(SDL_Point cursor_coordinates);
    static void processMouseMotion(SDL_Point cursor_coordinates);
    static void processMouseButtonUp(SDL_Point cursor_coordinates);

    void lineUpHitboxAndTexture();

    SDL_Rect getHitbox() const;
    int32_t getHitboxWidth() const;
    int32_t getHitboxHeight() const;
    int32_t getHitboxX() const;
    int32_t getHitboxY() const;

    void setHitbox(SDL_Rect hitbox);
    void setHitboxWidth(int32_t width);
    void setHitboxHeight(int32_t height);
    void setHitboxX(int32_t x);
    void setHitboxY(int32_t y);

    void tie();
    void untie();
    bool isTied() const;

    void syncTextureAndHitbox();
    void unsyncTextureAndHitbox();
    bool textureAndHitboxAreSync() const;

private:
    static std::vector<InteractiveComponent *> _components;
    static InteractiveComponent * _selected_component;

    SDL_Rect _hitbox;
    SDL_Point _initial_dragging_position;
    bool _can_drag;
    bool _sync_texture_and_hitbox;

protected:
    InteractiveComponent();
    ~InteractiveComponent();

    virtual void reactToClick(SDL_Point cursor_coordinates);
    virtual void reactToDragging(SDL_Point dragging_vector);
};

#endif