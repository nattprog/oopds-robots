#ifndef JUMPBOT_H
#define JUMPBOT_H

#include "GenericRobot.h"

class JumpBot : virtual public GenericRobot
{
public:
    JumpBot(string id = "", string name = "", int x = -1, int y = -1);
    virtual ~JumpBot();
    JumpBot(const Robot &other);
    JumpBot &operator=(const Robot &other);
    virtual void actionMove(Battlefield *battlefield) final;

protected:
    int SUPERJUMP_COUNT = 3;
    virtual int moveStartCols() final { return 0; }
    virtual int moveStartRows() final { return 0; }

private:
};

#endif // JUMPBOT_H
