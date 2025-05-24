#ifndef HIDEBOT_H
#define HIDEBOT_H

#include "GenericRobot.h"

class HideBot : virtual public GenericRobot
{
public:
    HideBot();
    virtual ~HideBot();
    HideBot(const HideBot &other);
    HideBot &operator=(const HideBot &other);

protected:
private:
};

#endif // HIDEBOT_H
