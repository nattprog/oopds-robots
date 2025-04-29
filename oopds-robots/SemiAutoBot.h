#ifndef SEMIAUTOBOT_H
#define SEMIAUTOBOT_H

#include "Robot.h"


class SemiAutoBot : public Robot
{
    public:
        SemiAutoBot();
        virtual ~SemiAutoBot();
        SemiAutoBot(const SemiAutoBot& other);
        SemiAutoBot& operator=(const SemiAutoBot& other);

    protected:

    private:
};

#endif // SEMIAUTOBOT_H
