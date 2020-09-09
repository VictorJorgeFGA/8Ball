#include "PhysicWorld.hpp"
#include "Ball.hpp"
#include "Cushion.hpp"

#include <iostream>

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

void PhysicWorld::addCushion(Cushion * cushion)
{
    for (auto c : _cushions)
        if (c == cushion) return;
    _cushions.push_back(cushion);
}

void PhysicWorld::removeCushion(Cushion * cushion)
{
    auto iter = _cushions.begin();
    while (true) {
        if (iter == _cushions.end())
            return;
        else if (*iter == cushion)
            break;
        else
            iter++;
    }
    _cushions.erase(iter);
}

void PhysicWorld::setFrictionCoefficient(double_t value)
{
    _friction_coefficient = value;
}

double_t PhysicWorld::getFrictionCoefficient() const
{
    return _friction_coefficient;
}

void PhysicWorld::updateWorldObjects(double_t delta_time)
{
    updateObjectsPosition(delta_time);
    resolveCollisions();
    applyFrictionForce(delta_time);
}

void PhysicWorld::resolveCollisions()
{
    for (int32_t i = 0; i < (int32_t) _balls.size(); i++)
        for (int32_t j = i + 1; j < (int32_t) _balls.size(); j++)
            collideBallToBall(_balls[i], _balls[j]);
    
    for (auto ball : _balls)
        for (auto cushion : _cushions)
            collideBallToCushion(ball, cushion);
}

void PhysicWorld::applyFrictionForce(double_t delta_time)
{
    for (auto ball : _balls)
        ball->decreaseVelocity(getFrictionCoefficient() * delta_time);
}

void PhysicWorld::updateObjectsPosition(double_t delta_time)
{
    for (auto ball : _balls)
        ball->updatePosition(delta_time);
}

void PhysicWorld::collideBallToBall(Ball * ball1, Ball * ball2)
{
    if (ball1->getCenter().distance(ball2->getCenter()) > ball1->getRadius() + ball2->getRadius())
        return;

    makePerfectBallToBallContact(ball1, ball2);

    Vector2D un(ball1->getCenter(), ball2->getCenter());
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

void PhysicWorld::makePerfectBallToBallContact(Ball * ball1, Ball * ball2)
{
    double_t x1 = ball1->getCenter().x();
    double_t x2 = ball2->getCenter().x();

    double_t y1 = ball1->getCenter().y();
    double_t y2 = ball2->getCenter().y();

    double_t vx1 = ball1->getVelocity().x();
    double_t vx2 = ball2->getVelocity().x();

    double_t vy1 = ball1->getVelocity().y();
    double_t vy2 = ball2->getVelocity().y();

    double_t r = ball1->getRadius() + ball2->getRadius();

    double_t a = (vx1 * vx1) - (2 * vx1 * vx2) + (vx2 * vx2) + (vy1 * vy1) - (2 * vy1 * vy2) + (vy2 * vy2);
    double_t b = 2 * (x1 * vx1 - x1 * vx2 - x2 * vx1 + x2 * vx2 + y1 * vy1 - y1 * vy2 - y2 * vy1 + y2 * vy2);
    double_t c = (x1*x1) - (2 * x1 * x2) + (x2 * x2) + (y1 * y1) - (2 * y1 * y2) + (y2 * y2) - (r*r);

    double_t delta = sqrt(b*b - (4 * a * c));
    double_t rollback_delta_time = ((-b) - delta) / (2*a);
    ball1->translate(ball1->getVelocity() * rollback_delta_time);
    ball2->translate(ball2->getVelocity() * rollback_delta_time);
}

void PhysicWorld::collideBallToCushion(Ball * ball, Cushion * cushion)
{
    if (abs(ball->getCenter().x() - cushion->getCenter().x()) > ball->getRadius() + (cushion->getWidth() / 2.0) ||
        abs(ball->getCenter().y() - cushion->getCenter().y()) > ball->getRadius() + (cushion->getHeight() / 2.0))
        return;
    
    if (cushion->getWidth() > cushion->getHeight()) {
        // Ideal_y tell us where ball should be placed to get a perfect tangential collision
        // If velocity vector aims to up, the ideal_y is bellow to cushion center
        // else the ideal_y is above to cushion center
        double_t ideal_y = cushion->getCenter().y();
        ideal_y += ball->getVelocity().y() < 0 ? cushion->getHeight() / 2 + ball->getRadius() : -(cushion->getHeight() / 2 + ball->getRadius());
        
        // Delta_y tell us how much the ball need to return in order to be placed at ideal_y
        // Time tell us how much time the ball spend to roll delta_y distance
        // and finally we translate ball with a negative time times velocity
        double_t delta_y = ideal_y - ball->getCenter().y();
        double_t time = -abs(delta_y / ball->getVelocity().y());
        ball->translate(ball->getVelocity() * time);
        ball->setVelocity({ball->getVelocity().x(), -ball->getVelocity().y()});
    } else {
        double_t ideal_x = cushion->getCenter().x();
        ideal_x += ball->getVelocity().x() < 0 ? cushion->getWidth() / 2 + ball->getRadius() : -(cushion->getWidth() / 2 + ball->getRadius());

        double_t delta_x = ideal_x - ball->getCenter().x();
        double_t time = -abs(delta_x / ball->getVelocity().x());
        ball->translate(ball->getVelocity() * time);
        ball->setVelocity({-ball->getVelocity().x(), ball->getVelocity().y()});
    }
}

PhysicWorld::PhysicWorld():
_friction_coefficient(7.2)
{

}

PhysicWorld::~PhysicWorld()
{
    
}