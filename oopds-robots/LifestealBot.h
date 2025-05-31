#ifndef LIFESTEALBOT_H
#define LIFESTEALBOT_H

#include "GenericRobot.h"

class LifeStealBot : virtual public GenericRobot
{
public:
    LifeStealBot(string id = "", int x = -1, int y = -1);
    virtual ~LifeStealBot();
    LifeStealBot(const Robot &other);
    LifeStealBot &operator=(const Robot &other);

    virtual void actionFire(Battlefield *battlefield) override;

protected:
private:
};

#endif // LIFESTEALBOT_H
