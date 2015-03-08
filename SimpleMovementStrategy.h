#ifndef SIMPLE_MOVEMENT_STRATEGY_H
#define SIMPLE_MOVEMENT_STRATEGY_H

#include "IMovementStrategy.h"
#include "SimpleMovementData.h"

class SimpleMovementStrategy : public IMovementStrategy {
private:
    SimpleMovementStrategy(const SimpleMovementStrategy&);

public:
    template<class T>
    SimpleMovementStrategy(IMovementData<T>* movementData, f64 precision) :
        IMovementStrategy() {
        this->movementData = movementData;
        this->precision = precision;
    }

    void doStep() {

    }

    bool isDone() {

    }
};

#endif