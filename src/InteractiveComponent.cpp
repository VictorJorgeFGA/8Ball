#include "InteractiveComponent.hpp"

std::vector<InteractiveComponent *> InteractiveComponent::_components {};
InteractiveComponent * InteractiveComponent::_selected_component;

void InteractiveComponent::processMouseButtonDown(SDL_Point cursor_coordinates)
{
    for (auto component : _components) {
        if (SDL_PointInRect(&cursor_coordinates, &component->_hitbox) == SDL_TRUE) {
            component->_initial_dragging_position = cursor_coordinates;
            _selected_component = component;
        }
    }
}

void InteractiveComponent::processMouseMotion(SDL_Point cursor_coordinates)
{
    if (_selected_component == nullptr || _selected_component->isTied())
        return;

    int32_t delta_x = SDL_abs(cursor_coordinates.x - _selected_component->_initial_dragging_position.x);
    int32_t delta_y = SDL_abs(cursor_coordinates.y - _selected_component->_initial_dragging_position.y);
    
    if (delta_x > 2 || delta_y > 2)
        _selected_component->reactToDragging({delta_x, delta_y});
}

void InteractiveComponent::processMouseButtonUp(SDL_Point cursor_coordinates)
{
    if (_selected_component == nullptr)
        return;

    int32_t delta_x = SDL_abs(cursor_coordinates.x - _selected_component->_initial_dragging_position.x);
    int32_t delta_y = SDL_abs(cursor_coordinates.y - _selected_component->_initial_dragging_position.y);

    if (delta_x <= 2 || delta_y <= 2)
        _selected_component->reactToClick(cursor_coordinates);

    _selected_component = nullptr;
}

void InteractiveComponent::lineUpHitboxAndTexture()
{
    setGlobalX(getHitboxX());
    setGlobalY(getHitboxY());
}

SDL_Rect InteractiveComponent::getHitbox() const
{
    return _hitbox;
}

int32_t InteractiveComponent::getHitboxWidth() const
{
    return _hitbox.w;
}

int32_t InteractiveComponent::getHitboxHeight() const
{
    return _hitbox.h;
}

int32_t InteractiveComponent::getHitboxX() const
{
    return _hitbox.x;
}

int32_t InteractiveComponent::getHitboxY() const
{
    return _hitbox.y;
}

void InteractiveComponent::setHitbox(SDL_Rect hitbox)
{
    _hitbox = hitbox;
}

void InteractiveComponent::setHitboxWidth(int32_t width)
{
    _hitbox.w = width;
}

void InteractiveComponent::setHitboxHeight(int32_t height)
{
    _hitbox.h = height;
}

void InteractiveComponent::setHitboxX(int32_t x)
{
    _hitbox.x = x;
}

void InteractiveComponent::setHitboxY(int32_t y)
{
    _hitbox.y = y;
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

void InteractiveComponent::syncTextureAndHitbox()
{
    _sync_texture_and_hitbox = true;
}

void InteractiveComponent::unsyncTextureAndHitbox()
{
    _sync_texture_and_hitbox = false;
}

bool InteractiveComponent::textureAndHitboxAreSync() const
{
    return _sync_texture_and_hitbox;
}

InteractiveComponent::InteractiveComponent()
{
    setParent(getScreenObject());
}

InteractiveComponent::~InteractiveComponent()
{
    
}

virtual void InteractiveComponent::reactToClick(SDL_Point cursor_cordinates)
{

}

virtual void InteractiveComponent::reactToDragging(SDL_Point dragging_vector)
{
    setHitboxX(dragging_vector.x + getHitboxX());
    setHitboxY(dragging_vector.y + getHitboxY());

    if (textureAndHitboxAreSync())
        lineUpHitboxAndTexture();
}