#ifndef THIRTYSHOTBOT_H
#define THIRTYSHOTBOT_H

#include "GenericRobot.h"

class ThirtyShotBot : virtual public GenericRobot
{
public:
    ThirtyShotBot(string id = "", int x = -1, int y = -1);
    virtual ~ThirtyShotBot();
    ThirtyShotBot(const ThirtyShotBot &other);
    ThirtyShotBot &operator=(const ThirtyShotBot &other);

    virtual void actionFire(Battlefield *battlefield) final;

protected:
private:
};

#endif // THIRTYSHOTBOT_H
