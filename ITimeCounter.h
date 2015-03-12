#ifndef I_TIMER_H
#define I_TIMER_H

#include "types.h"

class ITimeCounter {
public:
    virtual ~ITimeCounter() {}

    virtual s64 getMicroseconds() const = 0;
    virtual f64 getMilliseconds() const = 0;
    virtual f64 getSeconds() const = 0;
    virtual f64 getMinutes() const = 0;
};

#endif