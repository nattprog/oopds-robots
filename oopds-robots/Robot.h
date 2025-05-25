#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

// class prototypes/forward declarations
class Battlefield;
class GenericRobot;

class Robot
{
public:
    // PC + DC
    Robot(string id = "", int x = -1, int y = -1) : id_(id), robotPositionX(x), robotPositionY(y) {}
    virtual ~Robot();
    Robot(const Robot &other);
    Robot &operator=(const Robot &other);

    // Getter and Setter functions
    int x() const
    {
        return robotPositionX;
    }
    void setX(int x)
    {
        robotPositionX = x;
    }
    int y() const
    {
        return robotPositionY;
    }
    void setY(int y)
    {
        robotPositionY = y;
    }
    string id() const
    {
        return id_;
    }
    void setId(string id)
    {
        id_ = id;
    }
    string robotType() const
    {
        return robotType_;
    }
    void setRobotType(string robotType)
    {
        robotType_ = robotType;
    }
    string robotName() const
    {
        return robotName_;
    }
    void setRobotName(string robotName)
    {
        robotName_ = robotName;
    }
    int numOfLives() const
    {
        return numOfLives_;
    }
    void setNumOfLives(int numOfLives)
    {
        numOfLives_ = numOfLives;
    }
    int numOfKills() const
    {
        return numOfKills_;
    }
    void setNumOfKills(int numOfKills)
    {
        numOfKills_ = numOfKills;
    }
    void reduceLife()
    {
        if (numOfLives_ > 0)
            numOfLives_--;
    }
    void incrementKills()
    {
        numOfKills_++;
    }
    bool isAlive() const
    {
        return numOfLives_ > 0;
    }

    // Overloading the << operator for Robot class
    friend ostream &operator<<(ostream &out, const Robot &r)
    {
        out << r.id_ << " at (" << r.robotPositionX << ", " << r.robotPositionY << ")";
        return out;
    }

    // Pure virtual functions
    virtual void setLocation(int x, int y) = 0;
    virtual void actions(Battlefield *battlefield) = 0;

protected:
    int robotPositionX = -1;
    int robotPositionY = -1;
    string id_ = ""; // eg GRO1, to display robot id on the Battlefield
    string robotType_ = "";
    string robotName_ = ""; // Robot id underscore robot name, eg GROS5_Star
    int numOfLives_ = 3;
    int numOfKills_ = 0;

    class Location
    {
    public:
        Location(Robot &x) : parent(x) {}
        int locX;
        int locY;
        string value;
        int relativeX()
        {
            return locX - parent.robotPositionX;
        }
        int relativeY()
        {
            return locY - parent.robotPositionY;
        }
        int relDistance()
        {
            int dis = 0;
            const int relx = relativeX();
            const int rely = relativeY();
            if (relx < 0)
            {
                dis -= relx;
            }
            else
            {
                dis += relx;
            }
            if (rely < 0)
            {
                dis -= rely;
            }
            else
            {
                dis += rely;
            }
            return dis;
        }

    private:
        Robot &parent;
    };

private:
};

#endif // ROBOT_H
