#include "interfaces/graphics.h"

#include "SDL2/SDL.h"

#include "interfaces/config.h"
#include "models/entity.h"
#include "models/field.h"

namespace {

void RenderEntityBoundingBox(
        SDL_Renderer* const renderer, const EResource& res, int window_scale) {
    SDL_FRect rect = {
        window_scale * res.r.x,
        window_scale * res.r.y,
        window_scale * res.width,
        window_scale * res.height
    };
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawRectF(renderer, &rect);
}

void RenderEntityVelocity(
        SDL_Renderer* const renderer, const EResource& res, int window_scale) {
    float x1 = window_scale * (res.r.x + res.width/2);
    float y1 = window_scale * (res.r.y + res.height/2);
    float x2 = x1 + window_scale*kVelocityRenderScale*res.v.x;
    float y2 = y1 + window_scale*kVelocityRenderScale*res.v.y;
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
    SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
}

void RenderEntityAcceleration(
        SDL_Renderer* const renderer, const EResource& res, int window_scale) {
    float x1 = window_scale * (res.r.x + res.width/2);
    float y1 = window_scale * (res.r.y + res.height/2);
    float x2 = x1 + window_scale*kAccelerationRenderScale*res.a.x;
    float y2 = y1 + window_scale*kAccelerationRenderScale*res.a.y;
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
}

}  // namespace

void RenderEntityDebugInfo(
        SDL_Renderer* const renderer, const EResource& res, int window_scale) {
    RenderEntityBoundingBox(renderer, res, window_scale);
    RenderEntityVelocity(renderer, res, window_scale);
    RenderEntityAcceleration(renderer, res, window_scale);
}

namespace {

void RenderEntityVelocityOnCorners(
        SDL_Renderer* const renderer, const EResource& res, int window_scale) {
    float x, y;
    float w = window_scale * kVelocityRenderScale * res.v.x;
    float h = window_scale * kVelocityRenderScale * res.v.y;
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
    if ((w < 0.0f) || (h < 0.0f)) {
        x = window_scale * res.r.x;
        y = window_scale * res.r.y;
        SDL_RenderDrawLineF(renderer, x, y, x + w, y + h);
    }
    if ((w > 0.0f) || (h < 0.0f)) {
        x = window_scale * (res.r.x + res.width);
        y = window_scale * res.r.y;
        SDL_RenderDrawLineF(renderer, x, y, x + w, y + h);
    }
    if ((w < 0.0f) || (h > 0.0f)) {
        x = window_scale * res.r.x;
        y = window_scale * (res.r.y + res.height);
        SDL_RenderDrawLineF(renderer, x, y, x + w, y + h);
    }
    if ((w > 0.0f) || (h > 0.0f)) {
        x = window_scale * (res.r.x + res.width);
        y = window_scale * (res.r.y + res.height);
        SDL_RenderDrawLineF(renderer, x, y, x + w, y + h);
    }
}

}  // namespace

void RenderEntityCollisionInfo(
        SDL_Renderer* const renderer, const EResource& res, int window_scale) {
    RenderEntityBoundingBox(renderer, res, window_scale);
    RenderEntityVelocityOnCorners(renderer, res, window_scale);
    RenderEntityAcceleration(renderer, res, window_scale);
}

void RenderFieldDebugInfo(
        SDL_Renderer* const renderer, const Field& field, int window_scale) {
    // just for debugging
    int value;
    SDL_Rect rect;
    for (int i = 0; i < kFieldMaxHeight; ++i) {
        for (int j = 0; j < kFieldMaxWidth; ++j) {
            value = field.GetCollision(i, j).debug_value;
            if (value == 100) {
                continue;
            }
            rect = {
                window_scale * kGridUnit * j,
                window_scale * kGridUnit * i,
                window_scale * kGridUnit,
                window_scale * kGridUnit
            };
            switch (value) {
            case 101:
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                break;
            case 102:
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                break;
            default:
                SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
                break;
            }
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}
