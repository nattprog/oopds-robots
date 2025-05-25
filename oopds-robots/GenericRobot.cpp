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
    // getting a random number from 0 to 5
    int randomActionThink = rand() % 6;

    actionThink(battlefield);

    // executing actions based on random number genned. 3 randomised actions so 6 total permutations
    switch (randomActionThink)
    {
    case 0:
        actionLook(battlefield);
        actionFire(battlefield);
        actionMove(battlefield);
        break;
    case 1:
        actionLook(battlefield);
        actionMove(battlefield);
        actionFire(battlefield);
        break;
    case 2:
        actionFire(battlefield);
        actionMove(battlefield);
        actionLook(battlefield);
        break;
    case 3:
        actionFire(battlefield);
        actionLook(battlefield);
        actionMove(battlefield);
        break;
    case 4:
        actionMove(battlefield);
        actionLook(battlefield);
        actionFire(battlefield);
        break;
    case 5:
        actionMove(battlefield);
        actionFire(battlefield);
        actionLook(battlefield);
        break;
    default:
        actionLook(battlefield);
        actionFire(battlefield);
        actionMove(battlefield);
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