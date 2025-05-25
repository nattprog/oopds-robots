#include "GenericRobot.h"
#include "Battlefield.h"

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

    // executing actions based on random number genned. (Robot always has to think and look first)
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
    const int cols = 3;
    const int rows = 3;
    cout << "GenericRobot actionLook" << endl;
    Location *lookedAt[rows][cols];
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            const int x = robotPositionX + i - 1;
            const int y = robotPositionY + j - 1;
            Location *newLoc = new Location(*this);
            newLoc->value = battlefield->look(x, y);
            newLoc->locX = x;
            newLoc->locY = y;
            lookedAt[j][i] = newLoc;
        }
    }

    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            cout << lookedAt[j][i]->relDistance();
        }
        cout << endl;
    }
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