#ifndef SDL2_TIME_COUNTER_H
#define SDL2_TIME_COUNTER_H

#include "ITimeCounter.h"

class SDL2TimeCounter : public ITimeCounter {
public:
    virtual inline s64 getMicroseconds() const { return (s64)getMilliseconds() * 1000; }
    virtual f64 getMilliseconds() const;
    virtual inline f64 getSeconds() const { return getMilliseconds() / 1000.0; }
    virtual inline f64 getMinutes() const { return getSeconds() / 1000.0; }
};

#endif