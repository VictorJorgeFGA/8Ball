#ifndef _CUSHION_HPP_
#define _CUSHION_HPP_

#include "PhysicComponent.hpp"
#include "Vector2D.hpp"

class Cushion : public PhysicComponent
{
public:
    static Cushion * newCushion(double_t width, double_t height, const Vector2D & top_left);

    Vector2D getCenter() const;

    void setWidth(double_t width);
    double_t getWidth() const;

    void setHeight(double_t height);
    double_t getHeight() const;

private:
    Vector2D _top_left;
    double_t _width;
    double_t _height;

    void updateTextureCoordinates();
    void updateTextureSize();

    Cushion(double_t width, double_t height, const Vector2D & top_left);
    virtual ~Cushion();

};

#endif