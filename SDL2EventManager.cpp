#include "SDL2EventManager.h"

#include <SDL2\SDL.h>
#include "SDL2Event.h"

void SDL2EventManager::addListener(IEventListener* listener) {
    eventListeners.push_back(listener);
}

void SDL2EventManager::removeListener(IEventListener* listener) {
    eventListeners.remove(listener);
}

void SDL2EventManager::updateListeners() {
    SDL2Event event;

    SDL_PollEvent(&event.rawSDLEvent);

    for (auto it = eventListeners.begin(); it != eventListeners.end(); it++) {
        (*it)->update(&event);
    }
}