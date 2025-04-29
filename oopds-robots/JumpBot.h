#ifndef JUMPBOT_H
#define JUMPBOT_H

#include "Robot.h"


class JumpBot : public Robot
{
    public:
        JumpBot();
        virtual ~JumpBot();
        JumpBot(const JumpBot& other);
        JumpBot& operator=(const JumpBot& other);

    protected:

    private:
};

#endif // JUMPBOT_H
