#include "VisualComponent.hpp"

VisualComponent::VisualComponent():
_parent(nullptr),
_texture(NULL),
_body({0,0,0,0})
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

void VisualComponent::setTexture(SDL_Texture * texture)
{
    _texture = texture;
}

SDL_Texture * VisualComponent::getTexture()
{
    return _texture;
}

SDL_Rect VisualComponent::getBody() const
{
    if (_parent == nullptr)
        return _body;
   
    return {getX(), getY(), getWidth(), getHeight()};
}
int32_t VisualComponent::getX() const
{
    return (_parent == nullptr ? _body.x : _body.x + _parent->getX());
}

void VisualComponent::setX(int32_t x)
{
    _body.x = x;
}

int32_t VisualComponent::getY() const
{
    return _parent == nullptr ? _body.y : _body.y + _parent->getY();
}

void VisualComponent::setY(int32_t y)
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
