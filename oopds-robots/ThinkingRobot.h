#ifndef THINKINGROBOT_H
#define THINKINGROBOT_H

#include "Robot.h"

class ThinkingRobot : virtual public Robot
{
public:
    ThinkingRobot();
    virtual ~ThinkingRobot();
    ThinkingRobot(const ThinkingRobot &other);
    ThinkingRobot &operator=(const ThinkingRobot &other);

    virtual void actionThink(Battlefield *battlefield) = 0; // Pure virtual function for stepping

protected:
private:
};

#endif // THINKINGROBOT_H
