#include "GenericRobot.h"

GenericRobot::GenericRobot(string id, int x, int y)
{
    id_ = id;
    robotPositionX = x;
    robotPositionY = y;
    robotAutoIncrementInt_++;
}

GenericRobot::~GenericRobot()
{
    // dtor
}

GenericRobot::GenericRobot(const GenericRobot &other)
{
    // copy ctor
}

GenericRobot &GenericRobot::operator=(const GenericRobot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void GenericRobot::setLocation(int x, int y)
{
    robotPositionX = x;
    robotPositionY = y;
}

void GenericRobot::actions(Battlefield *battlefield)
{
    int randomActionThink = 0;
    if (randomActionThink % 2 == 0)
    {
        actionThink(battlefield);
        actionLook(battlefield);
        actionFire(battlefield);
        actionMove(battlefield);
    }
    else if (randomActionThink % 2 == 1)
    {
        actionThink(battlefield);
        actionLook(battlefield);
        actionMove(battlefield);
        actionFire(battlefield);
    }
}

int GenericRobot::robotAutoIncrementInt() { return robotAutoIncrementInt_; }

void GenericRobot::actionThink(Battlefield *battlefield)
{
    cout << "GenericRobot actionThink" << endl;
}

void GenericRobot::actionLook(Battlefield *battlefield)
{
    cout << "GenericRobot actionLook" << endl;
}
void GenericRobot::actionFire(Battlefield *battlefield)
{
    cout << "GenericRobot actionFire" << endl;
}
void GenericRobot::actionMove(Battlefield *battlefield)
{
    cout << "GenericRobot actionMove" << endl;
}

int GenericRobot::robotAutoIncrementInt_ = 0;