#include "LongShotBot.h"
#include "Battlefield.h"

LongShotBot::LongShotBot(string id, int x, int y)
{
    // ctor
    id_ = id;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "LongShotBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT = 10;
    UPGRADED_SHOOTINGROBOT_ = robotType_;
}

LongShotBot::~LongShotBot()
{
    // dtor
}

LongShotBot::LongShotBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "LongShotBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT = 10;
    PREV_KILL_ = other.PREV_KILL();
    IS_WAITING_ = other.IS_WAITING();
    UPGRADED_SHOOTINGROBOT_ = robotType_;

    UPGRADED_MOVINGROBOT_ = other.UPGRADED_MOVINGROBOT();
    UPGRADED_SEEINGROBOT_ = other.UPGRADED_SEEINGROBOT();
    numOfLives_ = other.numOfLives();
}

LongShotBot &LongShotBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void LongShotBot::actionFire(Battlefield *battlefield)
{
    cout << robotType_ << " actionFire" << endl;

    const int startCols = shootStartCols();
    const int startRows = shootStartRows();
    const int shootColsWidth = 7;
    const int shootRowsWidth = 7;
    setPREV_KILL(false);
    bool temp = false;

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

    // perform shoot based on if foundenemy or not
    if (foundEnemy)
    {
        locationSortVector(shoot_, foundEnemy);
        if (locationRelativeDistanceChebyshev(foundEnemy, shoot_[0]) == 0)
        {
            if (SHELL_COUNT > 0)
            {
                temp = battlefield->strike(shoot_[0]->locX, shoot_[0]->locY, SHOOT_SUCCESS_PERCENTAGE, this); // target enemy
                SHELL_COUNT--;
                if (temp)
                {
                    setPREV_KILL(true);
                }
            }
        }
    }
    else
    {
        if (SHELL_COUNT > 0)
        {
            const int randIndex = rand() % (shoot_.size());
            temp = battlefield->strike(shoot_[randIndex]->locX, shoot_[randIndex]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
            SHELL_COUNT--;
            if (temp)
            {
                setPREV_KILL(true);
            }
        }
    }
}
