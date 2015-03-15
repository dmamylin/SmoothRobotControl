#ifndef PLAYGROUND_MOUSE_EVENT_H
#define PLAYGROUND_MOUSE_EVENT_H

#include "IEvent.h"
#include "EventTypes.h"

class PlaygroundMouseEvent : public IEvent {
private:

public:
    s32 getType() const { return EVENT_PLAYGROUND_MOUSE; }
};

#endif