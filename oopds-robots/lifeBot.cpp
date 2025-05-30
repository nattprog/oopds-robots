#include "lifeBot.h"
#include "Battlefield.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// Constructor
lifeBot::lifeBot(string id, int x, int y)
    : GenericRobot(id, x, y), lifeUpg_(100)  // Starting with 100 health
{
    robotType_ = "lifeBot";
}

// Destructor
lifeBot::~lifeBot() {}

// Copy constructor
lifeBot::lifeBot(const lifeBot &other)
    : GenericRobot(other), lifePoints_(other.lifePoints_)
{
}

// Assignment operator
lifeBot &lifeBot::operator=(const lifeBot &rhs)
{
    if (this == &rhs) return *this;
    GenericRobot::operator=(rhs);
    lifePoints_ = rhs.lifePoints_;
    return *this;
}

// Custom method to upgrade health
void lifeBot::upgradeHealth()
{
    lifeUpg_ += 20; // Example: increase by 20
    cout << "lifeBot upgraded! New health: " << lifePoints_ << endl;
}


void lifeBot::actionFire(Battlefield *battlefield)
{
    cout << robotType_ << " actionFire" << endl;

    // Perform the same logic as GenericRobot::actionFire, but with a hit check
    const int startCols = shootStartCols();
    const int startRows = shootStartRows();
    const int shootColsWidth = 3;
    const int shootRowsWidth = 3;

    // Clear previous round valid move locations
    for (size_t i = 0; i < shoot_.size(); i++)
    {
        if (shoot_[i]) delete shoot_[i];
        shoot_[i] = nullptr;
    }
    shoot_.clear();

    // Find valid shoot locations
    location *newLoc;
    for (int j = 0; j < shootRowsWidth; j++)
    {
        for (int i = 0; i < shootColsWidth; i++)
        {
            const int x = startCols + i;
            const int y = startRows + j;

            if (x == robotPositionX && y == robotPositionY) continue;

            if (battlefield->isValidFireLocation(x, y))
            {
                newLoc = new location(x, y);
                shoot_.push_back(newLoc);
            }
        }
    }

    // Find the closest enemy
    location *foundEnemy = nullptr;
    locationSortVector(view_);
    for (size_t i = 0; i < view_.size() && !foundEnemy; i++)
    {
        if (view_[i]->value != "*" && view_[i]->value != "#")
        {
            foundEnemy = view_[i];
        }
    }

    bool hitEnemy = false;

    if (foundEnemy)
    {
        locationSortVector(shoot_, foundEnemy);
        if (locationRelativeDistance(foundEnemy, shoot_[0]) == 0)
        {
            hitEnemy = battlefield->bomb(shoot_[0]->locX, shoot_[0]->locY, SHOOT_SUCCESS_RATE);
        }
    }
    else if (!shoot_.empty())
    {
        const int randIndex = rand() % shoot_.size();
        setLocation(shoot_[randIndex]->locX, shoot_[randIndex]->locY);
        hitEnemy = battlefield->bomb(shoot_[randIndex]->locX, shoot_[randIndex]->locY, SHOOT_SUCCESS_RATE);
    }

    // Upgrade health based on realistic outcome (hit)
    if (hitEnemy)
    {
        cout << robotType_ << " hit an enemy! Upgrading health." << endl;
        upgradeHealth();
    }
    else
    {
        cout << robotType_ << " missed. No health upgrade." << endl;
    }
}
