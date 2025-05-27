#include "GenericRobot.h"
#include "Battlefield.h"

GenericRobot::GenericRobot(string id, int x, int y)
{
    id_ = id;
    robotPositionX = x;
    robotPositionY = y;
    robotAutoIncrementInt_++;
}

GenericRobot::~GenericRobot()
{
    // dtor
}

GenericRobot::GenericRobot(const GenericRobot &other)
{
    // copy ctor
}

GenericRobot &GenericRobot::operator=(const GenericRobot &rhs)
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
        actionMove(battlefield);
    }
    else if (randomActionThink % 2 == 1)
    {
        actionThink(battlefield);
        actionLook(battlefield);
        actionMove(battlefield);
        actionFire(battlefield);
    }
}

int GenericRobot::robotAutoIncrementInt() { return robotAutoIncrementInt_; }

void GenericRobot::actionThink(Battlefield *battlefield)
{
    cout << "GenericRobot actionThink" << endl;
}

void GenericRobot::actionLook(Battlefield *battlefield)
{
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
            val = battlefield->look(x, y);

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
    cout << "GenericRobot actionLook" << endl;
}

void GenericRobot::actionFire(Battlefield *battlefield)
{
    cout << "GenericRobot actionFire" << endl;
}

void GenericRobot::actionMove(Battlefield *battlefield)
{

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
    for (size_t i = 0; i < view_.size(); i++)
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
        if (locationRelativeDistance(foundEnemy) > 1)
        {
            setLocation(move_[0]); // move to location that's towards enemy
        }
    }
    else
    {
        setLocation(move_[rand() % (move_.size())]); // random move
    }
    cout << "GenericRobot actionMove" << endl;
}

int GenericRobot::robotAutoIncrementInt_ = 0;

void GenericRobot::setLocation(location *locPtr)
{
    robotPositionX = locPtr->locX;
    robotPositionY = locPtr->locY;
};

int GenericRobot::locationRelativeDistance(location *locTarget, location *locObject) const
{
    int relx, rely;
    if (locObject)
    {
        relx = locTarget->locX - locObject->locX;
        rely = locTarget->locY - locObject->locY;
    }
    else
    {
        relx = locTarget->locX - robotPositionX;
        rely = locTarget->locY - robotPositionY;
    }
    if (relx < 0)
    {
        relx = -relx;
    }
    if (rely < 0)
    {
        rely = -rely;
    }
    if (relx > rely)
    {
        return relx;
    }
    else
    {
        return rely;
    }
}

// selection sort to sort view vector based on closest to furthest
void GenericRobot::locationSortVector(vector<location *> &locvec, location *locTarget)
{
    const int MAX_MOVE = locvec.size();
    int minIndex, minValue;
    location *temp;
    for (int start = 0; start < (MAX_MOVE - 1); start++)
    {
        minIndex = start;
        minValue = locationRelativeDistance(locvec.at(start), locTarget);
        for (int index = start + 1; index < MAX_MOVE; index++)
        {
            if (locationRelativeDistance(locvec.at(index), locTarget) < minValue)
            {
                minValue = locationRelativeDistance(locvec.at(index), locTarget);
                minIndex = index;
            }
        }
        temp = locvec.at(start);
        locvec.at(start) = locvec.at(minIndex);
        locvec.at(minIndex) = temp;
        temp = nullptr;
    }
}