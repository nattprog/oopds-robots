#ifndef MOVINGROBOT_H
#define MOVINGROBOT_H

#include "Robot.h"

class MovingRobot : virtual public Robot
{
public:
    MovingRobot();
    virtual ~MovingRobot();
    MovingRobot(const MovingRobot &other);
    MovingRobot &operator=(const MovingRobot &other);

protected:
private:
};

#endif // MOVINGROBOT_H
