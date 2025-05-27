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
    int moveColsWidth = -1;
    int moveRowsWidth = -1;
    virtual int moveStartCols() = 0;
    virtual int moveStartRows() = 0;

    int moveRelativeDistance(location *locTarget, location *locObject) const;
    void moveSortMove(location *locTarget);
    vector<location *> move_;

private:
};

#endif // MOVINGROBOT_H
