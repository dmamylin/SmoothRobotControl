#ifndef WINDOWS_TIME_COUNTER_H
#define WINDOWS_TIME_COUNTER_H

#include "ITimeCounter.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class WindowsTimeCounter : public ITimeCounter {
private:
    LARGE_INTEGER frequency;
    LARGE_INTEGER startingTime;

    WindowsTimeCounter(const WindowsTimeCounter&);

public:
    WindowsTimeCounter();
    virtual ~WindowsTimeCounter() {}

    virtual s64 getMicroseconds() const;
    virtual inline f64 getMilliseconds() const { return getMicroseconds() / 1000.0; }
    virtual f64 getSeconds() const { return getMilliseconds() / 1000.0; }
    virtual f64 getMinutes() const { return getSeconds() / 60.0;  }
};

#endif