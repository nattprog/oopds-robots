#include "Battlefield.h"

Battlefield::Battlefield()
{
    // ctor
    BATTLEFIELD_NUM_OF_ROWS_ = 10;
    BATTLEFIELD_NUM_OF_COLS_ = 20;
    for (int i = 0; i < BATTLEFIELD_NUM_OF_ROWS_; i++)
    {
        vector<string> a(BATTLEFIELD_NUM_OF_COLS_);
        battlefield_.push_back(a);
    }
}

Battlefield::~Battlefield()
{
    // dtor
    for (size_t i = 0; i < robots_.size(); i++)
    {
        if (robots_[i])
        {
            delete robots_[i];
        }
        robots_[i] = nullptr;
    }
}

Battlefield::Battlefield(const Battlefield &other)
{
    // copy ctor
}

Battlefield &Battlefield::operator=(const Battlefield &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void Battlefield::MAIN()
{
    char c;
    cout << "Press [Enter] key or enter any key to start." << endl;
    cout << "Enter [q] to quit." << endl
         << endl;
    c = getchar();

    vector<Robot *>::iterator robots_Iter = robots_.begin();

    while (c != 'q' && static_cast<int>(destroyedRobots_.size()) < static_cast<int>(robots_.size()) - 1 && turn < turns_)
    {
        if (!waitingRobots_.empty())
        {
            Robot *respawningBot = waitingRobots_.front();
            waitingRobots_.pop();

            // {x, y}
            vector<int *> validRespawnPoints;
            for (int j = 0; j < BATTLEFIELD_NUM_OF_ROWS_; j++)
            {
                for (int i = 0; i < BATTLEFIELD_NUM_OF_COLS_; i++)
                {
                    if (battlefield_[j][i] == "*")
                    {
                        int *a = new int[2]{i, j};
                        validRespawnPoints.push_back(a);
                    }
                }
            }

            const int rnd = rand() % (validRespawnPoints.size());
            const int x = validRespawnPoints[rnd][0];
            const int y = validRespawnPoints[rnd][1];
            for (int i = 0; i < validRespawnPoints.size(); i++)
            {
                if (validRespawnPoints[i])
                {
                    delete validRespawnPoints[i];
                }
            }
            // cout << "id" << respawningBot->id() << endl;

            respawningBot->setLocation(x, y);
            cout << "Respawning " << *respawningBot << " at (" << x << ", " << y << ")" << endl;
        }

        turn++;
        if (robots_Iter == robots_.end())
        {
            robots_Iter = robots_.begin();
        }
        while (!(*robots_Iter)->isAlive())
        {
            robots_Iter++;
            if (robots_Iter == robots_.end())
            {
                robots_Iter = robots_.begin();
            }
        }

        placeRobots();
        displayBattlefield();
        cout << "Turn " << turn << ":" << endl;

        cout << "-------------------------" << endl;

        cout << *(*robots_Iter) << endl;
        cout << "-------------------------" << endl;
        (*robots_Iter)->actions(this);

        if ((*robots_Iter)->PREV_KILL())
        {
            (*robots_Iter)->setPREV_KILL(false);
            upgrade(robots_Iter);
        }

        robots_Iter++;
        c = getchar();
    }
    cout << "Program terminated. Final state:" << endl;
    if (destroyedRobots_.size() == robots_.size() - 1)
    {
        for (auto a : robots_)
        {
            if (a->isAlive())
            {
                cout << "Winner: " << a->id() << endl;
                break;
            }
        }
    }
    placeRobots();
    displayBattlefield();
}

int Battlefield::BATTLEFIELD_NUM_OF_COLS()
{
    return BATTLEFIELD_NUM_OF_COLS_;
}
int Battlefield::BATTLEFIELD_NUM_OF_ROWS() { return BATTLEFIELD_NUM_OF_ROWS_; }
int Battlefield::turns() { return turns_; }
int Battlefield::numOfRobots() { return numOfRobots_; }

void Battlefield::readFile(string filename)
{
    Robot *g = new GenericRobot("123", 1, 2);
}

void Battlefield::placeRobots()
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
        if (!robots_[i]->isAlive())
        {
            continue;
        }
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

void Battlefield::displayBattlefield() const
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

string Battlefield::peek(int x, int y) const
{
    if (x < 0 || x > (BATTLEFIELD_NUM_OF_COLS_ - 1))
    {
        return "";
    }
    else if (y < 0 || y > (BATTLEFIELD_NUM_OF_ROWS_ - 1))
    {
        return "";
    }
    else
    {
        return battlefield_[y][x];
    }
};

bool Battlefield::isValidMoveLocation(int x, int y) const
{

    if (peek(x, y) == "*")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Battlefield::isValidFireLocation(int x, int y, Robot *rbt) const
{
    const string val = peek(x, y);

    if (val != "")
    {
        if (rbt && val == rbt->id())
        {
            return false;
        }
        return true;
    }
    else
    {
        return false;
    }
};

void Battlefield::setRobots(vector<Robot *> &vtrRbts)
{
    robots_ = vtrRbts;
}

Robot *Battlefield::findRobotById(string id)
{
    for (vector<Robot *>::iterator ptr = robots_.begin(); ptr != robots_.end(); ptr++)
    {
        if ((*ptr)->id() == id)
        {
            return *ptr;
        }
    }
    return nullptr;
}

bool Battlefield::bomb(int x, int y, int successPercent, Robot *bot)
{
    // success rate is successPercent%
    cout << "> " << bot->id() << " fires at (" << x << ", " << y << ") with a success rate of " << successPercent << "%" << endl;
    string val = peek(x, y);

    if (val == "*" || val == "#" && val == "")
    { // if unsuccessful
        return false;
    }

    vector<Robot *>::iterator botIter = robots_.end();
    for (vector<Robot *>::iterator ptr = robots_.begin(); ptr != robots_.end(); ptr++)
    {
        if ((*ptr)->id() == val)
        {
            botIter = ptr;
            break;
        }
    };

    if (botIter == robots_.end())
    {
        return false;
    }

    int random = rand() % 100;
    if (random < successPercent)
    {
        // successful kill
        (*botIter)->reduceLife();

        // if still has lives left, add to waiting
        if ((*botIter)->isAlive())
        {
            cout << *(*botIter) << " has been killed. " << (*botIter)->numOfLives() << " lives remaining." << endl;

            Robot *temp = *botIter;
            *botIter = new GenericRobot(**botIter);
            delete temp;
            temp = nullptr;

            waitingRobots_.push((*botIter));
        }
        else
        { // else destroyed
            cout << *(*botIter) << " has been destroyed." << endl;
            destroyedRobots_.push((*botIter));
        }

        return true;
    }
    return false;
}

void Battlefield::selfDestruct(Robot *bot)
{

    auto a = robots_.begin();
    for (a; a != robots_.end(); a++)
    {
        if (*a == bot)
        {
            break;
        }
    }
    if (a == robots_.end())
    {
        return;
    }

    cout << *bot << " has run out of shells and self-destructed." << endl;
    bot->reduceLife();

    if (bot->isAlive())
    {
        Robot *temp = *a;
        *a = new GenericRobot(**a);
        delete temp;
        temp = nullptr;

        waitingRobots_.push(*a);
    }
    else
    {
        destroyedRobots_.push(bot);

        cout << *bot << " has been destroyed." << endl;
    }
}

void Battlefield::upgrade(vector<Robot *>::iterator botIter)
{
    vector<vector<string>> possibleUpgrades;
    if ((*botIter)->UPGRADED_MOVINGROBOT() == "")
    {
        possibleUpgrades.push_back(MovingRobotUpgrades);
    }
    if ((*botIter)->UPGRADED_SHOOTINGROBOT() == "")
    {
        possibleUpgrades.push_back(ShootingRobotUpgrades);
    }
    if ((*botIter)->UPGRADED_SEEINGROBOT() == "")
    {
        possibleUpgrades.push_back(SeeingRobotUpgrades);
    }

    if (possibleUpgrades.empty())
    {
        return; // terminate if for any reason there's nothing to upgrade
    }
    const vector<string> upgradeAction = possibleUpgrades[rand() % possibleUpgrades.size()]; // randomly choosing which action to upgrade

    const string upgradedClass = upgradeAction[rand() % upgradeAction.size()]; // choosing which upgraded class

    cout << "upgradedClass: " << upgradedClass << endl;

    if (upgradedClass == "HideBot")
    {
        Robot *temp = *botIter;
        *botIter = new HideBot(**botIter);
        delete temp;
        temp = nullptr;
    }
    else if (upgradedClass == "JumpBot")
    {
        Robot *temp = *botIter;
        *botIter = new JumpBot(**botIter);
        delete temp;
        temp = nullptr;
    }
    else if (upgradedClass == "DodgeBot")
    {
        Robot *temp = *botIter;
        *botIter = new DodgeBot(**botIter);
        delete temp;
        temp = nullptr;
    }
    else if (upgradedClass == "LongShotBot")
    {
        Robot *temp = *botIter;
        *botIter = new LongShotBot(**botIter);
        delete temp;
        temp = nullptr;
    }
    else if (upgradedClass == "SemiAutoBot")
    {
        Robot *temp = *botIter;
        *botIter = new SemiAutoBot(**botIter);
        delete temp;
        temp = nullptr;
    }
    else if (upgradedClass == "ThirtyShotBot")
    {
        Robot *temp = *botIter;
        *botIter = new ThirtyShotBot(**botIter);
        delete temp;
        temp = nullptr;
    }
    else if (upgradedClass == "ShotgunBot")
    {
        Robot *temp = *botIter;
        *botIter = new ShotgunBot(**botIter);
        delete temp;
        temp = nullptr;
    }
    else if (upgradedClass == "LifeStealBot")
    {
        Robot *temp = *botIter;
        *botIter = new LifeStealBot(**botIter);
        delete temp;
        temp = nullptr;
    }
    else if (upgradedClass == "ScoutBot")
    {
        *botIter = new ScoutBot(**botIter);
    }
    else if (upgradedClass == "TrackBot")
    {
        *botIter = new TrackBot(**botIter);
    }
}