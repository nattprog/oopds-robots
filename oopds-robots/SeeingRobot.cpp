//*********************************************************  
// Program: YOUR_FILENAME.cpp  
// Course: CCP6124 OOPDS 
// Lecture Class: TC2L
// Tutorial Class: TT8L
// Trimester: 2510
// Member_1: 243UC247CZ | ABDULLAH HAKEEM BIN AHMAD KAMAL | ABDULLAH.HAKEEM.AHMAD@student.mmu.edu.my | +6012-4188-300
// Member_2: 242UC244GD | YOSHENAN A/L SHANKER | YOSHENAN .SHANKER@student.mmu.edu.my | PHONE
// Member_3: 243UC2463Z | PRABU NATAR A/L DHARMENDRA | PRABU.NATAR.DHARMENDRA@student.mmu.edu.my | PHONE
// Member_4: 243UC247BM | BONG WEI QIANG, NATHANIEL | BONG.WEI.QIANG@student.mmu.edu.my | +6011-6111-2440	 
//*********************************************************
// Task Distribution
// Member_1: Read from file input. Parse file input as battlefield information, number of robots and robot values (type, id, location).
// Member_2: All robot classes and subclasses, all actionMove, actionLook, actionThink, actionFire, program loop, handling robots vector and queues, inheritance, upgrades, deaths, logging
// Member_3: Output battlefields to txt log output files. Assisted logic for Read from file input.
// Member_4:Read the file start file Write to a file Initializing battleground with robots positions. Base robot class mostly implemented
// ********************************************************
#include "SeeingRobot.h"

SeeingRobot::SeeingRobot()
{
    // ctor
}

SeeingRobot::~SeeingRobot()
{
    // dtor
    for (int i = 0; i < view_.size(); i++)
    {
        if (view_[i])
        {
            delete view_[i];
        }
        view_[i] = nullptr;
    }
}

SeeingRobot::SeeingRobot(const Robot &other)
{
    // copy ctor
}

SeeingRobot &SeeingRobot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}