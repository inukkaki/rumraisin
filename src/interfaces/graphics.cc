#include "interfaces/graphics.h"

#include "SDL2/SDL.h"

#include "interfaces/config.h"
#include "models/entity.h"

namespace {

void RenderEntityBoundingBox(
        SDL_Renderer* const renderer, const EResource& res) {
    int window_scale = GetWindowScale();
    SDL_FRect rect = {
        window_scale * res.r.x,
        window_scale * res.r.y,
        window_scale * res.width,
        window_scale * res.height
    };
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawRectF(renderer, &rect);
}

void RenderEntityVelocity(SDL_Renderer* const renderer, const EResource& res) {
    int window_scale = GetWindowScale();
    float x1 = window_scale * (res.r.x + res.width/2);
    float y1 = window_scale * (res.r.y + res.height/2);
    float x2 = x1 + window_scale*kVelocityRenderScale*res.v.x;
    float y2 = y1 + window_scale*kVelocityRenderScale*res.v.y;
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
    SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
}

void RenderEntityAcceleration(
        SDL_Renderer* const renderer, const EResource& res) {
    int window_scale = GetWindowScale();
    float x1 = window_scale * (res.r.x + res.width/2);
    float y1 = window_scale * (res.r.y + res.height/2);
    float x2 = x1 + window_scale*kAccelerationRenderScale*res.a.x;
    float y2 = y1 + window_scale*kAccelerationRenderScale*res.a.y;
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
}

}  // namespace

void RenderEntityDebugInfo(
        SDL_Renderer* const renderer, const EResource& res) {
    RenderEntityBoundingBox(renderer, res);
    RenderEntityVelocity(renderer, res);
    RenderEntityAcceleration(renderer, res);
}
