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
    virtual void actionFire(Battlefield *battlefield);  // Pure virtual function for moving
    void shoot();

protected:
    int ammo=0;
    void selfDestruct();
private:
};

#endif // SHOOTINGROBOT_H
