#include "GenericRobot.h"
#include "Battlefield.h"

GenericRobot::GenericRobot(string id, int x, int y)
{
    id_ = id;
    robotPositionX = x;
    robotPositionY = y;
    robotAutoIncrementInt_++;
    robotType_ = "GenericRobot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT = 10;
}

GenericRobot::~GenericRobot()
{
    // dtor
}

GenericRobot::GenericRobot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "GenericRobot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT = 10;
    PREV_KILL_ = other.PREV_KILL();

    UPGRADED_MOVINGROBOT_ = other.UPGRADED_MOVINGROBOT();
    UPGRADED_SHOOTINGROBOT_ = other.UPGRADED_SHOOTINGROBOT();
    UPGRADED_SEEINGROBOT_ = other.UPGRADED_SEEINGROBOT();
    numOfLives_ = other.numOfLives();
}

GenericRobot &GenericRobot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void GenericRobot::setLocation(int x, int y)
{
    robotPositionX = x;
    robotPositionY = y;
}

void GenericRobot::actions(Battlefield *battlefield)
{
    // getting a random number from 0 to 5
    int randomActionThink = rand();

    // executing actions based on random number genned. (Robot always has to think and look first)
    if (randomActionThink % 2 == 0)
    {
        actionThink(battlefield);
        actionLook(battlefield);
        actionFire(battlefield);
        battlefield->placeRobots();
        actionMove(battlefield);
        battlefield->placeRobots();
    }
    else if (randomActionThink % 2 == 1)
    {
        actionThink(battlefield);
        actionLook(battlefield);
        actionMove(battlefield);
        battlefield->placeRobots();
        actionFire(battlefield);
        battlefield->placeRobots();
    }
    if (SHELL_COUNT <= 0)
    {
        battlefield->selfDestruct(this);
    }
}

int GenericRobot::robotAutoIncrementInt() { return robotAutoIncrementInt_; }

void GenericRobot::actionThink(Battlefield *battlefield)
{
    cout << robotType_ << " actionThink" << endl;
}

void GenericRobot::actionLook(Battlefield *battlefield)
{
    cout << robotType_ << " actionLook" << endl;

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
}

void GenericRobot::actionMove(Battlefield *battlefield)
{
    cout << robotType_ << " actionMove" << endl;

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
            setLocation(move_[0]->locX, move_[0]->locY); // move to location that's towards enemy
        }
    }
    else
    {
        const int randIndex = rand() % (move_.size());
        setLocation(move_[randIndex]->locX, move_[randIndex]->locY); // random move
    }
}

int GenericRobot::robotAutoIncrementInt_ = 0;

void GenericRobot::actionFire(Battlefield *battlefield)
{
    cout << robotType_ << " actionFire" << endl;
    const int startCols = shootStartCols();
    const int startRows = shootStartRows();
    const int shootColsWidth = 3;
    const int shootRowsWidth = 3;
    bool temp = false;
    setPREV_KILL(false);

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
                temp = battlefield->bomb(shoot_[0]->locX, shoot_[0]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
                SHELL_COUNT--;
            }
        }
    }
    else
    {
        if (SHELL_COUNT > 0)
        {
            const int randIndex = rand() % (shoot_.size());
            temp = battlefield->bomb(shoot_[randIndex]->locX, shoot_[randIndex]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
            SHELL_COUNT--;
            if (temp)
            {
                setPREV_KILL(true);
            }
        }
    }
}