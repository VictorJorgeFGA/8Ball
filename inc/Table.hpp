#ifndef _TABLE_HPP_
#define _TABLE_HPP_

#include "PhysicComponent.hpp"
#include "Cushion.hpp"

#include <vector>

class Table : public PhysicComponent
{
public:
    static Table * newTable(double_t width, double_t height, const Vector2D & top_left = {0.0, 0.0});

    void setPosition(const Vector2D & top_left);
    Vector2D getPosition() const;

private:
    Table(double_t width = 270.0, double_t height = 135.0, const Vector2D & top_left = {0.0, 0.0});
    virtual ~Table();

    double_t _width;
    double_t _height;
    Vector2D _top_left;
    std::vector<Cushion *> _cushions;
};

#endif