#include "VisualComponent.hpp"

VisualComponent::VisualComponent():
_parent(nullptr),
_children(),
_texture(nullptr),
_body({0,0,0,0}),
_is_hide(false)
{

}

VisualComponent::~VisualComponent()
{

}

void VisualComponent::setParent(VisualComponent * parent)
{
    _parent = parent;
}

VisualComponent * VisualComponent::getParent()
{
    return _parent;
}

void VisualComponent::addChild(VisualComponent * child)
{
    for (auto e : _children) {
        if (e == child)
            return;
    }
    _children.push_back(child);
}

std::vector<VisualComponent *> VisualComponent::getChildren() const
{
    return _children;
}

void VisualComponent::hide()
{
    _is_hide = true;
}

void VisualComponent::show()
{
    _is_hide = false;
}

bool VisualComponent::isHide() const
{
    return _is_hide;
}

void VisualComponent::setTexture(SDL_Texture * texture)
{
    _texture = texture;
}

SDL_Texture * VisualComponent::getTexture()
{
    return _texture;
}

SDL_Rect VisualComponent::getGlobalBody() const
{
    if (_parent == nullptr)
        return _body;
   
    return {getGlobalX(), getGlobalY(), getWidth(), getHeight()};
}

SDL_Rect VisualComponent::getRelativeBody() const
{
    return _body;
}

int32_t VisualComponent::getGlobalX() const
{
    return (_parent == nullptr ? _body.x : _body.x + _parent->getGlobalX());
}

int32_t VisualComponent::getRelativeX() const
{
    return _body.x;
}

void VisualComponent::setGlobalX(int32_t x)
{
    if (_parent == nullptr)
        _body.x = x;
    else
        _body.x = x - _parent->getGlobalX();
}

void VisualComponent::setRelativeX(int32_t x)
{
    _body.x = x;
}

int32_t VisualComponent::getGlobalY() const
{
    return _parent == nullptr ? _body.y : _body.y + _parent->getGlobalY();
}

int32_t VisualComponent::getRelativeY() const
{
    return _body.y;
}

void VisualComponent::setGlobalY(int32_t y)
{
    if (_parent == nullptr)
        _body.y = y;
    else
        _body.y = y - _parent->getGlobalY();
}

void VisualComponent::setRelativeY(int32_t y)
{
    _body.y = y;
}

int32_t VisualComponent::getWidth() const
{
    return _body.w;
}

void VisualComponent::setWidth(int32_t width)
{
    _body.w = width;
}

int32_t VisualComponent::getHeight() const
{
    return _body.h;
}

void VisualComponent::setHeight(int32_t height)
{
    _body.h = height;
}
