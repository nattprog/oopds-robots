#ifndef SCOUTBOT_H
#define SCOUTBOT_H

#include "GenericRobot.h"

class ScoutBot : virtual public GenericRobot
{
public:
    ScoutBot(string id = "", int x = -1, int y = -1);
    virtual ~ScoutBot();
    ScoutBot(const ScoutBot &other);
    ScoutBot &operator=(const ScoutBot &other);
    virtual void actionLook(Battlefield *battlefield) final;

protected:
    virtual int viewStartCols() { return 0; };
    virtual int viewStartRows() { return 0; };

private:
};

#endif // SCOUTBOT_H
