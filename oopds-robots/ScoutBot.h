#ifndef SCOUTBOT_H
#define SCOUTBOT_H

#include "Robot.h"


class ScoutBot : public Robot
{
    public:
        ScoutBot();
        virtual ~ScoutBot();
        ScoutBot(const ScoutBot& other);
        ScoutBot& operator=(const ScoutBot& other);

    protected:

    private:
};

#endif // SCOUTBOT_H
