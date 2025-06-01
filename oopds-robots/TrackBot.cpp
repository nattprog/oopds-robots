#include "TrackBot.h"
#include "Battlefield.h"

TrackBot::TrackBot(string id, int x, int y)
{
    // ctor
    id_ = id;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "TrackBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT = 10;
    UPGRADED_SEEINGROBOT_ = robotType_;
}

TrackBot::~TrackBot()
{
    // dtor
}

TrackBot::TrackBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "TrackBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT = 10;
    PREV_KILL_ = other.PREV_KILL();
    IS_WAITING_ = other.IS_WAITING();
    UPGRADED_SEEINGROBOT_ = robotType_;

    UPGRADED_MOVINGROBOT_ = other.UPGRADED_MOVINGROBOT();
    UPGRADED_SHOOTINGROBOT_ = other.UPGRADED_SHOOTINGROBOT();
    numOfLives_ = other.numOfLives();
}

TrackBot &TrackBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void TrackBot::actionLook(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionLook" << endl;

    const int startCol = viewStartCols();
    const int startRow = viewStartRows();
    const int viewColsWidth = 3;
    const int viewRowsWidth = 3;

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

    // find closest enemy from view
    location *foundEnemy = nullptr;
    locationSortVector(view_);
    for (size_t i = 0; i < view_.size() && !foundEnemy; i++)
    {
        if (view_[i]->value != "*" && view_[i]->value != "#")
        {
            foundEnemy = view_[i];
            Robot *enemyPtr = battlefield->findRobotById(view_[i]->value);

            bool match = false;
            for (Robot *ptr : trackedBots_)
            {
                if (ptr == enemyPtr)
                {
                    match = true;
                }
            }

            if (!match && trackedBots_.size() < 3)
            {
                trackedBots_.insert(trackedBots_.begin(), enemyPtr);
            }
        }
    }

    for (vector<Robot *>::iterator ptr = trackedBots_.begin(); ptr != trackedBots_.end(); ptr++)
    {

        if ((*ptr)->isAlive())
        {
            *battlefield << id_ << " is tracking " << *(*ptr) << endl;
        }
        else
        {
            trackedBots_.erase(ptr);
        }
    }
}
