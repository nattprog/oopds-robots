#ifndef TRACKBOT_H
#define TRACKBOT_H

#include "GenericRobot.h"

class TrackBot : virtual public GenericRobot
{
public:
    TrackBot();
    virtual ~TrackBot();
    TrackBot(const TrackBot &other);
    TrackBot &operator=(const TrackBot &other);

protected:
private:
};

#endif // TRACKBOT_H
