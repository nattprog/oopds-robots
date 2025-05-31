#include "ThinkingRobot.h"

ThinkingRobot::ThinkingRobot()
{
    // ctor
}

ThinkingRobot::~ThinkingRobot()
{
    // dtor
}

ThinkingRobot::ThinkingRobot(const Robot &other)
{
    // copy ctor
}

ThinkingRobot &ThinkingRobot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}
