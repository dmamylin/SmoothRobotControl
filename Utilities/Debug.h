#ifndef DEBUG_H
#define DEBUG_H

#ifdef _MSC_VER
    #include <crtdbg.h>
    #define ASSERT(expr) _ASSERTE(expr)
#else
    #include <assert.h>
    #define ASSERT(expr) assert(expr)
#endif

#endif