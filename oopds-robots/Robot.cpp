//*********************************************************
// Program: YOUR_FILENAME.cpp
// Course: CCP6124 OOPDS
// Lecture Class: TC2L
// Tutorial Class: TT8L
// Trimester: 2510
// Member_1: 243UC247CZ | ABDULLAH HAKEEM BIN AHMAD KAMAL | ABDULLAH.HAKEEM.AHMAD@student.mmu.edu.my | +6012-4188-300
// Member_2: 243UC247BM | BONG WEI QIANG, NATHANIEL | BONG.WEI.QIANG@student.mmu.edu.my | +6011-6111-2440
// Member_3: 243UC2463Z | PRABU NATAR A/L DHARMENDRA | PRABU.NATAR.DHARMENDRA@student.mmu.edu.my | +6017-322-0572
// Member_4: 242UC244GD | YOSHENAN A/L SHANKER | YOSHENAN .SHANKER@student.mmu.edu.my | +6011-3310-7367
//*********************************************************
// Task Distribution
// Member_1: Read from file input. Parse file input as battlefield information, number of robots and robot values (type, id, location).
// Member_2: All robot classes and subclasses abilities, Robot, MovingRobot, SeeingRobot, ShootingRobot, ThinkingRobot, GenericRobot, ScoutBot, TrackBot, LongShotBot, SemiAutoBot, ThirtyShotBot, HideBot, JumpBot, DodgeBot, LifeStealBot, ShotgunBot, all actionMove, actionLook, actionThink, actionFire, program loop, handling robots vector and queues, inheritance, polymorphism, operator overloading, operator overloading for battlefield file output, nested class, UML class diagram
// Member_3: Output battlefields to txt log output files. Assisted logic for Read from file input.
// Member_4: Read the file start file Write to a file Initializing battleground with robots positions. Base robot class mostly implemented
// ********************************************************

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

int Robot::locationRelativeDistanceChebyshev(location *locTarget, location *locObject) const
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

int Robot::locationRelativeDistanceTaxicab(location *locTarget, location *locObject) const
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
    return relx + rely;
}

void Robot::locationSortVector(vector<location *> &locvec, location *locTarget)
{
    const int MAX_MOVE = locvec.size();
    int minIndex, minValue;
    location *temp;
    for (int start = 0; start < (MAX_MOVE - 1); start++)
    {
        minIndex = start;
        minValue = locationRelativeDistanceChebyshev(locvec.at(start), locTarget);
        for (int index = start + 1; index < MAX_MOVE; index++)
        {
            if (locationRelativeDistanceChebyshev(locvec.at(index), locTarget) < minValue)
            {
                minValue = locationRelativeDistanceChebyshev(locvec.at(index), locTarget);
                minIndex = index;
            }
        }
        temp = locvec.at(start);
        locvec.at(start) = locvec.at(minIndex);
        locvec.at(minIndex) = temp;
        temp = nullptr;
    }
}