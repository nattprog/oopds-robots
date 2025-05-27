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

    virtual void actionMove(Battlefield *battlefield) = 0; // Pure virtual function for moving

protected:
    virtual int moveStartCols() = 0;
    virtual int moveStartRows() = 0;

    vector<location *> move_;

private:
};

#endif // MOVINGROBOT_H
