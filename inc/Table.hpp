#ifndef _TABLE_HPP_
#define _TABLE_HPP_

#include "PhysicComponent.hpp"
#include "Cushion.hpp"

#include <vector>

class Table : public PhysicComponent
{
public:
    static Table * newTable();

    void setPosition(const Vector2D & top_left);
    Vector2D getPosition() const;

    Vector2D getTableCenter() const;

private:
    void updateCushionsPosition();

    Table();
    virtual ~Table();

    double_t _width;
    double_t _height;
    Vector2D _top_left;
    
    Cushion * _top_cushion;
    Cushion * _right_cushion;
    Cushion * _bot_cushion;
    Cushion * _left_cushion;
};

#endif