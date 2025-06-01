#ifndef HIDEBOT_H
#define HIDEBOT_H

#include "GenericRobot.h"

class HideBot : virtual public GenericRobot
{
public:
    HideBot(string id = "", string name = "", int x = -1, int y = -1);
    virtual ~HideBot();
    HideBot(const Robot &other);
    HideBot &operator=(const Robot &other);
    virtual void actionMove(Battlefield *battlefield) final;
    virtual string ApparentId() const
    {
        if (isHidden_)
        {
            return "#";
        }
        else
        {
            return id_;
        }
    }

protected:
    bool isHidden_ = false;
    int HIDE_COUNT = 3;

private:
};

#endif // HIDEBOT_H
