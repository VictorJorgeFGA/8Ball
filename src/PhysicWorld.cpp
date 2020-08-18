#include "PhysicWorld.hpp"
#include "Ball.hpp"

PhysicWorld * PhysicWorld::_instance = nullptr;

PhysicWorld * PhysicWorld::getInstance()
{
    if (_instance == nullptr) _instance = new PhysicWorld();
    return _instance;
}

void PhysicWorld::addBall(Ball * ball)
{
    for (auto b : _balls)
        if (b == ball) return;

    _balls.push_back(ball);
}

void PhysicWorld::removeBall(Ball * ball)
{
    auto iter = _balls.begin();
    while (true) {
        if (iter == _balls.end())
            return;
        else if (*iter == ball)
            break;
        else
            iter++;
    }
    _balls.erase(iter);
}

void PhysicWorld::resolveCollisions()
{
    for (int32_t i = 0; i < (int32_t) _balls.size(); i++)
        for (int32_t j = i + 1; j < (int32_t) _balls.size(); j++)
            collideBallToBall(_balls[i], _balls[j]);
}

void PhysicWorld::updateObjectsPosition(double_t delta_time)
{
    for (auto ball : _balls)
        ball->updatePosition(delta_time);
}

void PhysicWorld::collideBallToBall(Ball * ball1, Ball * ball2)
{
    Vector2D un(ball1->getCenter(), ball2->getCenter());
    if (un.magnitude() > ball1->getRadius() + ball2->getRadius())
        return;

    if (un.magnitude() == 0.0)
        return;
    un = un * (1/un.magnitude());
    Vector2D ut(-un.y(), un.x());

    double_t v1n = un.innerProduct(ball1->getVelocity());
    double_t v1t = ut.innerProduct(ball1->getVelocity());
    double_t v2n = un.innerProduct(ball2->getVelocity());
    double_t v2t = ut.innerProduct(ball2->getVelocity());

    double_t v1n_ = v2n;
    double_t v2n_ = v1n;
    double_t v1t_ = v1t;
    double_t v2t_ = v2t;

    Vector2D vel1n(un * v1n_);
    Vector2D vel1t(ut * v1t_);
    Vector2D vel2n(un * v2n_);
    Vector2D vel2t(ut * v2t_);
    ball1->setVelocity(vel1n + vel1t);
    ball2->setVelocity(vel2n + vel2t);
}

PhysicWorld::PhysicWorld()
{

}

PhysicWorld::~PhysicWorld()
{
    
}