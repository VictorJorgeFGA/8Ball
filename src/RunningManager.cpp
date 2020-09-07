#include "RunningManager.hpp"
#include "VisualComponent.hpp"
#include "InteractiveComponent.hpp"
#include "Button.hpp"
#include "SolidImage.hpp"
#include "Table.hpp"

#include <stdexcept>
#include <iostream>

RunningManager * RunningManager::_instance = nullptr;

void RunningManager::startUp()
{
    if (_instance != nullptr)
        throw std::runtime_error("Attempt to initialize RunningManager twice.");

    _instance = new RunningManager();
}

RunningManager * RunningManager::getInstance()
{
    return _instance;
}

void RunningManager::shutDown()
{
    if (_instance == nullptr)
        throw std::runtime_error("Attempt to shutdown RunningManager before initialization");

    delete _instance;
    _instance = nullptr;
}

void RunningManager::runProgram()
{
    while (! _quit) {
        while (SDL_PollEvent(&_event) != 0)
            processEvent();

        if (_physics_timer.getElapsedTime() >= _120FPS_TIME) {
            _physic_world->updateWorldObjects(_physics_timer.getElapsedTime());
            _physics_timer.reset();
        }
        
        if (_rendering_timer.getElapsedTime() >= _60FPS_TIME) {
            VisualComponent::drawComponents();
            _rendering_timer.reset();
        }
        SDL_Delay(5);
    }
}


void RunningManager::processEvent()
{
    switch (_event.type) {
    case SDL_QUIT:
        _quit = true;
        break;

    case SDL_MOUSEBUTTONDOWN:
        if (_event.button.button == SDL_BUTTON_LEFT)
            InteractiveComponent::processMouseButtonDown({_event.button.x, _event.button.y});
        break;
    
    case SDL_MOUSEBUTTONUP:
        if (_event.button.button == SDL_BUTTON_LEFT)
            InteractiveComponent::processMouseButtonUp({_event.button.x, _event.button.y});
        break;

    case SDL_MOUSEMOTION:
        InteractiveComponent::processMouseMotion({_event.motion.x, _event.motion.y});
        break;

    default:
        break;
    }
}

RunningManager::RunningManager():
_event(),
_quit(false),
_rendering_timer(),
_LOOP_TIME(0.0035),
_120FPS_TIME(1.0/120.0),
_60FPS_TIME(1.0/60.0),
_30FPS_TIME(1.0/30.0),
_quit_button(nullptr)
{
    _quit_button = Button::newButton("Sair");
    _quit_button->setClickReaction([](){
        SDL_Event e;
        e.type = SDL_QUIT;
        SDL_PushEvent(&e);
    });

    _table = Table::newTable(960.0, 544.0);
    _quit_button->setParent(_table);
    _quit_button->untie();

    _120FPS_TIME -= _LOOP_TIME;
    _60FPS_TIME -= _LOOP_TIME;
    _30FPS_TIME -= _LOOP_TIME;

    _physic_world = PhysicWorld::getInstance();
    _test_ball = Ball::newBall(15.0, {150.0, 150.0}, 1);
    _test_ball->setVelocity({700.0,700.0});
    _ball2 = Ball::newBall(15.0, {200.0, 200.0}, 1);
    _ball2->setVelocity({5.0, -10.0});
    _test_ball->activate();
    _ball2->activate();
    _test_ball->untie();
    _ball2->untie();
    _test_ball->setParent(_table);
    _ball2->setParent(_table);
    _table->deactivate();
    Ball * bola = Ball::newBall(15.0, {150.0, 300.0}, 1);
    bola->setVelocity({-100, -90});
    bola->setParent(_table);
    bola->untie();

    Ball * bola2 = Ball::newBall(15.0, {175.0, 300.0}, 1);
    bola2->setVelocity({1,1});
    bola2->setParent(_table);
    bola2->untie();
}

RunningManager::~RunningManager()
{

}