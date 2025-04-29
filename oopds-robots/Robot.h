#ifndef ROBOT_H
#define ROBOT_H

class Robot
{
public:
    Robot();
    virtual ~Robot() = 0;
    Robot(const Robot &other);
    Robot &operator=(const Robot &other);

protected:
private:
};

#endif // ROBOT_H
