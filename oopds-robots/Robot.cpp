#include "Robot.h"

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

Robot::location::location(int x, int y, string val)
{
    locX = x;
    locY = y;
    value = val;
}
