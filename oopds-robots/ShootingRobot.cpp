#include "ShootingRobot.h"

ShootingRobot::ShootingRobot()
{
    // ctor
}

ShootingRobot::~ShootingRobot()
{
    // dtor
    for (int i = 0; i < shoot_.size(); i++)
    {
        if (shoot_[i])
        {
            delete shoot_[i];
        }
        shoot_[i] = nullptr;
    }
}

ShootingRobot::ShootingRobot(const ShootingRobot &other)
{
    // copy ctor
}

ShootingRobot &ShootingRobot::operator=(const ShootingRobot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}
