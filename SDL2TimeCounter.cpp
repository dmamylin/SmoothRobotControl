#include <SDL2\SDL.h>

#include "SDL2TimeCounter.h"

f64 SDL2TimeCounter::getMilliseconds() const {
    return (f64)SDL_GetTicks();
}