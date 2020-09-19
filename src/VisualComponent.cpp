#include "VisualComponent.hpp"
#include "Graphics.hpp"
#include <stdexcept>
#include <iostream>

VisualComponent * VisualComponent::SCREEN = nullptr;
bool VisualComponent::VERBOSE = false;
const std::string VisualComponent::VERBOSE_MSG = "\033[0;33m(VERBOSE) VisualComponent:\t\033[0m";
Graphics * VisualComponent::graphics = nullptr;

void VisualComponent::setVerboseMode()
{
    VERBOSE = true;
}

void VisualComponent::startUp()
{
    if (SCREEN == nullptr) {
        graphics = Graphics::getInstance();
        SCREEN = new VisualComponent();
        SCREEN->setWidth(graphics->getWindowWidth());
        SCREEN->setHeight(graphics->getWindowHeight());
        SCREEN->setGlobalX(0);
        SCREEN->setGlobalY(0);

        if (VERBOSE) std::cout << VERBOSE_MSG + "Starting up" << std::endl;
    }
    else
        throw std::runtime_error("Attempt to startUp VisualComponent twice");
}

void VisualComponent::shutDown()
{
    if (SCREEN == nullptr)
        throw std::runtime_error("Attempt to shutDown VisualComponent before initialization");
    
    delete SCREEN;
    SCREEN = nullptr;
    graphics = nullptr;

    if (VERBOSE) std::cout << VERBOSE_MSG + "Shutting down\n" << std::endl; 
}

void VisualComponent::drawComponents()
{
    if (SCREEN == nullptr)
        throw std::runtime_error("Attempt to draw VisualComponent objects before VisualComponent initialization");
    
    graphics->clearScreen();
    SCREEN->draw();
    graphics->updateScreen();
}

VisualComponent * VisualComponent::getScreenObject()
{
    if (SCREEN == nullptr)
        throw std::runtime_error("Attempt to get VisualComponent::SCREEN object before VisualComponent initialization");
    
    return SCREEN;
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

double VisualComponent::getRotationAngle() const
{
    return _rotation_angle;
}

void VisualComponent::setRotationAngle(double rotation_angle)
{
    _rotation_angle = rotation_angle;
}

void VisualComponent::rotateClockwise(double amount)
{
    setRotationAngle(getRotationAngle() + amount);
    for (auto child : _children)
        child->rotateClockwise(amount);
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

void VisualComponent::draw()
{
    if (_texture != nullptr && !_is_hide)
        graphics->drawTexture(_texture, getGlobalBody(), getRotationAngle());
    
    for (auto child : _children)
        child->draw();
}

VisualComponent::VisualComponent():
_parent(nullptr),
_children(),
_texture(nullptr),
_body({0,0,0,0}),
_is_hide(false),
_rotation_angle(0.0f)
{

}

VisualComponent::~VisualComponent()
{
    for (auto child : _children) {
        
        if (VERBOSE) {
            std::cout << VERBOSE_MSG + "Deleting this component:" << std::endl;

            graphics->clearScreen();
            if (child->getTexture() != nullptr)
                graphics->drawTexture(child->getTexture(), child->getGlobalBody());
            graphics->updateScreen();
            SDL_Delay(900);
        }

        delete child;
    }
}
