#ifndef _VECTOR2D_HPP_
#define _VECTOR2D_HPP_

#include <cmath>

class Vector2D
{
public:
    Vector2D(double x = 0, double y = 0);
    Vector2D(const Vector2D & v);
    Vector2D(const Vector2D && v);
    Vector2D(const Vector2D & origin, const Vector2D & arrow);

    ~Vector2D();

    double_t magnitude();
    double_t innerProduct(const Vector2D & v);
    double_t distance(const Vector2D & v);
    
    Vector2D & operator=(const Vector2D && v);
    Vector2D & operator=(const Vector2D & v);
    Vector2D & operator+=(const Vector2D & v);
    Vector2D & operator+=(const Vector2D && v);
    Vector2D operator+(const Vector2D & v) const; 
    Vector2D operator*(double_t k) const;
    Vector2D operator-(const Vector2D & v) const;
    
    double_t x() const;
    double_t y() const;
    void x(double_t x);
    void y(double_t y);

private:
    bool _mag_changed {true};
    double_t _mag {1.0};
    double_t _x, _y;
};

#endif
