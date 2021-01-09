#include "Pocket.hpp"
#include "AssetsManager.hpp"
#include "PhysicWorld.hpp"

#include <string>
#include <iostream>

const std::string Pocket::POCKET_TEXTURE = "pocket_texture.png";
const std::string Pocket::POCKET_SPOTLIGHT_TEXTURE = "pocket_spotlight_texture.png";

Pocket * Pocket::chosen_pocket = nullptr;
bool Pocket::can_choose_pocket = false;

Pocket * Pocket::newPocket(const Vector2D center, double_t radius)
{
    return new Pocket(center, radius);
}

void Pocket::enablePocketChoice() noexcept
{
    can_choose_pocket = true;
}

void Pocket::disablePocketChoice() noexcept
{
    can_choose_pocket = false;
}

void Pocket::setCenter(const Vector2D & center) noexcept
{
    _center = center;
}

Vector2D Pocket::getCenter() const noexcept
{
    return _center;
}

void Pocket::setRadius(double_t radius) noexcept
{
    _radius = radius;
}

double_t Pocket::getRadius() const noexcept
{
    return _radius;
}

void Pocket::updateTextureCoordinates() noexcept
{
    VisualComponent::setGlobalX(Pocket::getCenter().x() / PhysicComponent::getScale());
    VisualComponent::setGlobalY(Pocket::getCenter().y() / PhysicComponent::getScale());
}

void Pocket::updateTextureSize() noexcept
{
    VisualComponent::setWidth(Pocket::getRadius() / PhysicComponent::getScale());
    VisualComponent::setHeight(Pocket::getRadius() / PhysicComponent::getScale());
}

Pocket::Pocket()
{

}

Pocket::Pocket(const Vector2D center, double_t radius):
_center(center),
_radius(radius)
{

    VisualComponent::setTexture(AssetsManager::getInstance()->getTexture(POCKET_TEXTURE));
    
    updateTextureSize();
    updateTextureCoordinates();

    _spotlight = SolidImage::newSolidImage(POCKET_SPOTLIGHT_TEXTURE, VisualComponent::getWidth(), VisualComponent::getHeight());
    _spotlight->setParent(this);
    _spotlight->setWidth(VisualComponent::getWidth());
    _spotlight->setHeight(VisualComponent::getHeight());
    _spotlight->hide();

    InteractiveComponent::activate();
    PhysicWorld::getInstance()->addPocket(this);
}

Pocket::~Pocket()
{

}

void Pocket::reactToClick(const SDL_Point & cursor_coordinates)
{
    if (!can_choose_pocket)
        return;

    if (chosen_pocket == this) {
        chosen_pocket = nullptr;
        _spotlight->hide();
        return;
    }
    
    if (chosen_pocket != nullptr)
        chosen_pocket->_spotlight->hide();

    chosen_pocket = this;
    _spotlight->show();
}
