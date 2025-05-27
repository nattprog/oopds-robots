#include "SeeingRobot.h"

SeeingRobot::SeeingRobot()
{
    // ctor
}

SeeingRobot::~SeeingRobot()
{
    // dtor
    for (int i = 0; i < view_.size(); i++)
    {
        if (view_[i])
        {
            delete view_[i];
        }
        view_[i] = nullptr;
    }
}

SeeingRobot::SeeingRobot(const SeeingRobot &other)
{
    // copy ctor
}

SeeingRobot &SeeingRobot::operator=(const SeeingRobot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

int SeeingRobot::viewRelativeX(location *loc) const
{
    return loc->locX - robotPositionX;
}

int SeeingRobot::viewRelativeY(location *loc) const
{
    return loc->locY - robotPositionY;
}

// int SeeingRobot::locationRelativeDistance(location *loc) const
// {
//     int relx = viewRelativeX(loc);
//     int rely = viewRelativeY(loc);
//     if (relx < 0)
//     {
//         relx = -relx;
//     }
//     if (rely < 0)
//     {
//         rely = -rely;
//     }
//     if (relx > rely)
//     {
//         return relx;
//     }
//     else
//     {
//         return rely;
//     }
// }

// // selection sort to sort view vector based on closest to furthest
// void SeeingRobot::viewSortView()
// {
//     const int MAX_VIEW = view_.size();
//     int minIndex, minValue;
//     location *temp;
//     for (int start = 0; start < (MAX_VIEW - 1); start++)
//     {
//         minIndex = start;
//         minValue = locationRelativeDistance(view_.at(start));
//         for (int index = start + 1; index < MAX_VIEW; index++)
//         {
//             if (locationRelativeDistance(view_.at(index)) < minValue)
//             {
//                 minValue = locationRelativeDistance(view_.at(index));
//                 minIndex = index;
//             }
//         }
//         temp = view_.at(start);
//         view_.at(start) = view_.at(minIndex);
//         view_.at(minIndex) = temp;
//         temp = nullptr;
//     }
// }