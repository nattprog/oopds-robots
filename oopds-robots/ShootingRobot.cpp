#include "ShootingRobot.h"

ShootingRobot::ShootingRobot()
{
    // ctor
}

ShootingRobot::~ShootingRobot()
{
    // dtor
}

ShootingRobot::ShootingRobot(const ShootingRobot &other)
{
    // copy ctor
}

ShootingRobot &ShootingRobot::operator=(const ShootingRobot &rhs)
{
    if (this == &rhs)
        return *this;

    // ammo = rhs.ammo;
    return *this;
}
