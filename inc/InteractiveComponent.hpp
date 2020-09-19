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
    static void startUp();

    static void processMouseButtonDown(const SDL_Point & cursor_coordinates);
    static void processMouseMotion(const SDL_Point & cursor_coordinates);
    static void processMouseButtonUp(const SDL_Point & cursor_coordinates);
    static void processKeyPressing(int32_t sdl_keysym);

    void tie();
    void untie();
    bool isTied() const;

    void activate();
    void deactivate();
    bool isActive() const;

private:
    static InteractiveComponent * getComponentByClickCoordinates(const SDL_Point & coordinates);

    static InteractiveComponent * NEUTRAL_COMPONENT;
    static const std::string ERROR_MSG;
    
    static std::vector<InteractiveComponent *> _components;
    static InteractiveComponent * _selected_component;
    static InteractiveComponent * _overlapped_component;
    static InteractiveComponent * _focused_component;


    SDL_Point _initial_dragging_position;
    SDL_Point _initial_hitbox_position;
    bool _can_drag;
    bool _is_active;

protected:
    InteractiveComponent();
    virtual ~InteractiveComponent();

    //The reaction when mouse button is pressed on the component
    virtual void reactToPressing(const SDL_Point & cursor_coordinates);

    //The reaction when mouse button is released after a previous
    //pressing on the component
    virtual void reactToReleasing(const SDL_Point & cursor_coordinates);

    //The reaction when the component takes a mouse click
    virtual void reactToClick(const SDL_Point & cursor_coordinates);

    //The reaction when the component is being dragged
    virtual void reactToDragging(const SDL_Point & cursor_coordinates);

    // The reaction when the mouse cursor is overlapping the component (with no clicks or pressings)
    virtual void reactToCursorOverlappingComponent(const SDL_Point & cursor_coordinates);

    // The reaction when the mouse cursor stops overlapping the component (with no clicks or pressings)
    virtual void reactToCursorStopedOverlappingComponent(const SDL_Point & cursor_coordinates);

    // The reaction when a key from keyboard is pressed
    virtual void reactToKeyPressing(int32_t sdl_keysym);
};

#endif