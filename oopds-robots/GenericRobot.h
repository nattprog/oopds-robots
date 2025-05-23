#ifndef GENERICROBOT_H
#define GENERICROBOT_H

#include "MovingRobot.h"
#include "SeeingRobot.h"
#include "ShootingRobot.h"
#include "ThinkingRobot.h"

class GenericRobot : virtual public MovingRobot, virtual public SeeingRobot, virtual public ShootingRobot, virtual public ThinkingRobot
{
public:
    GenericRobot();
    virtual ~GenericRobot();
    GenericRobot(const GenericRobot &other);
    GenericRobot &operator=(const GenericRobot &other);

protected:
private:
};

#endif // GENERICROBOT_H
