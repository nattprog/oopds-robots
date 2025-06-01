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

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "HideBot.h"
#include "JumpBot.h"
#include "LongShotBot.h"
#include "SemiAutoBot.h"
#include "ThirtyShotBot.h"
#include "ScoutBot.h"
#include "TrackBot.h"
#include "DodgeBot.h"
#include "ShotgunBot.h"
#include "LifeStealBot.h"

using namespace std;

class Battlefield
{

public:
    friend class Robot;
    Battlefield();
    virtual ~Battlefield();
    Battlefield(const Battlefield &other);
    Battlefield &operator=(const Battlefield &other);

    void MAIN();

    // Getter functions
    int BATTLEFIELD_NUM_OF_COLS();
    int BATTLEFIELD_NUM_OF_ROWS();
    int turns();
    int numOfRobots();

    // Read input file to initialize battlefield and robots
    void readFile(string filename);

    // Place robots on the battlefield
    void placeRobots();

    // Display the battlefield in the screen
    void displayBattlefield();

    string peek(int x, int y) const;
    bool isValidMoveLocation(int x, int y) const;
    bool isValidFireLocation(int x, int y) const;

    void setRobots(vector<Robot *> &vtrRbts);

    Robot *findRobotById(string id);

    bool strike(int x, int y, int successPercent, Robot *bot);

    void selfDestruct(vector<Robot *>::iterator botIter);

    void upgrade(vector<Robot *>::iterator botIter);

    void respawnWaiting();

    void justifyIter(vector<Robot *>::iterator &robots_Iter);

    // void setBATTLEFIELD_NUM_OF_COLS(int Xvalue) // temo
    // {
    //     BATTLEFIELD_NUM_OF_COLS_ = Xvalue;
    // }
    // void setBATTLEFIELD_NUM_OF_ROWS(int Yvalue) //temp
    // {
    //     BATTLEFIELD_NUM_OF_ROWS_ = Yvalue;
    // }

    template <typename T>
    Battlefield &operator<<(const T &t)
    {
        outputFile << t;
        cout << t;
        return *this;
    }

    Battlefield &operator<<(std::ostream &(*manip)(std::ostream &))
    {
        o_ << manip;
        outputFile << o_.str();
        cout << o_.str();
        o_.str("");
        o_.clear();
        return *this;
    }

protected:
private:
    int BATTLEFIELD_NUM_OF_COLS_ = -1; // x or M
    int BATTLEFIELD_NUM_OF_ROWS_ = -1; // y or N
    int turns_ = -1;                   // Total number of turns
    int turn = 0;                      // Current turn number
    stringstream o_;
    ofstream outputFile;

    int numOfRobots_ = -1; // Number of robots
    vector<Robot *> robots_;
    queue<Robot *> destroyedRobots_;
    queue<Robot *> waitingRobots_;

    // [row][col] or [N][M] or [y][x]
    vector<vector<string>> battlefield_; // 2D vector representing the battlefield

    // list of possible upgrades
    const vector<string> MovingRobotUpgrades = {"HideBot", "JumpBot", "DodgeBot"};
    const vector<string> ShootingRobotUpgrades = {"LongShotBot", "SemiAutoBot", "ThirtyShotBot", "ShotgunBot", "LifeStealBot"};
    const vector<string> SeeingRobotUpgrades = {"ScoutBot", "TrackBot"};
};

#endif // BATTLEFIELD_H
