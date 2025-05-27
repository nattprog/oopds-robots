#ifndef HIDEBOT_H
#define HIDEBOT_H

#include "GenericRobot.h"

class HideBot : virtual public GenericRobot
{
public:
    HideBot();
    HideBot(string id = "", int x = -1, int y = -1) : GenericRobot(id, x, y) {};
    virtual ~HideBot();
    HideBot(const HideBot &other);
    HideBot &operator=(const HideBot &other);
    virtual void actionMove(Battlefield *battlefield) final;
    virtual string id() const final
    {
        if (isHidden)
        {
            return "#";
        }
        else
        {
            return id_;
        }
    }

protected:
    bool isHidden = false;
    int HIDE_COUNT = 3;

private:
};

#endif // HIDEBOT_H
