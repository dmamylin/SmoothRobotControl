#include "IEvent.h"
#include "EventTypes.h"

#include "ObstacleAvoidancePlayground.h"

void ObstacleAvoidancePlayground::getEvent(const IEvent* event) {
    switch (event->getType()) {
    case EVENT_PLAYGROUND_KEYBOARD:
        break;

    case EVENT_PLAYGROUND_MOUSE:
        break;

    default:
        break;
    }
}