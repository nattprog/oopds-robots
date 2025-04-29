#ifndef TRACKBOT_H
#define TRACKBOT_H

#include "Robot.h"


class TrackBot : public Robot
{
    public:
        TrackBot();
        virtual ~TrackBot();
        TrackBot(const TrackBot& other);
        TrackBot& operator=(const TrackBot& other);

    protected:

    private:
};

#endif // TRACKBOT_H
