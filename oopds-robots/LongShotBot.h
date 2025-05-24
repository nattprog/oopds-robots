#ifndef LONGSHOTBOT_H
#define LONGSHOTBOT_H

#include "GenericRobot.h"

class LongShotBot : virtual public GenericRobot
{
public:
    LongShotBot();
    virtual ~LongShotBot();
    LongShotBot(const LongShotBot &other);
    LongShotBot &operator=(const LongShotBot &other);

protected:
private:
};

#endif // LONGSHOTBOT_H
