#include "ShotgunBot.h"
#include "Battlefield.h"

ShotgunBot::ShotgunBot(string id, string name, int x, int y)
{
    // ctor
    id_ = id;
    robotName_ = name;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "ShotgunBot";
    SHOOT_SUCCESS_PERCENTAGE = 40;
    SHELL_COUNT_ = 10;
    UPGRADED_SHOOTINGROBOT_ = robotType_;

    SPREAD_SHOOT_SUCCESS_PERCENTAGE = 10; // 3*10 + 40 = 70
}

ShotgunBot::~ShotgunBot()
{
    // dtor
    for (int i = 0; i < shotgun_spread.size(); i++)
    {
        if (shotgun_spread[i])
        {
            delete shotgun_spread[i];
        }
        shotgun_spread[i] = nullptr;
    }
}

ShotgunBot::ShotgunBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotName_ = other.robotName();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "ShotgunBot";
    SHOOT_SUCCESS_PERCENTAGE = 40;
    SHELL_COUNT_ = 10;
    PREV_KILL_ = other.PREV_KILL();
    IS_WAITING_ = other.IS_WAITING();
    UPGRADED_SHOOTINGROBOT_ = robotType_;

    SPREAD_SHOOT_SUCCESS_PERCENTAGE = 10; // 3*10 + 40 = 70

    UPGRADED_MOVINGROBOT_ = other.UPGRADED_MOVINGROBOT();
    UPGRADED_SEEINGROBOT_ = other.UPGRADED_SEEINGROBOT();
    numOfLives_ = other.numOfLives();
}

ShotgunBot &ShotgunBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void ShotgunBot::actionFire(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionFire" << endl;

    const int startCols = shootStartCols();
    const int startRows = shootStartRows();
    const int shootColsWidth = 3;
    const int shootRowsWidth = 3;
    setPREV_KILL(false);
    bool temp;

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

    for (int i = 0; i < shotgun_spread.size(); i++)
    {
        if (shotgun_spread[i])
        {
            delete shotgun_spread[i];
        }
        shotgun_spread[i] = nullptr;
    }
    shotgun_spread.clear();

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
            if (SHELL_COUNT_ > 0)
            {
                temp = battlefield->strike(shoot_[0]->locX, shoot_[0]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
                if (temp)
                {
                    setPREV_KILL(true);
                }
                setShotgunSpread(shoot_[0]);
                for (auto a : shotgun_spread)
                {
                    if (battlefield->isValidFireLocation(a->locX, a->locY))
                    {
                        temp = battlefield->strike(a->locX, a->locY, SPREAD_SHOOT_SUCCESS_PERCENTAGE, this);
                        if (temp)
                        {
                            setPREV_KILL(true);
                        }
                    }
                }
                SHELL_COUNT_--;
            }
        }
    }
    else
    {
        if (SHELL_COUNT_ > 0)
        {
            const int randIndex = rand() % (shoot_.size());
            temp = battlefield->strike(shoot_[randIndex]->locX, shoot_[randIndex]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
            if (temp)
            {
                setPREV_KILL(true);
            }
            setShotgunSpread(shoot_[randIndex]);
            for (auto a : shotgun_spread)
            {
                if (battlefield->isValidFireLocation(a->locX, a->locY))
                {
                    temp = battlefield->strike(a->locX, a->locY, SPREAD_SHOOT_SUCCESS_PERCENTAGE, this);
                    if (temp)
                    {
                        setPREV_KILL(true);
                    }
                }
            }
            SHELL_COUNT_--;
        }
    }
}

void ShotgunBot::setShotgunSpread(location *shootLoc)
{
    int relx = shootLoc->locX - robotPositionX;
    int rely = shootLoc->locY - robotPositionY;
    if (relx > 0)
    {
        relx = 1;
    }
    else if (relx < 0)
    {
        relx = -1;
    };

    if (rely > 0)
    {
        rely = 1;
    }
    else if (rely < 0)
    {
        rely = -1;
    }

    if (!relx) // top bottom
    {
        /*
        T = target
        R = self
        X = shotgun spread
        top side:
        **X**
        *XTX*
        **R**
        *****
        *****

        */
        shotgun_spread.push_back(new location(shootLoc->locX, shootLoc->locY + rely));
        shotgun_spread.push_back(new location(shootLoc->locX + 1, shootLoc->locY));
        shotgun_spread.push_back(new location(shootLoc->locX - 1, shootLoc->locY));
    }
    else if (!rely) // left right
    {
        /*
        T = target
        R = self
        X = shotgun spread
        left side:
        *****
        *X***
        XTR**
        *X***
        *****

        */

        shotgun_spread.push_back(new location(shootLoc->locX + relx, shootLoc->locY));
        shotgun_spread.push_back(new location(shootLoc->locX, shootLoc->locY + 1));
        shotgun_spread.push_back(new location(shootLoc->locX, shootLoc->locY - 1));
    }
    else if (relx && rely) // corners
    {
        /*
        T = target
        R = self
        X = shotgun spread
        top left side:
        XX***
        XT***
        **R**
        *****
        *****

        */
        shotgun_spread.push_back(new location(shootLoc->locX + relx, shootLoc->locY + rely));
        shotgun_spread.push_back(new location(shootLoc->locX + relx, shootLoc->locY));
        shotgun_spread.push_back(new location(shootLoc->locX, shootLoc->locY + rely));
    }
}