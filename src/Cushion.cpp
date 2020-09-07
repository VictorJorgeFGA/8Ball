#include "Cushion.hpp"
#include "AssetsManager.hpp"
#include "PhysicWorld.hpp"

Cushion * Cushion::newCushion(double_t width, double_t height, const Vector2D & top_left_point)
{
    return new Cushion(width, height, top_left_point);;
}

Vector2D Cushion::getCenter() const
{
    return Vector2D(_top_left.x() + (_width / 2.0), _top_left.y() + (_height / 2.0));
}

void Cushion::setWidth(double_t width)
{
    _width = width;
    updateTextureSize();
}

double_t Cushion::getWidth() const
{
    return _width;
}

void Cushion::setHeight(double_t height)
{
    _height = height;
    updateTextureSize();
}

double_t Cushion::getHeight() const
{
    return _height;
}

void Cushion::updateTextureCoordinates()
{
    setRelativeX(_top_left.x() / PhysicComponent::getScale());
    setRelativeY(_top_left.y() / PhysicComponent::getScale());
}

void Cushion::updateTextureSize()
{
    setWidth(_width / PhysicComponent::getScale());
    setHeight(_height / PhysicComponent::getScale());
}

Cushion::Cushion(double_t width, double_t height, const Vector2D & top_left_point):
_top_left(top_left_point),
_width(width),
_height(height)
{
    AssetsManager * am = AssetsManager::getInstance();
    updateTextureCoordinates();
    updateTextureSize();
    PhysicWorld::getInstance()->addCushion(this);
    InteractiveComponent::deactivate();

    if (width > height)
        VisualComponent::setTexture(am->getTexture("horizontal_cushion_texture.png"));
    else
        VisualComponent::setTexture(am->getTexture("vertical_cushion_texture.png"));
}

Cushion::~Cushion()
{

}