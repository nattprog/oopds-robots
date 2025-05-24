#include "GenericRobot.h"

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