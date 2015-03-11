#ifndef SDL2_I_EVENT_LISTENER_H
#define SDL2_I_EVENT_LISTENER_H

class SDL2IEventListener {
public:
    virtual ~SDL2IEventListener();

    virtual void update(const SDL_Event&);
};

#endif