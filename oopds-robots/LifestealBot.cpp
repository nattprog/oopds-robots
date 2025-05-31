#include "LifestealBot.h"
#include "Battlefield.h"

LifestealBot::LifestealBot(string id, int x, int y)
{
    // ctor
    id_ = id;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "LifestealBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT = 10;
    UPGRADED_SHOOTINGROBOT_ = robotType_;
}

LifestealBot::~LifestealBot()
{
    // dtor
}

LifestealBot::LifestealBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "LifestealBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT = 10;
    UPGRADED_SHOOTINGROBOT_ = robotType_;

    UPGRADED_MOVINGROBOT_ = other.UPGRADED_MOVINGROBOT();
    UPGRADED_SEEINGROBOT_ = other.UPGRADED_SEEINGROBOT();
    numOfLives_ = other.numOfLives();
}

LifestealBot &LifestealBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void LifestealBot::actionFire(Battlefield *battlefield)
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
            if (SHELL_COUNT > 0)
            {
                Robot *bot = battlefield->bomb(shoot_[0]->locX, shoot_[0]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
                SHELL_COUNT--;
                if (bot)
                {
                    numOfLives_++;
                }
            }
        }
    }
    else
    {
        if (SHELL_COUNT > 0)
        {
            const int randIndex = rand() % (shoot_.size());
            battlefield->bomb(shoot_[randIndex]->locX, shoot_[randIndex]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
            SHELL_COUNT--;
        }
    }
}