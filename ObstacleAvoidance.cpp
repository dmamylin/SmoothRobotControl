#define SDL_MAIN_HANDLED

#include "SDL2Application.h"
#include "ObstacleAvoidancePlayground.h"

#define WIDTH 800
#define HEIGHT 600
#define CAPTION "Obstacles avoidance"

int main(int argc, char** argv) {
    SDL2Application app;

    return app.run(new ObstacleAvoidancePlayground(), WIDTH, HEIGHT, CAPTION);
}