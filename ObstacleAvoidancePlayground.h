#ifndef OBSTACLE_AVOIDANCE_PLAYGROUND_H
#define OBSTACLE_AVOIDANCE_PLAYGROUND_H

struct IEvent;

#include "IPlayground.h"

class ObstacleAvoidancePlayground : public IPlayground {
private:

public:
    void getEvent(const IEvent*);
};

#endif