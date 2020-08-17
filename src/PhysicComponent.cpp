#include "PhysicComponent.hpp"

double_t PhysicComponent::_measurement_scale = 1.0;

double_t PhysicComponent::getScale()
{
    return _measurement_scale;
}

void PhysicComponent::setScale(double_t meters_per_pixel)
{
    _measurement_scale = meters_per_pixel;
}

void PhysicComponent::setVelocity(const Vector2D & new_velocity)
{
    _velocity = new_velocity;
}

Vector2D PhysicComponent::getVelocity() const
{
    return _velocity;
}

void PhysicComponent::enableGhost()
{
    _is_ghost = true;
}

void PhysicComponent::disableGhost()
{
    _is_ghost = false;
}

bool PhysicComponent::isGhost() const
{
    return _is_ghost;
}

bool PhysicComponent::isStopped() const
{
    return (abs(_velocity.x) < DBL_EPSILON && abs(_velocity.y) < DBL_EPSILON);
}

PhysicComponent::PhysicComponent():
_velocity({0.0, 0.0}),
_is_ghost(false)
{
    setParent(VisualComponent::getScreenObject());
}

PhysicComponent::~PhysicComponent()
{

}