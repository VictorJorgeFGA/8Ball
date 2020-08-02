#include "Timer.hpp"
#include "SDL.hpp"

Timer::Timer():
_initial_ticks(SDL_GetTicks()),
_time_scale(1.0f)
{

}

Timer::~Timer()
{

}

float Timer::getElapsedTime() const
{
    return ((SDL_GetTicks() - _initial_ticks) * _time_scale) / 1000;
}

float Timer::getTimeScale() const
{
    return _time_scale;
}

void Timer::setTimeScale(float time_scale)
{
    _time_scale = time_scale;
}

void Timer::reset()
{
    _initial_ticks = SDL_GetTicks();
}