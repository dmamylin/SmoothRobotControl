#ifndef SDL2_APPLICATION_H
#define SDL2_APPLICATION_H

#include "types.h"
#include "IEventListener.h"
#include "ITimeCounter.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

class SDL2EventManager;

class SDL2Application : public IEventListener {
private:
    SDL_Window* appWindow;
    SDL_Renderer* appRenderer;
    SDL_Surface* appDisplay;
    
    SDL2EventManager* eventManager;

    ITimeCounter* timeCounter;

    bool isRun;

    bool init(s32 windowWidth, s32 windowHeight, const char* windowCaption);
    void cleanup();
    void updateApplication();

    // IEventListener override:
    void update(const IEvent*);

public:
    SDL2Application() :
    appWindow(0),
    appRenderer(0),
    appDisplay(0),
    eventManager(0),
    timeCounter(0),
    isRun(true) {}

    int run(s32 windowWidth, s32 windowHeight, const char* windowCaption);
};

#endif