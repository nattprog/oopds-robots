//*********************************************************
// Program: YOUR_FILENAME.cpp
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

#ifndef GENERICROBOT_H
#define GENERICROBOT_H

#include "MovingRobot.h"
#include "SeeingRobot.h"
#include "ShootingRobot.h"
#include "ThinkingRobot.h"

class GenericRobot : virtual public MovingRobot, virtual public SeeingRobot, virtual public ShootingRobot, virtual public ThinkingRobot
{
public:
    friend class HideBot;
    GenericRobot(string id = "", string name = "", int x = -1, int y = -1);

    virtual ~GenericRobot();
    GenericRobot(const Robot &other);
    GenericRobot &operator=(const Robot &other);

    static int robotAutoIncrementInt();
    virtual void setLocation(int x, int y) override;

    virtual void actionThink(Battlefield *battlefield) override;
    virtual void actionLook(Battlefield *battlefield) override;
    virtual void actionFire(Battlefield *battlefield) override;
    virtual void actionMove(Battlefield *battlefield) override;
    virtual void actions(Battlefield *battlefield) override;

protected:
    virtual int viewStartCols() override { return robotPositionX - 1; }
    virtual int viewStartRows() override { return robotPositionY - 1; }
    virtual int moveStartCols() override { return robotPositionX - 1; }
    virtual int moveStartRows() override { return robotPositionY - 1; }
    virtual int shootStartCols() override { return robotPositionX - 1; }
    virtual int shootStartRows() override { return robotPositionY - 1; }

private:
    static int robotAutoIncrementInt_;
};

#endif // GENERICROBOT_H
