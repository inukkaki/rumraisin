#include "interfaces/timer.h"

#include <limits>

#include "SDL2/SDL.h"

void SimpleTimer::Set() {
    start_time_ = SDL_GetTicks64();
}

int SimpleTimer::GetElapsedTime() const {
    Uint64 elapsed_time = SDL_GetTicks64() - start_time_;
    if (elapsed_time > std::numeric_limits<int>::max()) {
        return std::numeric_limits<int>::max();
    } else {
        return static_cast<int>(elapsed_time);
    }
}

void FrameRateBalancer::SetTimer() {
    timer_.Set();
}

void FrameRateBalancer::Delay() const {
    int elapsed_time = timer_.GetElapsedTime();
    int delay_time = static_cast<int>(1000.0f/frame_rate_ - elapsed_time);
    if (delay_time > 0) {
        SDL_Delay(delay_time);
    }
}
