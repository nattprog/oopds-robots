#ifndef LONGSHOTBOT_H
#define LONGSHOTBOT_H

#include "GenericRobot.h"

class LongShotBot : virtual public GenericRobot
{
public:
    LongShotBot(string id = "", int x = -1, int y = -1);
    virtual ~LongShotBot();
    LongShotBot(const LongShotBot &other);
    LongShotBot &operator=(const LongShotBot &other);

    virtual void actionFire(Battlefield *battlefield) final;

protected:
    virtual int shootStartCols() override { return robotPositionX - 3; }
    virtual int shootStartRows() override { return robotPositionY - 3; }

private:
};

#endif // LONGSHOTBOT_H
