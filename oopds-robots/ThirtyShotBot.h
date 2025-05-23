#ifndef THIRTYSHOTBOT_H
#define THIRTYSHOTBOT_H

#include "GenericRobot.h"

class ThirtyShotBot : virtual public GenericRobot
{
public:
    ThirtyShotBot();
    virtual ~ThirtyShotBot();
    ThirtyShotBot(const ThirtyShotBot &other);
    ThirtyShotBot &operator=(const ThirtyShotBot &other);

protected:
private:
};

#endif // THIRTYSHOTBOT_H
