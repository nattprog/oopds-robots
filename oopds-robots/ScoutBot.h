#ifndef SCOUTBOT_H
#define SCOUTBOT_H

#include "GenericRobot.h"

class ScoutBot : virtual public GenericRobot
{
public:
    ScoutBot();
    virtual ~ScoutBot();
    ScoutBot(const ScoutBot &other);
    ScoutBot &operator=(const ScoutBot &other);

protected:
private:
};

#endif // SCOUTBOT_H
