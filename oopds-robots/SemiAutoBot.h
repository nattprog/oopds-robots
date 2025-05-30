#ifndef SEMIAUTOBOT_H
#define SEMIAUTOBOT_H

#include "GenericRobot.h"

class SemiAutoBot : virtual public GenericRobot
{
public:
    SemiAutoBot(string id = "", int x = -1, int y = -1);
    virtual ~SemiAutoBot();
    SemiAutoBot(const SemiAutoBot &other);
    SemiAutoBot &operator=(const SemiAutoBot &other);

    virtual void actionFire(Battlefield *battlefield) final;

protected:
private:
};

#endif // SEMIAUTOBOT_H
