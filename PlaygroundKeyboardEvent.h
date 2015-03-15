#ifndef PLAYGROUND_KEYBOARD_EVENT_H
#define PLAYGROUND_KEYBOARD_EVENT_H

#include "IEvent.h"
#include "EventTypes.h"

class PlaygroundKeyboardEvent : public IEvent {
private:

public:
    s32 getType() const { return EVENT_PLAYGROUND_KEYBOARD; }
};

#endif