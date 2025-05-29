#include "Robot.h"

Robot::~Robot()
{
    // dtor
}

Robot::Robot(const Robot &other)
{
    // copy ctor
}

Robot &Robot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

Robot::location::location(int x, int y, string val)
{
    locX = x;
    locY = y;
    value = val;
}

int Robot::locationRelativeDistance(location *locTarget, location *locObject) const
{
    int relx, rely;
    if (locObject)
    {
        relx = locTarget->locX - locObject->locX;
        rely = locTarget->locY - locObject->locY;
    }
    else
    {
        relx = locTarget->locX - robotPositionX;
        rely = locTarget->locY - robotPositionY;
    }
    if (relx < 0)
    {
        relx = -relx;
    }
    if (rely < 0)
    {
        rely = -rely;
    }
    if (relx > rely)
    {
        return relx;
    }
    else
    {
        return rely;
    }
}

void Robot::locationSortVector(vector<location *> &locvec, location *locTarget)
{
    const int MAX_MOVE = locvec.size();
    int minIndex, minValue;
    location *temp;
    for (int start = 0; start < (MAX_MOVE - 1); start++)
    {
        minIndex = start;
        minValue = locationRelativeDistance(locvec.at(start), locTarget);
        for (int index = start + 1; index < MAX_MOVE; index++)
        {
            if (locationRelativeDistance(locvec.at(index), locTarget) < minValue)
            {
                minValue = locationRelativeDistance(locvec.at(index), locTarget);
                minIndex = index;
            }
        }
        temp = locvec.at(start);
        locvec.at(start) = locvec.at(minIndex);
        locvec.at(minIndex) = temp;
        temp = nullptr;
    }
}