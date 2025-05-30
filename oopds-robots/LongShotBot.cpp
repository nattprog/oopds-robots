#include "LongShotBot.h"
#include "Battlefield.h"

LongShotBot::LongShotBot(string id, int x, int y)
{
    // ctor
    id_ = id;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "LongShotBot";
    SHELL_COUNT = 10;
}

LongShotBot::~LongShotBot()
{
    // dtor
}

LongShotBot::LongShotBot(const LongShotBot &other)
{
    // copy ctor
}

LongShotBot &LongShotBot::operator=(const LongShotBot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void LongShotBot::actionFire(Battlefield *battlefield)
{

    const int startCols = shootStartCols();
    const int startRows = shootStartRows();
    const int shootColsWidth = 7;
    const int shootRowsWidth = 7;

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
            newLoc = new location(x, y);
            if (battlefield->isValidFireLocation(x, y) && locationRelativeDistanceTaxicab(newLoc) <= 3) // remove out of bound areas and other robots
            {
                cout << "Taxicab distance:" << locationRelativeDistanceTaxicab(newLoc) << endl;
                shoot_.push_back(newLoc);
            }
            else
            {
                delete newLoc;
                newLoc = nullptr;
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

    // perform move based on if foundenemy or not
    if (foundEnemy)
    {
        locationSortVector(shoot_, foundEnemy);
        if (locationRelativeDistanceChebyshev(foundEnemy, shoot_[0]) == 0)
        {
            if (SHELL_COUNT > 0)
            {
                battlefield->bomb(shoot_[0]->locX, shoot_[0]->locY, SHOOT_SUCCESS_RATE); // target enemy
                SHELL_COUNT--;
            }
        }
    }
    else
    {
        if (SHELL_COUNT > 0)
        {
            const int randIndex = rand() % (shoot_.size());
            battlefield->bomb(shoot_[randIndex]->locX, shoot_[randIndex]->locY, SHOOT_SUCCESS_RATE);
            SHELL_COUNT--;
        }
    }

    cout << robotType_ << " actionFire" << endl;
}
