#ifndef LONGSHOTBOT_H
#define LONGSHOTBOT_H

#include "Robot.h"


class LongShotBot : public Robot
{
    public:
        LongShotBot();
        virtual ~LongShotBot();
        LongShotBot(const LongShotBot& other);
        LongShotBot& operator=(const LongShotBot& other);

    protected:

    private:
};

#endif // LONGSHOTBOT_H
