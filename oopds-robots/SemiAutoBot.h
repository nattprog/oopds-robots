#ifndef SEMIAUTOBOT_H
#define SEMIAUTOBOT_H

#include "GenericRobot.h"

class SemiAutoBot : virtual public GenericRobot
{
public:
    SemiAutoBot();
    virtual ~SemiAutoBot();
    SemiAutoBot(const SemiAutoBot &other);
    SemiAutoBot &operator=(const SemiAutoBot &other);

protected:
private:
};

#endif // SEMIAUTOBOT_H
