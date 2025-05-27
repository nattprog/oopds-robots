#include "JumpBot.h"
#include "Battlefield.h"

JumpBot::JumpBot()
{
    // ctor
    SUPERJUMP_COUNT = 3;
}

JumpBot::~JumpBot()
{
    // dtor
}

JumpBot::JumpBot(const JumpBot &other)
{
    // copy ctor
}

JumpBot &JumpBot::operator=(const JumpBot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void JumpBot::actionMove(Battlefield *battlefield)
{

    if (SUPERJUMP_COUNT > 0)
    {
        moveColsWidth = battlefield->BATTLEFIELD_NUM_OF_COLS();
        moveRowsWidth = battlefield->BATTLEFIELD_NUM_OF_ROWS();
    }

    cout << "JumpBot actionMove" << endl;
}