#include "DodgeBot.h"
#include "Battlefield.h"

DodgeBot::DodgeBot(string id, int x, int y)
{
    // ctor
    id_ = id;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "DodgeBot";
    SHELL_COUNT = 10;
    DODGE_COUNT = 0;
}

DodgeBot::~DodgeBot()
{
    // dtor
}

DodgeBot::DodgeBot(const DodgeBot &other)
{
    // copy ctor
}

DodgeBot &DodgeBot::operator=(const DodgeBot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void DodgeBot::actionMove(Battlefield *battlefield)
{
    cout << robotType_ << " actionMove" << endl;
    const int startCols = moveStartCols();
    const int startRows = moveStartRows();
    const int moveColsWidth = 3;
    const int moveRowsWidth = 3;

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
            const int x = startCols + i;
            const int y = startRows + j;

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
    for (size_t i = 0; i < view_.size() && !foundEnemy; i++)
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
        setLocation(move_.back()->locX, move_.back()->locY); // move to location that's towards enemy
    }
    else
    {
        const int randIndex = rand() % (move_.size());
        setLocation(move_[randIndex]->locX, move_[randIndex]->locY); // random move
    }
}
