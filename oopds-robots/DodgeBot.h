#ifndef DODGEBOT_H
#define DODGEBOT_H

#include "GenericRobot.h"

class DodgeBot : virtual public GenericRobot
{
public:
    DodgeBot(string id = "", int x = -1, int y = -1);
    virtual ~DodgeBot();
    DodgeBot(const Robot &other);
    DodgeBot &operator=(const Robot &other);

    virtual void actionMove(Battlefield *battlefield) final;

protected:
    int DODGE_COUNT;
private:
};

#endif // DODGEBOT_H
