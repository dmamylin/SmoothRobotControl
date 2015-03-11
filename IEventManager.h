#ifndef I_EVENT_MANAGER_H
#define I_EVENT_MANAGER_H

#include "IEvent.h"
#include "IEventListener.h"

class IEventManager {
public:
    virtual ~IEventManager() {}

    virtual void addListener(IEventListener*) = 0;
    virtual void removeListener(IEventListener*) = 0;
    virtual void updateListeners() = 0;
};

#endif