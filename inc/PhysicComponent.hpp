#ifndef _PHYSICCOMPONENT_HPP_
#define _PHYSICCOMPONENT_HPP_

#include "InteractiveComponent.hpp"
#include "VisualComponent.hpp"
#include "Vector2D.hpp"

class PhysicComponent : public InteractiveComponent
{
public:
    // Scale of the real world to pixels world
    // centimeters per pixel
    static double_t getScale();
    
    // Scale of the real world to pixels world
    static void setScale(double_t centimeters_per_pixel);

    void setVelocity(const Vector2D & new_velocity);
    Vector2D getVelocity() const;

    void decreaseVelocity(double_t amount);

    void enableGhost();
    void disableGhost();
    bool isGhost() const;
    bool isStopped() const;

private:
    static double_t _measurement_scale; 

    Vector2D _velocity;
    bool _is_ghost;

protected:
    PhysicComponent();
    virtual ~PhysicComponent();
};

#endif