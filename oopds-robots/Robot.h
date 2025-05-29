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
    virtual string id() const
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
        out << r.robotType_ << " " << r.id_ << " at (" << r.robotPositionX << ", " << r.robotPositionY << ")";
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

    class location
    {
    public:
        location(int x, int y, string val = "");
        int locX;
        int locY;
        string value;
    };

    // relative distance between target and object, object defaults to robot's position if unspecified
    int locationRelativeDistance(location *locTarget, location *locObject = nullptr) const;
    // sorts location vector by ascending distance from target, target defaults to robot's position if unspecified.
    void locationSortVector(vector<location *> &locvec, location *locTarget = nullptr);

private:
};

#endif // ROBOT_H
