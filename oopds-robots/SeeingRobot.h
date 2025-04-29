#ifndef SEEINGROBOT_H
#define SEEINGROBOT_H

#include "Robot.h"

class SeeingRobot : public Robot
{
public:
    SeeingRobot();
    virtual ~SeeingRobot() = 0;
    SeeingRobot(const SeeingRobot &other);
    SeeingRobot &operator=(const SeeingRobot &other);

protected:
private:
};

#endif // SEEINGROBOT_H
