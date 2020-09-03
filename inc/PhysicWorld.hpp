#ifndef _PHYSICWORLD_HPP_
#define _PHYSICWORLD_HPP_

#include <vector>
#include <cmath>

class Ball;
class Cushion;

class PhysicWorld
{
public:
    static PhysicWorld * getInstance();
    void addBall(Ball * ball);
    void removeBall(Ball * ball);

    void addCushion(Cushion * cushion);
    void removeCushion(Cushion * cushion);

    //Recommended to be called at least 80x per second
    //High object velocities and low calling rate could result in strange physics behavior 
    void resolveCollisions();
    void updateObjectsPosition(double_t delta_time);

private:
    static PhysicWorld * _instance;

    void collideBallToBall(Ball * ball1, Ball * ball2);
    void collideBallToCushion(Ball * ball, Cushion * cushion);

    std::vector<Ball *> _balls;
    std::vector<Cushion *> _cushions;

    PhysicWorld();
    ~PhysicWorld();
};

#endif