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
    int viewColsWidth = -1;
    int viewRowsWidth = -1;
    int viewStartCols() { return robotPositionX - 1; }
    int viewStartRows() { return robotPositionY - 1; }

    vector<location *> view;

    // view actions
    int viewRelativeX(location *loc) const;

    int viewRelativeY(location *loc) const;

    // Chebyshev distance (the max of either X or Y)
    int viewRelativeDistance(location *loc) const;

    void viewSortView();

private:
};

#endif // SEEINGROBOT_H
