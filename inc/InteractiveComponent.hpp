#ifndef _INTERACTIVECOMPONENT_HPP_
#define _INTERACTIVECOMPONENT_HPP_

#include "SDL.hpp"
#include "VisualComponent.hpp"

#include <vector>
#include <functional>
#include <string>

// Allow click detection, dragging events and state changes
class InteractiveComponent : public VisualComponent
{
public:
    static void processMouseButtonDown(const SDL_Point & cursor_coordinates);
    static void processMouseMotion(const SDL_Point & cursor_coordinates);
    static void processMouseButtonUp(const SDL_Point & cursor_coordinates);

    void tie();
    void untie();
    bool isTied() const;

    void activate();
    void deactivate();
    bool isActive() const;

private:
    static InteractiveComponent * getComponentByClickCoordinates(const SDL_Point & coordinates);

    static std::vector<InteractiveComponent *> _components;
    static InteractiveComponent * _selected_component;

    SDL_Point _initial_dragging_position;
    SDL_Point _initial_hitbox_position;
    bool _can_drag;
    bool _is_active;

protected:
    InteractiveComponent();
    virtual ~InteractiveComponent();

    SDL_Point getInitialMousePositionDuringDragging() const;
    SDL_Point getInitialHitboxPositionDuringDragging() const;

    //The reaction when mouse button is pressed on the component
    virtual void reactToPressing(const SDL_Point & cursor_coordinates);

    //The reaction when mouse button is released after a previous
    //pressing on the component
    virtual void reactToReleasing(const SDL_Point & cursor_coordinates);

    //The reaction when the component takes a mouse click
    virtual void reactToClick(const SDL_Point & cursor_coordinates);

    //The reaction when the component is being dragged
    virtual void reactToDragging(const SDL_Point & cursor_coordinates);
};

#endif