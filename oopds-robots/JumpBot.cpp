#include "JumpBot.h"
#include "Battlefield.h"

JumpBot::JumpBot()
{
    // ctor
}

JumpBot::~JumpBot()
{
    // dtor
}

JumpBot::JumpBot(const JumpBot &other)
{
    // copy ctor
}

JumpBot &JumpBot::operator=(const JumpBot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void JumpBot::actionMove(Battlefield *battlefield)
{
    int moveStartCols, moveStartRows, moveColsWidth, moveRowsWidth;
    if (SUPERJUMP_COUNT > 0)
    {
        moveStartCols = JumpBot::moveStartCols();
        moveStartRows = JumpBot::moveStartRows();
        moveColsWidth = battlefield->BATTLEFIELD_NUM_OF_COLS();
        moveRowsWidth = battlefield->BATTLEFIELD_NUM_OF_ROWS();
    }
    else
    {
        moveStartCols = GenericRobot::moveStartCols();
        moveStartRows = GenericRobot::moveStartRows();
        moveColsWidth = 3;
        moveRowsWidth = 3;
    }

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
            const int x = moveStartCols + i;
            const int y = moveStartRows + j;

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
    locationSortVector(view_);
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
        locationSortVector(move_, foundEnemy);
        if (locationRelativeDistance(foundEnemy) > 1)
        {
            if (locationRelativeDistance(move_[0]) > 1)
            {
                SUPERJUMP_COUNT--;
            }
            setLocation(move_[0]); // move to location that's towards closest enemy
        }
    }
    else
    {
        location *randloc = move_[rand() % (move_.size())];
        if (locationRelativeDistance(randloc) > 1)
        {
            SUPERJUMP_COUNT--;
        }
        setLocation(randloc); // random move
    }

    cout << "JumpBot actionMove" << endl;
}