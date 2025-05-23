#ifndef JUMPBOT_H
#define JUMPBOT_H

#include "GenericRobot.h"

class JumpBot : virtual public GenericRobot
{
public:
    JumpBot();
    virtual ~JumpBot();
    JumpBot(const JumpBot &other);
    JumpBot &operator=(const JumpBot &other);

protected:
private:
};

#endif // JUMPBOT_H
