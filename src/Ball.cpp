#include "AssetsManager.hpp"
#include "Ball.hpp"
#include "PhysicWorld.hpp"

Ball * Ball::newBall(double_t radius, const Vector2D & center, uint8_t ball_number)
{
    return new Ball(radius, center, ball_number);
}

void Ball::translate(const Vector2D & translation)
{
    _center += translation;
    updateTextureCoordinates();
}

void Ball::updatePosition(double_t delta_time)
{
    _center += (getVelocity() * delta_time);
    updateTextureCoordinates();
}

void Ball::setCenter(const Vector2D & new_center)
{
    _center = new_center;
    updateTextureCoordinates();
}

Vector2D Ball::getCenter() const
{
    return _center;
}

void Ball::setRadius(double_t new_radius)
{
    _radius = new_radius;
    updateTextureSize();
}

double_t Ball::getRadius() const
{
    return _radius;
}

uint8_t Ball::getBallNumber() const
{
    return _ball_number;
}

void Ball::updateTextureCoordinates()
{
    setRelativeX((_center.x() - _radius) * PhysicComponent::getScale());
    setRelativeY((_center.y() - _radius) * PhysicComponent::getScale());
}

void Ball::updateTextureSize()
{
    setWidth(2.0 * _radius * PhysicComponent::getScale());
    setHeight(2.0 * _radius * PhysicComponent::getScale());
}

Ball::Ball(double_t radius, const Vector2D & center, uint8_t ball_number):
_radius(radius),
_center(center),
_ball_number(ball_number)
{
    AssetsManager * am = AssetsManager::getInstance();
    setTexture(am->getTexture("ball" + std::to_string(ball_number) + "_texture.png"));
    updateTextureCoordinates();
    updateTextureSize();
    PhysicWorld::getInstance()->addBall(this);
}

Ball::~Ball()
{

}
