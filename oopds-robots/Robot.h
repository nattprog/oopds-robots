//*********************************************************
// Program: ASG_CCP6124_2510_TC2L_G03_AbdullahH_BongWeiQiangL_Prabu_Yoshenan.cpp
// Course: CCP6124 OOPDS
// Lecture Class: TC2L
// Tutorial Class: TT8L
// Trimester: 2510
// Member_1: 243UC247CZ | ABDULLAH HAKEEM BIN AHMAD KAMAL | ABDULLAH.HAKEEM.AHMAD@student.mmu.edu.my | +6012-4188-300
// Member_2: 243UC247BM | BONG WEI QIANG, NATHANIEL | BONG.WEI.QIANG@student.mmu.edu.my | +6011-6111-2440
// Member_3: 243UC2463Z | PRABU NATAR A/L DHARMENDRA | PRABU.NATAR.DHARMENDRA@student.mmu.edu.my | +6017-322-0572
// Member_4: 242UC244GD | YOSHENAN A/L SHANKER | YOSHENAN .SHANKER@student.mmu.edu.my | +6011-3310-7367
//*********************************************************
// Task Distribution
// Member_1: Read from file input. Parse file input as battlefield information, number of robots and robot values (type, id, location).
// Member_2: All robot classes and subclasses abilities, Robot, MovingRobot, SeeingRobot, ShootingRobot, ThinkingRobot, GenericRobot, ScoutBot, TrackBot, LongShotBot, SemiAutoBot, ThirtyShotBot, HideBot, JumpBot, DodgeBot, LifeStealBot, ShotgunBot, all actionMove, actionLook, actionThink, actionFire, program loop, handling robots vector and queues, inheritance, polymorphism, operator overloading, operator overloading for battlefield file output, nested class, UML class diagram
// Member_3: Output battlefields to txt log output files. Assisted logic for Read from file input.
// Member_4: Read the file start file Write to a file Initializing battleground with robots positions. Base robot class mostly implemented
// ********************************************************

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
    Robot(string id = "", string name = "", int x = -1, int y = -1) : id_(id), robotName_(name), robotPositionX(x), robotPositionY(y) {}
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
    virtual string ApparentId() const
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

    string UPGRADED_MOVINGROBOT() const
    {
        return UPGRADED_MOVINGROBOT_;
    }
    string UPGRADED_SHOOTINGROBOT() const
    {
        return UPGRADED_SHOOTINGROBOT_;
    }
    string UPGRADED_SEEINGROBOT() const
    {
        return UPGRADED_SEEINGROBOT_;
    }

    bool PREV_KILL() const
    {
        return PREV_KILL_;
    }
    void setPREV_KILL(bool a)
    {
        PREV_KILL_ = a;
    }

    bool IS_WAITING() const
    {
        return IS_WAITING_;
    }
    void setIS_WAITING(bool val)
    {
        IS_WAITING_ = val;
    }

    int SHELL_COUNT()
    {
        return SHELL_COUNT_;
    }

protected:
    int robotPositionX = -1;
    int robotPositionY = -1;
    string id_ = ""; // eg GRO1, to display robot id on the Battlefield
    string robotType_ = "";
    string robotName_ = ""; // Robot id underscore robot name, eg GROS5_Star
    int numOfLives_ = 3;
    int numOfKills_ = 0;
    bool PREV_KILL_ = false;
    bool IS_WAITING_ = false;
    string UPGRADED_MOVINGROBOT_ = "";
    string UPGRADED_SHOOTINGROBOT_ = "";
    string UPGRADED_SEEINGROBOT_ = "";
    int SHELL_COUNT_;

    class location
    {
    public:
        location(int x, int y, string val = "");
        int locX;
        int locY;
        string value;
    };

    // Chebyshev relative distance between target and object, object defaults to robot's position if unspecified
    int locationRelativeDistanceChebyshev(location *locTarget, location *locObject = nullptr) const;
    // Taxicab relative distance between target and object, object defaults to robot's position if unspecified
    int locationRelativeDistanceTaxicab(location *locTarget, location *locObject = nullptr) const;
    // sorts location vector by ascending distance from target, target defaults to robot's position if unspecified.
    void locationSortVector(vector<location *> &locvec, location *locTarget = nullptr);

private:
};

#endif // ROBOT_H
