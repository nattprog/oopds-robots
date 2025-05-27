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
    moveColsWidth = 3;
    moveRowsWidth = 3;
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
    int randomActionThink = rand();

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
    for (size_t i = 0; i < view_.size(); i++)
    {
        if (view_[i])
        {
            delete view_[i];
        }
        view_[i] = nullptr;
    }
    view_.clear();

    string val;
    location *newLoc;

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
                newLoc = new location(x, y, val);
                view_.push_back(newLoc);
            }
        }
    }

    // stubs;
    // for (location*a : view)
    // {
    //     cout << a->locX << " " << a->locY << endl;
    // }
    // cout << endl;
    // for (location*a : view)
    // {
    //     cout << viewRelativeDistance(a);
    // }
    // cout << endl;
    // robotPositionX += 1;
    // robotPositionY += 1;
    // for (location*a : view)
    // {
    //     cout << a->locX << " " << a->locY << endl;
    // }
    // cout << endl;
    // for (location*a : view)
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
    // clear previous round valid move locations
    for (size_t i = 0; i < move_.size(); i++)
    {
        if (move_[i])
        {
            delete move_[i];
        }
        move_[i] = nullptr;
    }
    move_.clear();

    // find valid move locations
    location *newLoc;
    for (int j = 0; j < moveRowsWidth; j++)
    {
        for (int i = 0; i < moveColsWidth; i++)
        {
            const int x = moveStartCols() + i;
            const int y = moveStartRows() + j;

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                continue;
            }

            if (battlefield->isValidMoveLocation(x, y)) // remove out of bound areas and other robots
            {
                newLoc = new location(x, y);
                move_.push_back(newLoc);
            }
        }
    }

    // terminate if no valid move locations
    if (move_.size() == 0)
    {
        cout << "No valid move locations." << endl;
        return;
    }

    // find closest enemy from view
    location *foundEnemy = nullptr;
    for (size_t i = 0; i < view_.size(); i++)
    {
        if (view_[i]->value != "*" && view_[i]->value != "#")
        {
            foundEnemy = view_[i];
        }
    }

    // perform move based on if foundenemy or not
    if (foundEnemy)
    {
        moveSortMove(foundEnemy);
        setLocation(move_[0]);
    }
    else
    {
        setLocation(move_[rand() % (move_.size())]);
    }
    // {
    //     if (viewRelativeX(foundEnemy) != 0)
    //     {
    //         if (viewRelativeX(foundEnemy) > 0)
    //         {
    //             x = robotPositionX + 1;
    //         }
    //         else
    //         {
    //             x = robotPositionX - 1;
    //         }
    //     }
    //     if (viewRelativeY(foundEnemy) != 0)
    //     {
    //         if (viewRelativeY(foundEnemy) > 0)
    //         {
    //             y = robotPositionY + 1;
    //         }
    //         else
    //         {
    //             y = robotPositionY - 1;
    //         }
    //     }
    // }
    // // while (!battlefield->isValidMoveLocation(x, y))
    // // {
    // //     if ()
    // // }

    cout << "GenericRobot actionMove" << endl;
}

int GenericRobot::robotAutoIncrementInt_ = 0;

void GenericRobot::setLocation(location *locPtr)
{
    robotPositionX = locPtr->locX;
    robotPositionY = locPtr->locY;
};
