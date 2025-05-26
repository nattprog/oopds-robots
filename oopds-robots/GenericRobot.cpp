#include "GenericRobot.h"
#include "Battlefield.h"

GenericRobot::GenericRobot(string id, int x, int y)
{
    id_ = id;
    robotPositionX = x;
    robotPositionY = y;
    robotAutoIncrementInt_++;
    viewColsWidth = 3;
    viewRowsWidth = 3;
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
    for (int i = 0; i < view.size(); i++)
    {
        if (view[i])
        {
            delete view[i];
        }
        view[i] = nullptr;
    }
    view.clear();

    string val;
    viewLocation *newLoc;

    for (int j = 0; j < viewRowsWidth; j++)
    {
        for (int i = 0; i < viewColsWidth; i++)
        {
            const int x = viewStartCols() + i;
            const int y = viewStartRows() + j;
            val = battlefield->look(x, y);

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                continue;
            }

            if (val != "") // remove out of bound areas
            {
                newLoc = new viewLocation(x, y, val);
                view.push_back(newLoc);
            }
        }
    }

    // stubs;
    // for (viewLocation *a : view)
    // {
    //     cout << a->locX << " " << a->locY << endl;
    // }
    // cout << endl;
    // for (viewLocation *a : view)
    // {
    //     cout << viewRelativeDistance(a);
    // }
    // cout << endl;
    // robotPositionX += 1;
    // robotPositionY += 1;
    // for (viewLocation *a : view)
    // {
    //     cout << a->locX << " " << a->locY << endl;
    // }
    // cout << endl;
    // for (viewLocation *a : view)
    // {
    //     cout << viewRelativeDistance(a);
    // }
    // cout << endl;

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