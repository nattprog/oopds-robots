#ifndef SHOOTINGROBOT_H
#define SHOOTINGROBOT_H

#include "Robot.h"

class Battlefield;

class ShootingRobot : virtual public Robot
{
public:
    ShootingRobot();
    virtual ~ShootingRobot();
    ShootingRobot(const ShootingRobot &other);
    ShootingRobot &operator=(const ShootingRobot &other);
    virtual void actionFire(Battlefield *battlefield) = 0; // Pure virtual function for firing

protected:
    virtual int shootStartCols() = 0;
    virtual int shootStartRows() = 0;

    int SHELL_COUNT;
    int SHOOT_SUCCESS_RATE;
    vector<location *> shoot_;
    // void selfDestruct();

private:
};

#endif // SHOOTINGROBOT_H
