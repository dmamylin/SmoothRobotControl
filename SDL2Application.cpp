#include <SDL2\SDL.h>

#include "SDL2Event.h"
#include "debug.h"
#include "SDL2EventManager.h"
#include "SDL2TimeCounter.h"

#include "SDL2Application.h"

int SDL2Application::run(s32 windowWidth, s32 windowHeight, const char* windowCaption) {
    int initSuccess = 1;
    isRun = false;

    if (init(windowWidth, windowHeight, windowCaption)) {
        initSuccess = 0;
        isRun = true;
        updateApplication();
    }
    cleanup();

    return initSuccess;
}

bool SDL2Application::init(s32 windowWidth, s32 windowHeight, const char* windowCaption) {
    ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0);

    appWindow = SDL_CreateWindow(windowCaption, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    appRenderer = SDL_CreateRenderer(appWindow, -1, SDL_RENDERER_ACCELERATED);
    appDisplay = SDL_CreateRGBSurface(0, windowWidth, windowHeight, 32, 0, 0, 0, 0);
    eventManager = new SDL2EventManager();
    timeCounter = new SDL2TimeCounter();

    if (eventManager) {
        eventManager->addListener(this);
    }

    return appWindow && appRenderer && appDisplay && eventManager && timeCounter;
}

void SDL2Application::cleanup() {
    SDL_FreeSurface(appDisplay);
    SDL_DestroyRenderer(appRenderer);
    SDL_DestroyWindow(appWindow);
    delete eventManager;
    delete timeCounter;

    SDL_Quit();
}

void SDL2Application::updateApplication() {
    while (isRun) {
        eventManager->updateListeners();
    }
}

void SDL2Application::update(const IEvent* event) {
    if (event->getType() == EVENT_SDL2) {
        SDL2Event *sdl2Event = (SDL2Event*)event;

        switch (sdl2Event->rawSDLEvent.type) {
        case SDL_QUIT:
            isRun = false;
            break;

        case SDL_KEYDOWN:
            if (sdl2Event->rawSDLEvent.key.keysym.sym == SDLK_ESCAPE) {
                isRun = false;
            }
            break;

        default:
            break;
        }
    }
}