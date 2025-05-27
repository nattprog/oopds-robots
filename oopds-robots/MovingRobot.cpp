#include "MovingRobot.h"

MovingRobot::MovingRobot()
{
    // ctor
}

MovingRobot::~MovingRobot()
{
    // dtor
    for (int i = 0; i < move_.size(); i++)
    {
        if (move_[i])
        {
            delete move_[i];
        }
        move_[i] = nullptr;
    }
}

MovingRobot::MovingRobot(const MovingRobot &other)
{
    // copy ctor
}

MovingRobot &MovingRobot::operator=(const MovingRobot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}
