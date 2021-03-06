#ifndef _RUNNINGMANAGER_HPP_
#define _RUNNINGMANAGER_HPP_

#include "SDL.hpp"
#include "Timer.hpp"
#include "Button.hpp"
#include "SolidImage.hpp"
#include "PhysicWorld.hpp"
#include "Ball.hpp"
#include "Table.hpp"

class RunningManager
{
public:
    static void startUp();
    static RunningManager * getInstance();
    static void shutDown();

    void runProgram();

private:
    static RunningManager * _instance;

    void processEvent();

    RunningManager();
    ~RunningManager();

    PhysicWorld * _physic_world;
    
    SDL_Event _event;
    bool _quit;
    Timer _rendering_timer;
    Timer _physics_timer;
    double _LOOP_TIME;
    double _120FPS_TIME;
    double _60FPS_TIME;
    double _30FPS_TIME;
    Button * _quit_button;
    Table * _table;
};

#endif