#ifndef HIDEBOT_H
#define HIDEBOT_H

#include "Robot.h"


class HideBot : public Robot
{
    public:
        HideBot();
        virtual ~HideBot();
        HideBot(const HideBot& other);
        HideBot& operator=(const HideBot& other);

    protected:

    private:
};

#endif // HIDEBOT_H
