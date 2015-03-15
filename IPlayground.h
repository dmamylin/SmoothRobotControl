#ifndef I_PLAYGROUND_H
#define I_PLAYGROUND_H

struct IEvent;

class IPlayground {
public:
    virtual ~IPlayground() {}

    virtual void getEvent(const IEvent*) = 0;
};

#endif