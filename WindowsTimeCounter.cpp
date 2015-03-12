#include "WindowsTimeCounter.h"

WindowsTimeCounter::WindowsTimeCounter() {
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&startingTime);
}

s64 WindowsTimeCounter::getMicroseconds() const {
    LARGE_INTEGER elapsedTime;
    QueryPerformanceCounter(&elapsedTime);

    elapsedTime.QuadPart -= startingTime.QuadPart;
    elapsedTime.QuadPart *= 1000000;
    elapsedTime.QuadPart /= frequency.QuadPart;

    return (s64)elapsedTime.QuadPart;
}