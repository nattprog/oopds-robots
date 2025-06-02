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

#ifndef MOVINGROBOT_H
#define MOVINGROBOT_H

#include "Robot.h"

class MovingRobot : virtual public Robot
{
public:
    MovingRobot();
    virtual ~MovingRobot();
    MovingRobot(const Robot &other);
    MovingRobot &operator=(const Robot &other);

    virtual void actionMove(Battlefield *battlefield) = 0; // Pure virtual function for moving

protected:
    virtual int moveStartCols() = 0;
    virtual int moveStartRows() = 0;

    vector<location *> move_;

private:
};

#endif // MOVINGROBOT_H
