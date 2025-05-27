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
    virtual int viewStartCols() = 0;
    virtual int viewStartRows() = 0;

    vector<location *> view_;

    // view actions
    int viewRelativeX(location *loc) const;
    int viewRelativeY(location *loc) const;

private:
};

#endif // SEEINGROBOT_H
