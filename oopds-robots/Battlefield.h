#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;
#include "Robot.h"

class Battlefield
{

public:
    Battlefield();
    virtual ~Battlefield();
    Battlefield(const Battlefield &other);
    Battlefield &operator=(const Battlefield &other);

    // Getter functions
    int
    BATTLEFIELD_NUM_OF_COLS()
    {
        return BATTLEFIELD_NUM_OF_COLS_;
    }
    int BATTLEFIELD_NUM_OF_ROWS() { return BATTLEFIELD_NUM_OF_ROWS_; }
    int turns() { return turns_; }
    int numOfRobots() { return numOfRobots_; }
    // Read input file to initialize battlefield and robots
    void readFile(string filename)
    {
    }
    // Place robots on the battlefield
    void placeRobots()
    {
        for (unsigned int i = 0; i < battlefield_.size(); ++i)
        {
            for (unsigned int j = 0; j < battlefield_[i].size(); ++j)
            {
                battlefield_[i][j] = "*";
            }
        }
        for (unsigned int i = 0; i < robots_.size(); ++i)
        {
            if (robots_[i]->y() < static_cast<long long int>(battlefield_.size()) && robots_[i]->x() < static_cast<long long int>(battlefield_[0].size()))
            {
                battlefield_[robots_[i]->y()][robots_[i]->x()] =
                    robots_[i]->id();
            }
            else
            {
                std::cout << "Error message: Invalid location for the robot " << robots_[i]->id() << endl;
                exit(1);
            }
        }
    }
    // Display the battlefield in the screen
    void displayBattlefield() const
    {
        std::cout << "Display Battlefield";
        std::cout << endl
                  << "    ";
        for (unsigned int j = 0; j < battlefield_[0].size(); ++j)
        {
            std::cout << "  " << right << setfill('0') << setw(2) << j << " ";
        }
        std::cout << endl;
        for (unsigned int i = 0; i < battlefield_.size(); ++i)
        {
            std::cout << "    ";
            for (unsigned int j = 0; j < battlefield_[i].size(); ++j)
            {
                std::cout << "+----";
            }
            std::cout << "+" << endl;
            std::cout << "  " << right << setfill('0') << setw(2) << i;
            for (unsigned int j = 0; j < battlefield_[0].size(); ++j)
            {
                if (battlefield_[i][j] == "")
                {
                    std::cout << "|" << "    ";
                }
                else
                {
                    std::cout << "|" << left << setfill(' ') << setw(4) << battlefield_[i][j];
                }
            }
            std::cout << "|" << endl;
        }
        std::cout << "    ";
        for (unsigned int j = 0; j < battlefield_[0].size(); ++j)
        {
            std::cout << "+----";
        }
        std::cout << "+" << endl;
    }

protected:
private:
    int BATTLEFIELD_NUM_OF_COLS_ = -1;
    int BATTLEFIELD_NUM_OF_ROWS_ = -1;
    int turns_ = -1; // Total number of turns
    int turn = 0;    // Current turn number

    int numOfRobots_ = -1; // Number of robots
    vector<Robot *> robots_;
    queue<Robot *> destroyedRobots_;
    queue<Robot *> waitingRobots_;

    vector<vector<string>> battlefield_; // 2D vector representing the battlefield
};

#endif // BATTLEFIELD_H
