#ifndef _VECTOR2D_HPP_
#define _VECTOR2D_HPP_

#include <cmath>

struct Vector2D
{
    Vector2D(double x = 0, double y = 0):x(x), y(y) {};
    Vector2D(const Vector2D & v2d):x(v2d.x), y(v2d.y) {};
    Vector2D(const Vector2D && v2d):x(v2d.x), y(v2d.y) {};
    ~Vector2D();

    double magnitude() const
    {
        return sqrt((x*x)+(y*y));
    }

    double translate(const Vector2D & v2d)
    {
        x += v2d.x;
        y += v2d.y;
    }

    Vector2D & operator=(const Vector2D && v2d)
    {
        x = v2d.x;
        y = v2d.y;

        return *this;
    }

    Vector2D & operator=(const Vector2D & v2d)
    {
        x = v2d.x;
        y = v2d.y;

        return *this;
    }

    Vector2D & operator+=(const Vector2D & v2d)
    {
        x += v2d.x;
        y += v2d.y;

        return *this;
    }

    Vector2D & operator+=(const Vector2D && v2d)
    {
        x += v2d.x;
        y += v2d.y;

        return *this;
    }

    Vector2D operator*(double_t k) const
    {
        return Vector2D(x*k, y*k);
    }

    double x, y;
};

const Vector2D VECTOR_I {1,0};
const Vector2D VECTOR_J {0,1};

#endif
