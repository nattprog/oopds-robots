//*********************************************************
// Program: ASG_CCP6124_2510_TC2L_G03_AbdullahH_BongWeiQiangL_Prabu_Yoshenan.cpp
// Course: CCP6124 OOPDS
// Lecture Class: TC2L
// Tutorial Class: TT8L
// Trimester: 2510
// Member_1: 243UC247CZ | ABDULLAH HAKEEM BIN AHMAD KAMAL | ABDULLAH.HAKEEM.AHMAD@student.mmu.edu.my | +6012-4188-300
// Member_2: 243UC247BM | BONG WEI QIANG, NATHANIEL | BONG.WEI.QIANG@student.mmu.edu.my | +6011-6111-2440
// Member_3: 243UC2463Z | PRABU NATAR A/L DHARMENDRA | PRABU.NATAR.DHARMENDRA@student.mmu.edu.my | +6017-322-0572
// Member_4: 242UC244GD | YOSHENAN A/L SHANKER | YOSHENAN .SHANKER@student.mmu.edu.my | +6011-3310-7367
//*********************************************************
// Task Distribution
// Member_1: Read from file input. Parse file input as battlefield information, number of robots and robot values (type, id, location).
// Member_2: All robot classes and subclasses abilities, Robot, MovingRobot, SeeingRobot, ShootingRobot, ThinkingRobot, GenericRobot, ScoutBot, TrackBot, LongShotBot, SemiAutoBot, ThirtyShotBot, HideBot, JumpBot, DodgeBot, LifeStealBot, ShotgunBot, all actionMove, actionLook, actionThink, actionFire, program loop, handling robots vector and queues, inheritance, polymorphism, operator overloading, operator overloading for battlefield file output, nested class, UML class diagram
// Member_3: Output battlefields to txt log output files. Assisted logic for Read from file input.
// Member_4: Read the file start file Write to a file Initializing battleground with robots positions. Base robot class mostly implemented
// ********************************************************
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
    numOfKills_ = other.numOfKills();
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

    if (SHELL_COUNT_ <= 0) // skip if no more shells
    {
        return;
    }

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
                    incrementKills();
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
                            incrementKills();
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
                incrementKills();
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
                        incrementKills();
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