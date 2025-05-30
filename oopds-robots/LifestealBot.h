#ifndef LIFESTEALBOT_H
#define LIFESTEALBOT_H

#include "GenericRobot.h"

class LifestealBot : virtual public GenericRobot
{
public:
    LifestealBot();
    virtual ~LifestealBot();
    LifestealBot(const LifestealBot &other);
    LifestealBot &operator=(const LifestealBot &other);

protected:
private:
};

#endif // LIFESTEALBOT_H
