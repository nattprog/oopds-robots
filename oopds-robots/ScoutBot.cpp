#include "ScoutBot.h"
#include "Battlefield.h"

ScoutBot::ScoutBot(string id, int x, int y)
{
    // ctor
    id_ = id;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "ScoutBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT = 10;
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
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "ScoutBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT = 10;
    PREV_KILL_ = other.PREV_KILL();
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
    cout << robotType_ << " actionLook" << endl;

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
        for (int i = 0; i < viewColsWidth; i++)
        {
            const int x = startCol + i;
            const int y = startRow + j;
            val = battlefield->peek(x, y);

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                continue;
            }

            if (val != "") // remove out of bound areas
            {
                newLoc = new location(x, y, val);
                view_.push_back(newLoc);
            }
        }
    }
}