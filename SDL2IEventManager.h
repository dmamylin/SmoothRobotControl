#ifndef SDL2_I_EVENT_MANAGER_H
#define SDL2_I_EVENT_MANAGER_H

#include "SDL2IEventListener.h"

class SDL2IEventManager {
public:
    virtual ~SDL2IEventManager();

    virtual void addListener(SDL2IEventListener* listener) = 0;
    virtual void removeListener(SDL2IEventListener* listener) = 0;
    virtual void notifyListeners(const SDL_Event& ev) = 0;
};

#endif