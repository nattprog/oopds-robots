#include "SemiAutoBot.h"
#include "Battlefield.h"

SemiAutoBot::SemiAutoBot(string id, int x, int y)
{
    // ctor
    id_ = id;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "SemiAutoBot";
    SHELL_COUNT = 10;
    UPGRADED_SHOOTINGROBOT_ = robotType_;
}

SemiAutoBot::~SemiAutoBot()
{
    // dtor
}

SemiAutoBot::SemiAutoBot(const SemiAutoBot &other)
{
    // copy ctor
}

SemiAutoBot &SemiAutoBot::operator=(const SemiAutoBot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void SemiAutoBot::actionFire(Battlefield *battlefield)
{
    cout << robotType_ << " actionFire" << endl;

    const int startCols = shootStartCols();
    const int startRows = shootStartRows();
    const int shootColsWidth = 3;
    const int shootRowsWidth = 3;

    // clear previous round valid move locations
    for (size_t i = 0; i < shoot_.size(); i++)
    {
        if (shoot_[i])
        {
            delete shoot_[i];
        }
        shoot_[i] = nullptr;
    }
    shoot_.clear();

    // find valid move locations
    location *newLoc;
    for (int j = 0; j < shootRowsWidth; j++)
    {
        for (int i = 0; i < shootColsWidth; i++)
        {
            const int x = startCols + i;
            const int y = startRows + j;

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                continue;
            }

            if (battlefield->isValidFireLocation(x, y)) // remove out of bound areas and other robots
            {
                newLoc = new location(x, y);
                shoot_.push_back(newLoc);
            }
        }
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

    // perform shoot based on if foundenemy or not
    if (foundEnemy)
    {
        locationSortVector(shoot_, foundEnemy);
        if (locationRelativeDistanceChebyshev(foundEnemy, shoot_[0]) == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                if (SHELL_COUNT > 0)
                {
                    battlefield->bomb(shoot_[0]->locX, shoot_[0]->locY, SHOOT_SUCCESS_RATE, this); // move to location that's towards enemy
                    SHELL_COUNT--;
                }
            }
        }
    }
    else
    {
        const int randIndex = rand() % (shoot_.size());
        for (int i = 0; i < 3; i++)
        {
            if (SHELL_COUNT > 0)
            {
                battlefield->bomb(shoot_[randIndex]->locX, shoot_[randIndex]->locY, SHOOT_SUCCESS_RATE, this);
                SHELL_COUNT--;
            }
        }
    }
}