#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <stdint.h>

class Timer
{
public:
    Timer();
    ~Timer();

    float getElapsedTime() const;
    float getTimeScale() const;
    void setTimeScale(float time_scale);
    void reset();

private:
    int32_t _initial_ticks;
    float _time_scale;
};

#endif