#ifndef GENERICROBOT_H
#define GENERICROBOT_H

#include "MovingRobot.h"
#include "SeeingRobot.h"
#include "ShootingRobot.h"
#include "ThinkingRobot.h"

#include "Battlefield.h"

class GenericRobot : public MovingRobot, public SeeingRobot, public ShootingRobot, public ThinkingRobot
{
public:
    GenericRobot(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        robotPositionX = x;
        robotPositionY = y;
        robotAutoIncrementInt_++;
    }
    virtual ~GenericRobot();
    GenericRobot(const GenericRobot &other);
    GenericRobot &operator=(const GenericRobot &other);

    static int robotAutoIncrementInt() { return robotAutoIncrementInt_; }
    virtual void setLocation(int x, int y)
    {
        robotPositionX = x;
        robotPositionY = y;
    }
    virtual void actionThink(Battlefield *battlefield);
    virtual void actionLook(Battlefield *battlefield);
    virtual void actionFire(Battlefield *battlefield);
    virtual void actionMove(Battlefield *battlefield);
    virtual void actions(Battlefield *battlefield)
    {
        int randomActionThink = 0;
        if (randomActionThink % 2 == 0)
        {
            actionThink(battlefield);
            actionLook(battlefield);
            actionFire(battlefield);
            actionMove(battlefield);
        }
        else if (randomActionThink % 2 == 1)
        {
            actionThink(battlefield);
            actionLook(battlefield);
            actionMove(battlefield);
            actionFire(battlefield);
        }
    }

protected:
private:
    static int robotAutoIncrementInt_;
};

#endif // GENERICROBOT_H
