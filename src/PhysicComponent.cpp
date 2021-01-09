#include "PhysicComponent.hpp"

#include <iostream>

double_t PhysicComponent::_measurement_scale = 1.0;

double_t PhysicComponent::getScale()
{
    return _measurement_scale;
}

void PhysicComponent::setScale(double_t centimeters_per_pixel)
{
    _measurement_scale = centimeters_per_pixel;
}

void PhysicComponent::setVelocity(const Vector2D & new_velocity)
{
    _velocity = new_velocity;
}

Vector2D PhysicComponent::getVelocity() const
{
    return _velocity;
}

void PhysicComponent::decreaseVelocity(double_t amount)
{
    if (_velocity.magnitude() < DBL_EPSILON)
        return;
    else if (_velocity.magnitude() < 0.1) {
        _velocity = Vector2D(0.0, 0.0);
        return;
    }
    _velocity.y(_velocity.y() - amount * (_velocity.y() / _velocity.magnitude()));
    _velocity.x(_velocity.x() - amount * (_velocity.x() / _velocity.magnitude()));
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
    return (abs(_velocity.x()) < DBL_EPSILON && abs(_velocity.y()) < DBL_EPSILON);
}

PhysicComponent::PhysicComponent():
InteractiveComponent(0, 0),
_velocity({0.0, 0.0}),
_is_ghost(false)
{

}

PhysicComponent::~PhysicComponent()
{

}
