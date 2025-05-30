#ifndef LIFESTEALBOT_H
#define LIFESTEALBOT_H

#include "GenericRobot.h"

class LifestealBot : virtual public GenericRobot
{
public:
    LifestealBot(string id = "", int x = -1, int y = -1);
    virtual ~LifestealBot();
    LifestealBot(const LifestealBot &other);
    LifestealBot &operator=(const LifestealBot &other);

    virtual void actionFire(Battlefield *battlefield) override;

protected:
private:
};

#endif // LIFESTEALBOT_H
