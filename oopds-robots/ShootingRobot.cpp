#include "ShootingRobot.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

ShootingRobot:: ShootingRobot()
: ammo(5)
{
    srand(time(0));
}

ShootingRobot::~ShootingRobot()
{
}

ShootingRobot::ShootingRobot(const ShootingRobot &other): ammo(other.ammo)
{
}

ShootingRobot &ShootingRobot::operator=(const ShootingRobot &rhs)
{
    if (this == &rhs)
        return *this;

    ammo = rhs.ammo;
    return *this;
}

void ShootingRobot::actionFire(Battlefield *battlefield)
{
    if (ammo > 0)
    {
        // Fire randomly in one of 8 directions
        int direction =rand() % 8;
        string directions[] ={"up","up-left","up-right","down","down-left","down-right","left","right"};
        cout << "ShootingRobot fires a shot towards " << directions[direction] << "! Ammo left: " << ammo - 1 << endl;
        ammo--;
    }
    if (ammo == 0)
    {
        selfDestruct();
    }
}
void ShootingRobot::selfDestruct()
{
    cout << "ShootingRobot has no ammo left and self-destructs! " << endl;
}

void ShootingRobot::shoot() {
    actionFire(nullptr);
}

