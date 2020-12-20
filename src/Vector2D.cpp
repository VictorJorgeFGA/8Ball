#include "Vector2D.hpp"

Vector2D::Vector2D(double_t x, double_t y):
_x(x),
_y(y),
_mag_changed(true)
{

}

Vector2D::Vector2D(const Vector2D & v):
_x(v.x()),
_y(v.y()),
_mag_changed(true)
{

}

Vector2D::Vector2D(const Vector2D && v):
_x(v.x()),
_y(v.y()),
_mag_changed(true)
{

}

Vector2D::Vector2D(const Vector2D & origin, const Vector2D & arrow):
_x(arrow.x() - origin.x()),
_y(arrow.y() - origin.y()),
_mag_changed(true)
{

}

Vector2D::~Vector2D()
{

}

double_t Vector2D::magnitude()
{
    if (_mag_changed) {
        _mag_changed = false;
        _mag = sqrt((_x*_x)+(_y*_y));
    }
    return _mag;
}

double_t Vector2D::innerProduct(const Vector2D & v)
{
    return _x*v.x() + _y*v.y();
}

double_t Vector2D::distance(const Vector2D & v)
{
    return sqrt( (x()-v.x())*(x()-v.x()) + (y()-v.y())*(y()-v.y()) );
}

Vector2D & Vector2D::operator=(const Vector2D & v)
{
    _x = v.x();
    _y = v.y();
    _mag_changed = true;
    return *this;
}

Vector2D & Vector2D::operator=(const Vector2D && v)
{
    _x = v.x();
    _y = v.y();
    _mag_changed = true;
    return *this;
}

Vector2D & Vector2D::operator+=(const Vector2D & v)
{
    _x += v.x();
    _y += v.y();
    _mag_changed = true;
    return *this;
}

Vector2D & Vector2D::operator+=(const Vector2D && v)
{
    _x += v.x();
    _y += v.y();
    _mag_changed = true;
    return *this;
}

Vector2D Vector2D::operator+(const Vector2D & v) const
{
    return Vector2D(_x + v.x(), _y + v.y());
}

Vector2D Vector2D::operator*(double_t k) const
{
    return Vector2D(_x*k, _y*k);
}

Vector2D Vector2D::operator-(const Vector2D & v) const
{
    return Vector2D(_x-v.x(), _y-v.y());
}

double_t Vector2D::x() const
{
    return _x;
}

double_t Vector2D::y() const
{
    return _y;
}

void Vector2D::x(double_t x)
{
    _x = x;
    _mag_changed = true;
}

void Vector2D::y(double_t y)
{
    _y = y;
    _mag_changed = true;
}
