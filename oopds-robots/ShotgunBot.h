#ifndef SHOTGUNBOT_H
#define SHOTGUNBOT_H

#include "GenericRobot.h"

class ShotgunBot : virtual public GenericRobot
{
public:
    ShotgunBot(string id = "", int x = -1, int y = -1);
    virtual ~ShotgunBot();
    ShotgunBot(const ShotgunBot &other);
    ShotgunBot &operator=(const ShotgunBot &other);

    virtual void actionFire(Battlefield *battlefield) final;

protected:
    int SPREAD_SHOOT_SUCCESS_RATE;
    void setShotgunSpread(location *shootLoc);
    vector<location *> shotgun_spread;

private:
};

#endif // SHOTGUNBOT_H
