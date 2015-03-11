#ifndef SDL2_EVENT_MANAGER_H
#define SDL2_EVENT_MANAGER_H

#include "IEventManager.h"

#include <list>

class SDL2EventManager : public IEventManager {
private:
    std::list<IEventListener*> eventListeners;

public:
    void addListener(IEventListener* listener);
    void removeListener(IEventListener* listener);
    void updateListeners();
};

#endif