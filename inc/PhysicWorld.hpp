#ifndef _PHYSICWORLD_HPP_
#define _PHYSICWORLD_HPP_

#include "Ball.hpp"

#include <vector>

class PhysicWorld
{
public:
    static PhysicWorld * getInstance();
    void addBall(Ball * ball);
    void removeBall(Ball * ball);
    void resolveCollisions();
    void updateObjectsPosition(double_t delta_time);

private:
    static PhysicWorld * _instance;

    void collideBallToBall(Ball * ball1, Ball * ball2);

    std::vector<Ball *> _balls;

    PhysicWorld();
    ~PhysicWorld();
};

#endif