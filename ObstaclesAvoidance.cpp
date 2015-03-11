#define SDL_MAIN_HANDLED

#include "SDL2Application.h"
#include <SDL2\SDL.h>

#pragma comment(lib, "SDL2.lib")

#define WIDTH 800
#define HEIGHT 600
#define CAPTION "Obstacles avoidance"

int main(int argc, char** argv) {
    SDL_SetMainReady();

    SDL2Application app;

    return app.run(WIDTH, HEIGHT, CAPTION);
}