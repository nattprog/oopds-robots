#ifndef GENERICROBOT_H
#define GENERICROBOT_H

#include "Robot.h"


class GenericRobot : public Robot
{
    public:
        GenericRobot();
        virtual ~GenericRobot();
        GenericRobot(const GenericRobot& other);
        GenericRobot& operator=(const GenericRobot& other);

    protected:

    private:
};

#endif // GENERICROBOT_H
