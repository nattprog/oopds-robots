#ifndef TRACKBOT_H
#define TRACKBOT_H

#include "GenericRobot.h"

class TrackBot : virtual public GenericRobot
{
public:
    TrackBot(string id = "", int x = -1, int y = -1);
    virtual ~TrackBot();
    TrackBot(const Robot &other);
    TrackBot &operator=(const Robot &other);
    virtual void actionLook(Battlefield *battlefield) final;

protected:
    vector<string> trackedBotsIds_;
private:
};

#endif // TRACKBOT_H
