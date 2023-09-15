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

class FrameRateBalancer {
public:
    explicit FrameRateBalancer(const int& frame_rate)
        : frame_rate_(frame_rate) {}
    ~FrameRateBalancer() {}

    void SetTimer();
    void Delay() const;

private:
    const int& frame_rate_;
    SimpleTimer timer_;
};

class FrameRateMeasurer {
public:
    FrameRateMeasurer() : counted_frames_(0) {}
    ~FrameRateMeasurer() {}

    void SetTimer();
    bool MeasureFrameRate(float& measured_frame_rate);

private:
    int counted_frames_;
    SimpleTimer timer_;
};

#endif  // RUMRAISIN_INTERFACES_TIMER_H_
