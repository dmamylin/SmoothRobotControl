#ifndef SDL2_DEVICE_H
#define SDL2_DEVICE_H

#include <SDL2\SDL.h>

#include "utilities.h"
#include "ColorRGB.h"
#include "SDL2Types.h"

class SDL2Device {
private:
    bool run;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* display;

    SDL2Device(const SDL2Device&);
public:
    SDL2Device() :
        run(true), window(NULL), renderer(NULL), display(NULL) {}

    void initialize(s32 width, s32 height, const char* caption) {
        SDL_Init(SDL_INIT_VIDEO);

        window = SDL_CreateWindow(caption, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        display = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    }

    void cleanup() {
        SDL_FreeSurface(display);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    inline bool isRun() const { return run; }
    void stop() { run = false; }
    void beginScene(const ColorRGB& fillColor) {
        SDL_FillRect(display, NULL, fillColor.getAsNumber());
    }
    void endScene() {
        SDL_Texture* displayTexture = SDL_CreateTextureFromSurface(renderer, display);
        SDL_RenderCopy(renderer, displayTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(displayTexture);
    }

    point2i getMousePosition() const {
        s32 mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        return point2i(mouseX, mouseY);
    }

    inline SDL_Surface* getDisplaySurface() { return display;  }
};

#endif