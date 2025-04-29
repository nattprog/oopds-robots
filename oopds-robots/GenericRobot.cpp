#include "GenericRobot.h"

GenericRobot::GenericRobot()
{
    //ctor
}

GenericRobot::~GenericRobot()
{
    //dtor
}

GenericRobot::GenericRobot(const GenericRobot& other)
{
    //copy ctor
}

GenericRobot& GenericRobot::operator=(const GenericRobot& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
