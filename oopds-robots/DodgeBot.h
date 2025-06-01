//*********************************************************
// Program: YOUR_FILENAME.cpp
// Course: CCP6124 OOPDS
// Lecture Class: TC2L
// Tutorial Class: TT8L
// Trimester: 2510
// Member_1: 243UC247CZ | ABDULLAH HAKEEM BIN AHMAD KAMAL | ABDULLAH.HAKEEM.AHMAD@student.mmu.edu.my | +6012-4188-300
// Member_2: 242UC244GD | BONG WEI QIANG, NATHANIEL | BONG.WEI.QIANG@student.mmu.edu.my | +6011-6111-2440
// Member_3: 243UC2463Z | PRABU NATAR A/L DHARMENDRA | PRABU.NATAR.DHARMENDRA@student.mmu.edu.my | PHONE
// Member_4: 243UC247BM | YOSHENAN A/L SHANKER | YOSHENAN .SHANKER@student.mmu.edu.my | PHONE
//*********************************************************
// Task Distribution
// Member_1: Read from file input. Parse file input as battlefield information, number of robots and robot values (type, id, location).
// Member_2: All robot classes and subclasses, all actionMove, actionLook, actionThink, actionFire, program loop, handling robots vector and queues, inheritance, upgrades, deaths, logging
// Member_3: Output battlefields to txt log output files. Assisted logic for Read from file input.
// Member_4:Read the file start file Write to a file Initializing battleground with robots positions. Base robot class mostly implemented
// ********************************************************

#ifndef DODGEBOT_H
#define DODGEBOT_H

#include "GenericRobot.h"

class DodgeBot : virtual public GenericRobot
{
public:
    DodgeBot(string id = "", string name = "", int x = -1, int y = -1);
    virtual ~DodgeBot();
    DodgeBot(const Robot &other);
    DodgeBot &operator=(const Robot &other);

    virtual void actionMove(Battlefield *battlefield) final;

protected:
    int DODGE_COUNT;

private:
};

#endif // DODGEBOT_H
