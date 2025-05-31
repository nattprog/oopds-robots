#include "JumpBot.h"
#include "Battlefield.h"

JumpBot::JumpBot(string id, int x, int y)
{
    // ctor
    id_ = id;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "JumpBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT = 10;
    UPGRADED_MOVINGROBOT_ = robotType_;
}

JumpBot::~JumpBot()
{
    // dtor
}

JumpBot::JumpBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "JumpBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT = 10;
    PREV_KILL_ = other.PREV_KILL();
    UPGRADED_MOVINGROBOT_ = robotType_;

    UPGRADED_SHOOTINGROBOT_ = other.UPGRADED_SHOOTINGROBOT();
    UPGRADED_SEEINGROBOT_ = other.UPGRADED_SEEINGROBOT();
    numOfLives_ = other.numOfLives();
}

JumpBot &JumpBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void JumpBot::actionMove(Battlefield *battlefield)
{
    cout << robotType_ << " actionMove" << endl;

    int moveStartCols, moveStartRows, moveColsWidth, moveRowsWidth;
    if (SUPERJUMP_COUNT > 0)
    {
        moveStartCols = JumpBot::moveStartCols();
        moveStartRows = JumpBot::moveStartRows();
        moveColsWidth = battlefield->BATTLEFIELD_NUM_OF_COLS();
        moveRowsWidth = battlefield->BATTLEFIELD_NUM_OF_ROWS();
    }
    else
    {
        moveStartCols = GenericRobot::moveStartCols();
        moveStartRows = GenericRobot::moveStartRows();
        moveColsWidth = 3;
        moveRowsWidth = 3;
    }

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
            const int x = moveStartCols + i;
            const int y = moveStartRows + j;

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
        cout << "No valid move locations." << endl;
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
        if (locationRelativeDistanceChebyshev(foundEnemy) > 1)
        {
            if (locationRelativeDistanceChebyshev(move_[0]) > 1)
            {
                SUPERJUMP_COUNT--;
            }
            setLocation(move_[0]->locX, move_[0]->locY); // move to location that's towards enemy
        }
    }
    else
    {
        location *randloc = move_[rand() % (move_.size())];
        if (locationRelativeDistanceChebyshev(randloc) > 1)
        {
            SUPERJUMP_COUNT--;
        }
        setLocation(randloc->locX, randloc->locY); // random move
    }
}