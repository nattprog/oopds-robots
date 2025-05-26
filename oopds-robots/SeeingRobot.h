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
    class viewLocation;
    vector<viewLocation *> view;

    // view actions
    int viewRelativeX(viewLocation *loc) const;

    int viewRelativeY(viewLocation *loc) const;

    // Chebyshev distance (the max of either X or Y)
    int viewRelativeDistance(viewLocation *loc) const;

    void viewSortView();

    class viewLocation
    {
    public:
        viewLocation(int x, int, string val);
        int locX;
        int locY;
        string value;
    };

private:
};

#endif // SEEINGROBOT_H
