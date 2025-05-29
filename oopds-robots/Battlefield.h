#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "HideBot.h"
#include "JumpBot.h"
#include "LongShotBot.h"
#include "SemiAutoBot.h"
#include "ThirtyShotBot.h"
#include "ScoutBot.h"
#include "TrackBot.h"

using namespace std;

class Battlefield
{

public:
    friend class Robot;
    Battlefield();
    virtual ~Battlefield();
    Battlefield(const Battlefield &other);
    Battlefield &operator=(const Battlefield &other);

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

    string look(int x, int y) const;
    bool isValidMoveLocation(int x, int y) const;
    bool isValidFireLocation(int x, int y, Robot *rbt = nullptr) const;

    void setRobots(vector<Robot *> &vtrRbts);

    Robot *findRobotById(string id);

    Robot *bomb(int x, int y, int successPercent);

protected:
private:
    int BATTLEFIELD_NUM_OF_COLS_ = -1; // x
    int BATTLEFIELD_NUM_OF_ROWS_ = -1; // y
    int turns_ = -1;                   // Total number of turns
    int turn = 0;                      // Current turn number

    int numOfRobots_ = -1; // Number of robots
    vector<Robot *> robots_;
    queue<Robot *> destroyedRobots_;
    queue<Robot *> waitingRobots_;

    // [row][col] or [N][M] or [y][x]
    vector<vector<string>> battlefield_; // 2D vector representing the battlefield
};

#endif // BATTLEFIELD_H
