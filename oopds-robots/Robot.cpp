#include "Robot.h"

Robot::Robot()
{
    // ctor
}

Robot::~Robot()
{
    // dtor
}

Robot::Robot(const Robot &other)
{
    // copy ctor
}

Robot &Robot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}
