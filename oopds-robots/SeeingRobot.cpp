#include "SeeingRobot.h"

SeeingRobot::SeeingRobot()
{
    // ctor
}

SeeingRobot::~SeeingRobot()
{
    // dtor
    for (int i = 0; i < view_.size(); i++)
    {
        if (view_[i])
        {
            delete view_[i];
        }
        view_[i] = nullptr;
    }
}

SeeingRobot::SeeingRobot(const Robot &other)
{
    // copy ctor
}

SeeingRobot &SeeingRobot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}