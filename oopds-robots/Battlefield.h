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
    void displayBattlefield() const;

    string peek(int x, int y) const;
    bool isValidMoveLocation(int x, int y) const;
    bool isValidFireLocation(int x, int y, Robot *rbt = nullptr) const;

    void setRobots(vector<Robot *> &vtrRbts);

    Robot *findRobotById(string id);

    bool strike(int x, int y, int successPercent, Robot *bot);

    void selfDestruct(Robot *bot);

    void upgrade(vector<Robot *>::iterator botIter);

protected:
private:
    int BATTLEFIELD_NUM_OF_COLS_ = -1; // x or M
    int BATTLEFIELD_NUM_OF_ROWS_ = -1; // y or N
    int turns_ = 200;                  // Total number of turns
    int turn = 0;                      // Current turn number

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
