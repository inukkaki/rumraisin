#ifndef RUMRAISIN_INTERFACES_GRAPHICS_H_
#define RUMRAISIN_INTERFACES_GRAPHICS_H_

#include "SDL2/SDL.h"

#include "models/entity.h"

inline constexpr float kVelocityRenderScale = 10.0f;
inline constexpr float kAccelerationRenderScale = 100.0f;

void RenderEntityDebugInfo(
        SDL_Renderer* const renderer, const EResource& res);

#endif  // RUMRAISIN_INTERFACES_GRAPHICS_H_
