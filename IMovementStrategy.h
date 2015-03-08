#ifndef I_MOVEMENT_STRATEGY_H
#define I_MOVEMENT_STRATEGY_H

#include "SDL2Types.h"
#include "IVelocityController.h"
#include "IMovementData.h"

class IMovementStrategy{
protected:
    IVelocityController* velocityController;
    IMovementData* movementData;
    f64 precision;

public:
    IMovementStrategy() :
        velocityController(NULL),
        movementData(NULL),
        precision(0.0) {}
    virtual ~IMovementStrategy() {};

    void setPrecision(f64 precision) { this->precision = precision; }

    const IVelocityController* getVelocityController() const { return velocityController; }
    f64 getPrecision() const { return precision; }
    virtual void doStep() = 0;
    virtual bool isDone() = 0;
}

#endif