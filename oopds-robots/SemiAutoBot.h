#ifndef SEMIAUTOBOT_H
#define SEMIAUTOBOT_H

#include "GenericRobot.h"

class SemiAutoBot : virtual public GenericRobot
{
public:
    SemiAutoBot(string id = "", string name = "", int x = -1, int y = -1);
    virtual ~SemiAutoBot();
    SemiAutoBot(const Robot &other);
    SemiAutoBot &operator=(const Robot &other);

    virtual void actionFire(Battlefield *battlefield) final;

protected:
private:
};

#endif // SEMIAUTOBOT_H
