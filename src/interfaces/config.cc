#include "interfaces/config.h"

namespace {

int window_scale = 2;

int frame_rate = 60;

}  // namespace

int GetWindowScale() {
    return window_scale;
}

const int& GetFrameRate() {
    return frame_rate;
}
