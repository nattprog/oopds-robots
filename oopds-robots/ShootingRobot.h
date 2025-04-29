#ifndef SHOOTINGROBOT_H
#define SHOOTINGROBOT_H

#include "Robot.h"

class ShootingRobot : public Robot
{
public:
    ShootingRobot();
    virtual ~ShootingRobot() = 0;
    ShootingRobot(const ShootingRobot &other);
    ShootingRobot &operator=(const ShootingRobot &other);

protected:
private:
};

#endif // SHOOTINGROBOT_H
