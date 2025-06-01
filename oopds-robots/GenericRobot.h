#ifndef GENERICROBOT_H
#define GENERICROBOT_H

#include "MovingRobot.h"
#include "SeeingRobot.h"
#include "ShootingRobot.h"
#include "ThinkingRobot.h"

class GenericRobot : virtual public MovingRobot, virtual public SeeingRobot, virtual public ShootingRobot, virtual public ThinkingRobot
{
public:
    friend class HideBot;
    GenericRobot(string id = "", string name = "", int x = -1, int y = -1);

    virtual ~GenericRobot();
    GenericRobot(const Robot &other);
    GenericRobot &operator=(const Robot &other);

    static int robotAutoIncrementInt();
    virtual void setLocation(int x, int y) override;

    virtual void actionThink(Battlefield *battlefield) override;
    virtual void actionLook(Battlefield *battlefield) override;
    virtual void actionFire(Battlefield *battlefield) override;
    virtual void actionMove(Battlefield *battlefield) override;
    virtual void actions(Battlefield *battlefield) override;

protected:
    virtual int viewStartCols() override { return robotPositionX - 1; }
    virtual int viewStartRows() override { return robotPositionY - 1; }
    virtual int moveStartCols() override { return robotPositionX - 1; }
    virtual int moveStartRows() override { return robotPositionY - 1; }
    virtual int shootStartCols() override { return robotPositionX - 1; }
    virtual int shootStartRows() override { return robotPositionY - 1; }

private:
    static int robotAutoIncrementInt_;
};

#endif // GENERICROBOT_H
