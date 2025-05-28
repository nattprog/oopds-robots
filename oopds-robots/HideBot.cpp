#include "HideBot.h"
#include "Battlefield.h"

HideBot::HideBot(string id, int x, int y)
{
    // ctor
    id_ = id;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "HideBot";
}

HideBot::~HideBot()
{
    // dtor
}

HideBot::HideBot(const HideBot &other)
{
    // copy ctor
}

HideBot &HideBot::operator=(const HideBot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void HideBot::actionMove(Battlefield *battlefield)
{
    isHidden = false;
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
        if (locationRelativeDistance(foundEnemy) == 1 && HIDE_COUNT > 0)
        {
            isHidden = true;
            HIDE_COUNT--;
            cout << "Hiding. Hidecount left: " << HIDE_COUNT << endl;
        }
        else if (locationRelativeDistance(foundEnemy) > 1)
        {
            setLocation(move_[0]); // move to location that's towards enemy
        }
    }
    else
    {
        setLocation(move_[rand() % (move_.size())]); // random move
    }
    cout << robotType_ << " actionMove" << endl;
};