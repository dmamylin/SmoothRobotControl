#ifndef SDL2_DEVICE_H
#define SDL2_DEVICE_H

#include <SDL2\SDL.h>
#include <list>

#include "utilities.h"
#include "ColorRGB.h"
#include "SDL2Types.h"
#include "SDL2IEventManager.h"

class SDL2Device : public SDL2IEventManager, SDL2IEventListener {
private:
    bool run;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* display;

    std::list<SDL2IEventListener*> eventListeners;

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

    void pollEvent() {
        SDL_Event ev;

        SDL_PollEvent(&ev);
        notifyListeners(ev);
    }

    void update(const SDL_Event& ev) {
        if (ev.type == SDL_QUIT ||
            (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE)) {
            this->stop();
        }
    }

    void addListener(SDL2IEventListener* listener) {
        eventListeners.push_back(listener);
    }

    void removeListener(SDL2IEventListener* listener) {
        eventListeners.remove(listener);
    }

    void notifyListeners(const SDL_Event& ev) {
        for (auto it = eventListeners.begin(); it != eventListeners.end(); it++) {
            (*it)->update(ev);
        }
    }
};

#endif