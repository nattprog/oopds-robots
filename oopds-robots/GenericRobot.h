#ifndef GENERICROBOT_H
#define GENERICROBOT_H

#include "MovingRobot.h"
#include "SeeingRobot.h"
#include "ShootingRobot.h"
#include "ThinkingRobot.h"

class GenericRobot : public MovingRobot, public SeeingRobot, public ShootingRobot, public ThinkingRobot
{
public:
    GenericRobot(string id = "", int x = -1, int y = -1);

    virtual ~GenericRobot();
    GenericRobot(const GenericRobot &other);
    GenericRobot &operator=(const GenericRobot &other);

    static int robotAutoIncrementInt();
    virtual void setLocation(int x, int y);
    virtual void actionThink(Battlefield *battlefield);
    virtual void actionLook(Battlefield *battlefield);
    virtual void actionFire(Battlefield *battlefield);
    virtual void actionMove(Battlefield *battlefield);
    virtual void actions(Battlefield *battlefield);

protected:
    virtual int viewStartCols() override { return robotPositionX - 1; }
    virtual int viewStartRows() override { return robotPositionY - 1; }
    virtual int moveStartCols() override { return robotPositionX - 1; }
    virtual int moveStartRows() override { return robotPositionY - 1; }

private:
    static int robotAutoIncrementInt_;
};

#endif // GENERICROBOT_H
