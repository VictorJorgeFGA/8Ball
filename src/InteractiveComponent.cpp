#include "InteractiveComponent.hpp"
#include <iostream>

std::vector<InteractiveComponent *> InteractiveComponent::_components {};
InteractiveComponent * InteractiveComponent::_selected_component;

void InteractiveComponent::processMouseButtonDown(const SDL_Point & cursor_coordinates)
{
    if ((_selected_component = getComponentByClickCoordinates(cursor_coordinates)) == nullptr)
        return;

    _selected_component->_initial_dragging_position = cursor_coordinates;
    _selected_component->_initial_hitbox_position = {
        _selected_component->getGlobalX(),
        _selected_component->getGlobalY()
    };
    _selected_component->reactToPressing(cursor_coordinates);
}

void InteractiveComponent::processMouseMotion(const SDL_Point & cursor_coordinates)
{
    if (_selected_component == nullptr || _selected_component->isTied())
        return;

    int32_t delta_x = cursor_coordinates.x - _selected_component->_initial_dragging_position.x;
    int32_t delta_y = cursor_coordinates.y - _selected_component->_initial_dragging_position.y;
    
    if (SDL_abs(delta_x) > 2 || SDL_abs(delta_y) > 2) {
        _selected_component->setGlobalX(delta_x + _selected_component->_initial_hitbox_position.x);
        _selected_component->setGlobalY(delta_y + _selected_component->_initial_hitbox_position.y);
        _selected_component->reactToDragging(cursor_coordinates);
    }
}

void InteractiveComponent::processMouseButtonUp(const SDL_Point & cursor_coordinates)
{
    if (_selected_component == nullptr)
        return;

    int32_t delta_x = SDL_abs(cursor_coordinates.x - _selected_component->_initial_dragging_position.x);
    int32_t delta_y = SDL_abs(cursor_coordinates.y - _selected_component->_initial_dragging_position.y);

    if (delta_x <= 2 || delta_y <= 2)
        _selected_component->reactToClick(cursor_coordinates);

    _selected_component->reactToReleasing(cursor_coordinates);
    _selected_component = nullptr;
}

void InteractiveComponent::tie()
{
    _can_drag = true;
}

void InteractiveComponent::untie()
{
    _can_drag = false;
}

bool InteractiveComponent::isTied() const
{
    return _can_drag;
}

void InteractiveComponent::activate()
{
    _is_active = true;
}

void InteractiveComponent::deactivate()
{
    _is_active = false;
}

bool InteractiveComponent::isActive() const
{
    return _is_active;
}

InteractiveComponent * InteractiveComponent::getComponentByClickCoordinates(const SDL_Point & coordinates)
{
    for (auto component : _components)
        if (component->isActive() && SDL_PointInRect(&coordinates, component->getGlobalBodyReference()) == SDL_TRUE)
            return component;
    return nullptr;
}

InteractiveComponent::InteractiveComponent():
_initial_dragging_position({0,0}),
_initial_hitbox_position({0,0}),
_can_drag(true),
_is_active(true)
{
    setParent(getScreenObject());
    _components.push_back(this);
}

InteractiveComponent::~InteractiveComponent()
{

}

SDL_Point InteractiveComponent::getInitialMousePositionDuringDragging() const
{
    return _initial_dragging_position;
}

SDL_Point InteractiveComponent::getInitialHitboxPositionDuringDragging() const
{
    return _initial_hitbox_position;
}

void InteractiveComponent::reactToPressing(const SDL_Point & cursor_coordinates)
{

}

void InteractiveComponent::reactToReleasing(const SDL_Point & cursor_coordinates)
{

}

void InteractiveComponent::reactToClick(const SDL_Point & cursor_cordinates)
{

}

void InteractiveComponent::reactToDragging(const SDL_Point & cursor_coordinates)
{
    
}