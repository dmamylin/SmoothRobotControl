#ifndef I_MOVEMENT_DATA_H
#define I_MOVEMENT_DATA_H

#include <list>

#include "point2.h"

class IMovementData {
protected:
    std::list<point2p2i> data;

public:
    IMovementData() {}
    virtual ~IMovementData() {}

    virtual point2i getNextTarget() = 0;
    virtual point2i getPreviousTarget() = 0;
    virtual bool isEmpty() = 0;
};

#endif