#ifndef RUMRAISIN_INTERFACES_GRAPHICS_H_
#define RUMRAISIN_INTERFACES_GRAPHICS_H_

#include "SDL2/SDL.h"

#include "models/entity.h"
#include "models/field.h"

inline constexpr float kVelocityRenderScale = 1.0f;
inline constexpr float kAccelerationRenderScale = 60.0f;

void RenderEntityDebugInfo(
        SDL_Renderer* const renderer, const EResource& res, int window_scale);
void RenderEntityCollisionInfo(
        SDL_Renderer* const renderer, const EResource& res, int window_scale);

void RenderFieldDebugInfo(
        SDL_Renderer* const renderer, const Field& field, int window_scale);

#endif  // RUMRAISIN_INTERFACES_GRAPHICS_H_
