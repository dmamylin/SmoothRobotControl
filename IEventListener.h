#ifndef I_EVENT_LISTENER_H
#define I_EVENT_LISTENER_H

#include "IEvent.h"

class IEventListener {
public:
    virtual ~IEventListener() {}

    virtual void update(const IEvent*) = 0;
};

#endif