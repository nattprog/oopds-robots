#include "TrackBot.h"
#include "Battlefield.h"

TrackBot::TrackBot(string id, string name, int x, int y)
{
    // ctor
    id_ = id;
    robotName_ = name;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "TrackBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
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
    robotName_ = other.robotName();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "TrackBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
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

                if (trackedBotsIds_.size() < 3 && val != "*" && val != "#") // if still has space to track bots
                {
                    bool AlreadyTracking = false;
                    for (string enemyId : trackedBotsIds_)
                    {
                        if (enemyId == val)
                        {
                            AlreadyTracking = true;
                        }
                    }

                    if (!AlreadyTracking)
                    {
                        trackedBotsIds_.push_back(val);
                    }
                }
            }
        }
        *battlefield << " " << endl;
    }

    locationSortVector(view_);

    for (vector<string>::iterator Idptr = trackedBotsIds_.begin(); Idptr != trackedBotsIds_.end(); Idptr++)
    {
        Robot *enemyPtr = battlefield->findRobotById(*Idptr);
        if (enemyPtr != nullptr && enemyPtr->isAlive())
        {
            if (!enemyPtr->IS_WAITING())
            {
                *battlefield << "> Tracking " << *enemyPtr << endl;
                location *loc = new location(enemyPtr->x(), enemyPtr->x(), enemyPtr->id()); // add robot enemy's position to view, to track in the next move
                view_.push_back(loc);
            }
        }
    }
}
