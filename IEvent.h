#ifndef I_EVENT_H
#define I_EVENT_H

#include "types.h"

struct IEvent {
    virtual inline ~IEvent() {}
    
    virtual s32 getType() const = 0;
};

#endif