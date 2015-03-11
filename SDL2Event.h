#ifndef SDL2_EVENT_H
#define SDL2_EVENT_H

#include "types.h"
#include "EventTypes.h"
#include "IEvent.h"

union SDL_Event;

class SDL2Event : public IEvent {
public:
    SDL_Event rawSDLEvent;

    inline s32 getType() const { return EVENT_SDL2;  }
};

#endif