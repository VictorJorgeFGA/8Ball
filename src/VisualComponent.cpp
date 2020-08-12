#include "VisualComponent.hpp"
#include "Graphics.hpp"
#include <stdexcept>
#include <iostream>

VisualComponent * VisualComponent::SCREEN = nullptr;
bool VisualComponent::VERBOSE = false;

void VisualComponent::setVerboseMode()
{
    VERBOSE = true;
}

void VisualComponent::startUp()
{
    if (SCREEN == nullptr) {
        Graphics * g = Graphics::getInstance();
        SCREEN = newVisualComponent(nullptr, 0, 0, g->getWindowWidth(), g->getWindowHeight());
        SCREEN->_parent = nullptr;
    }
}

void VisualComponent::shutDown()
{
    delete SCREEN;
    SCREEN = nullptr;
}

void VisualComponent::drawComponents()
{
    if (SCREEN == nullptr)
        throw std::runtime_error("Attempt to draw VisualComponent objects before VisualComponent initialization");
    
    SCREEN->draw();
}

VisualComponent * VisualComponent::getScreenObject()
{
    if (SCREEN == nullptr)
        throw std::runtime_error("Attempt to get VisualComponent::SCREEN object before VisualComponent initialization");
    
    return SCREEN;
}

VisualComponent * VisualComponent::newVisualComponent(SDL_Texture * texture, int32_t relative_x, int32_t relative_y, int32_t width, int32_t height, VisualComponent * parent)
{
    VisualComponent * visual_component = new VisualComponent();
    visual_component->setTexture(texture);
    visual_component->setRelativeX(relative_x);
    visual_component->setRelativeY(relative_y);
    visual_component->setWidth(width);
    visual_component->setHeight(height);
    visual_component->setParent(parent);

    if (VERBOSE) std::cout << "\tCreating a new VisualComponent" << std::endl;

    return visual_component;
}

void VisualComponent::setParent(VisualComponent * new_parent)
{
    if (new_parent == _parent)
        return;
    else if (new_parent == nullptr)
        throw std::runtime_error("Attempt to set a VisualComponent parent as nullptr");

    if (_parent != nullptr)
        _parent->removeChild(this);

    new_parent->addChild(this);
    _parent = new_parent;
}

VisualComponent * VisualComponent::getParent()
{
    return _parent;
}


int32_t VisualComponent::countChildren() const
{
    return (int32_t) _children.size();
}

std::vector<VisualComponent *> VisualComponent::getChildren() const
{
    return _children;
}

void VisualComponent::hide()
{
    _is_hide = true;
    for (auto child : _children)
        child->hide();
}

void VisualComponent::show()
{
    _is_hide = false;
    for (auto child : _children)
        child->show();
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

void VisualComponent::draw()
{
    Graphics * graphics = Graphics::getInstance();
    if (_texture != nullptr && !_is_hide)
        graphics->drawTexture(_texture, getGlobalBody());
    
    for (auto child : _children)
        child->draw();
}

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
    for (auto child : _children) {
        
        if (VERBOSE) {
            std::cout << "\tDeleting VisualComponent:" << std::endl;
            Graphics * g = Graphics::getInstance();
            g->clearScreen();
            if (child->getTexture() != nullptr)
                g->drawTexture(child->getTexture(), child->getGlobalBody());
            g->updateScreen();
            SDL_Delay(900);
        }
        
        delete child;
    }
}

void VisualComponent::addChild(VisualComponent * child)
{
    for (auto e : _children) {
        if (e == child)
            return;
    }
    _children.push_back(child);
}

void VisualComponent::removeChild(VisualComponent * child)
{
    auto iter = _children.begin();
    for ( ; iter != _children.end(); iter++)
        if (*iter == child) break;

    _children.erase(iter);
}
