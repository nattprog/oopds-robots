//*********************************************************
// Program: YOUR_FILENAME.cpp
// Course: CCP6124 OOPDS
// Lecture Class: TC2L
// Tutorial Class: TT8L
// Trimester: 2510
// Member_1: 243UC247CZ | ABDULLAH HAKEEM BIN AHMAD KAMAL | ABDULLAH.HAKEEM.AHMAD@student.mmu.edu.my | +6012-4188-300
// Member_2: 242UC244GD | BONG WEI QIANG, NATHANIEL | BONG.WEI.QIANG@student.mmu.edu.my | +6011-6111-2440
// Member_3: 243UC2463Z | PRABU NATAR A/L DHARMENDRA | PRABU.NATAR.DHARMENDRA@student.mmu.edu.my | PHONE
// Member_4: 243UC247BM | YOSHENAN A/L SHANKER | YOSHENAN .SHANKER@student.mmu.edu.my | PHONE
//*********************************************************
// Task Distribution
// Member_1: Read from file input. Parse file input as battlefield information, number of robots and robot values (type, id, location).
// Member_2: All robot classes and subclasses, all actionMove, actionLook, actionThink, actionFire, program loop, handling robots vector and queues, inheritance, upgrades, deaths, logging
// Member_3: Output battlefields to txt log output files. Assisted logic for Read from file input.
// Member_4:Read the file start file Write to a file Initializing battleground with robots positions. Base robot class mostly implemented
// ********************************************************

#include "DodgeBot.h"
#include "Battlefield.h"

DodgeBot::DodgeBot(string id, string name, int x, int y)
{
    // ctor
    id_ = id;
    robotName_ = name;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "DodgeBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    UPGRADED_MOVINGROBOT_ = robotType_;

    DODGE_COUNT = 3;
}

DodgeBot::~DodgeBot()
{
    // dtor
}

DodgeBot::DodgeBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotName_ = other.robotName();
    numOfKills_ = other.numOfKills();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "DodgeBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    PREV_KILL_ = other.PREV_KILL();
    IS_WAITING_ = other.IS_WAITING();
    UPGRADED_MOVINGROBOT_ = robotType_;

    DODGE_COUNT = 3;

    UPGRADED_SHOOTINGROBOT_ = other.UPGRADED_SHOOTINGROBOT();
    UPGRADED_SEEINGROBOT_ = other.UPGRADED_SEEINGROBOT();
    numOfLives_ = other.numOfLives();
}

DodgeBot &DodgeBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void DodgeBot::actionMove(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionMove" << endl;
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
        *battlefield << "No valid move locations." << endl;
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

        if (DODGE_COUNT > 0) // if still has dodges left
        {
            setLocation(move_.back()->locX, move_.back()->locY); // move to location that's towards enemy
            DODGE_COUNT--;
        } // else do generic robot's actions
        else if (locationRelativeDistanceChebyshev(foundEnemy) > 1)
        {
            setLocation(move_[0]->locX, move_[0]->locY); // move to location that's towards enemy
            *battlefield << "> " << id_ << " moves to position (" << move_[0]->locX << "," << move_[0]->locY << ")" << endl;
        }
    }
    else
    {
        const int randIndex = rand() % (move_.size());
        setLocation(move_[randIndex]->locX, move_[randIndex]->locY); // random move
        *battlefield << "> " << id_ << " moves to position (" << move_[randIndex]->locX << "," << move_[randIndex]->locY << ")" << endl;
    }
}
