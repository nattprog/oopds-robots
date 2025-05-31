#ifndef LIFESTEALBOT_H
#define LIFESTEALBOT_H

#include "GenericRobot.h"

class LifestealBot : virtual public GenericRobot
{
public:
    LifestealBot(string id = "", int x = -1, int y = -1);
    virtual ~LifestealBot();
    LifestealBot(const Robot &other);
    LifestealBot &operator=(const Robot &other);

    virtual void actionFire(Battlefield *battlefield) override;

protected:
private:
};

#endif // LIFESTEALBOT_H
