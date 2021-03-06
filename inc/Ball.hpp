#ifndef _BALL_HPP_
#define _BALL_HPP_

#include "Vector2D.hpp"
#include "PhysicComponent.hpp"

class Ball : public PhysicComponent
{
public:
    static Ball * newBall(double_t radius, const Vector2D & center, uint8_t ball_number);

    void translate(const Vector2D & translation);
    void updatePosition(double_t delta_time);

    void setCenter(const Vector2D & new_center);
    Vector2D getCenter() const;

    void setRadius(double_t new_radius);
    double_t getRadius() const;

    uint8_t getBallNumber() const;

private:
    void updateTextureCoordinates();
    void updateTextureSize();

    Ball(double_t radius = 0.0, const Vector2D & center = {0.0}, uint8_t ball_number = 0);
    virtual ~Ball();

    double_t _radius;
    Vector2D _center;
    uint8_t _ball_number;

protected:
    virtual void reactToDragging(const SDL_Point & cursor_coordinates);
};

#endif