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
#include "ScoutBot.h"
#include "Battlefield.h"

ScoutBot::ScoutBot(string id, string name, int x, int y)
{
    // ctor
    id_ = id;
    robotName_ = name;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "ScoutBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    UPGRADED_SEEINGROBOT_ = robotType_;
}

ScoutBot::~ScoutBot()
{
    // dtor
}

ScoutBot::ScoutBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotName_ = other.robotName();
    numOfKills_ = other.numOfKills();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "ScoutBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    PREV_KILL_ = other.PREV_KILL();
    IS_WAITING_ = other.IS_WAITING();
    UPGRADED_SEEINGROBOT_ = robotType_;

    UPGRADED_MOVINGROBOT_ = other.UPGRADED_MOVINGROBOT();
    UPGRADED_SHOOTINGROBOT_ = other.UPGRADED_SHOOTINGROBOT();
    numOfLives_ = other.numOfLives();
}

ScoutBot &ScoutBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void ScoutBot::actionLook(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionLook" << endl;

    const int startCol = viewStartCols();
    const int startRow = viewStartRows();
    const int viewColsWidth = battlefield->BATTLEFIELD_NUM_OF_COLS();
    const int viewRowsWidth = battlefield->BATTLEFIELD_NUM_OF_ROWS();

    for (size_t i = 0; i < view_.size(); i++)
    {
        if (view_[i])
        {
            delete view_[i];
        }
        view_[i] = nullptr;
    }
    view_.clear();

    string val;
    location *newLoc;

    for (int j = 0; j < viewRowsWidth; j++)
    {
        *battlefield << ">";
        for (int i = 0; i < viewColsWidth; i++)
        {
            const int x = startCol + i;
            const int y = startRow + j;
            val = battlefield->peek(x, y);

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                *battlefield << " " << left << setfill(' ') << setw(4) << id_;
                continue;
            }

            if (val != "") // remove out of bound areas
            {
                newLoc = new location(x, y, val);
                view_.push_back(newLoc);
                *battlefield << " " << left << setfill(' ') << setw(4) << val;
            }
        }

        *battlefield << " " << endl;
    }
}