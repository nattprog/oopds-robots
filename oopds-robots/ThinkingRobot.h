#ifndef THINKINGROBOT_H
#define THINKINGROBOT_H

#include "Robot.h"

class ThinkingRobot : public Robot
{
public:
    ThinkingRobot();
    virtual ~ThinkingRobot() = 0;
    ThinkingRobot(const ThinkingRobot &other);
    ThinkingRobot &operator=(const ThinkingRobot &other);

protected:
private:
};

#endif // THINKINGROBOT_H
