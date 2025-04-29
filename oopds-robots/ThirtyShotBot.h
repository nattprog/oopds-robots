#ifndef THIRTYSHOTBOT_H
#define THIRTYSHOTBOT_H

#include "Robot.h"


class ThirtyShotBot : public Robot
{
    public:
        ThirtyShotBot();
        virtual ~ThirtyShotBot();
        ThirtyShotBot(const ThirtyShotBot& other);
        ThirtyShotBot& operator=(const ThirtyShotBot& other);

    protected:

    private:
};

#endif // THIRTYSHOTBOT_H
