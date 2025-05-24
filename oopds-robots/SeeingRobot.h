#ifndef SEEINGROBOT_H
#define SEEINGROBOT_H

#include "Robot.h"

class SeeingRobot : virtual public Robot
{
public:
    SeeingRobot();
    virtual ~SeeingRobot();
    SeeingRobot(const SeeingRobot &other);
    SeeingRobot &operator=(const SeeingRobot &other);

    virtual void actionLook(Battlefield *battlefield) = 0; // Pure virtual function for looking

protected:
private:
};

#endif // SEEINGROBOT_H
