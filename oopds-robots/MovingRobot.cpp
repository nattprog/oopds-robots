#include "MovingRobot.h"

MovingRobot::MovingRobot()
{
    // ctor
}

MovingRobot::~MovingRobot()
{
    // dtor
    for (int i = 0; i < move_.size(); i++)
    {
        if (move_[i])
        {
            delete move_[i];
        }
        move_[i] = nullptr;
    }
}

MovingRobot::MovingRobot(const MovingRobot &other)
{
    // copy ctor
}

MovingRobot &MovingRobot::operator=(const MovingRobot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

int MovingRobot::moveRelativeDistance(location *locTarget, location *locObject) const
{
    int relx = locTarget->locX - locObject->locX;
    int rely = locTarget->locY - locObject->locY;
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

// selection sort to sort view vector based on closest to furthest
void MovingRobot::moveSortMove(location *locTarget)
{
    const int MAX_MOVE = move_.size();
    int minIndex, minValue;
    location *temp;
    for (int start = 0; start < (MAX_MOVE - 1); start++)
    {
        minIndex = start;
        minValue = moveRelativeDistance(move_.at(start), locTarget);
        for (int index = start + 1; index < MAX_MOVE; index++)
        {
            if (moveRelativeDistance(move_.at(index), locTarget) < minValue)
            {
                minValue = moveRelativeDistance(move_.at(index), locTarget);
                minIndex = index;
            }
        }
        temp = move_.at(start);
        move_.at(start) = move_.at(minIndex);
        move_.at(minIndex) = temp;
        temp = nullptr;
    }
}