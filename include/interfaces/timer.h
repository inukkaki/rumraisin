#ifndef RUMRAISIN_INTERFACES_TIMER_H_
#define RUMRAISIN_INTERFACES_TIMER_H_

#include "SDL2/SDL.h"

class SimpleTimer {
public:
    SimpleTimer() : start_time_(0ul) {}
    ~SimpleTimer() {}

    void Set();
    int GetElapsedTime() const;

private:
    Uint64 start_time_;
};

#endif  // RUMRAISIN_INTERFACES_TIMER_H_
