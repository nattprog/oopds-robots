#include "Battlefield.h"
#include <regex>

Battlefield::Battlefield()
{
    // ctor
    BATTLEFIELD_NUM_OF_ROWS_ = 5;
    BATTLEFIELD_NUM_OF_COLS_ = 5;
    turns_ = 100;
    outputFile.open("output.txt");
    // for (int i = 0; i < BATTLEFIELD_NUM_OF_ROWS_; i++)
    // {
    //     vector<string> a(BATTLEFIELD_NUM_OF_COLS_);
    //     battlefield_.push_back(a);
    // }
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
    outputFile.close();
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
        // increment turn
        turn++;

        // if at the end, or if bot is waiting, go back to start or skip
        justifyIter(robots_Iter);

        placeRobots();

        // respawn any waiting bot in waiting
        respawnWaiting();

        placeRobots();

        displayBattlefield();
        cout << "Turn " << turn << ":" << endl;

        cout << *(*robots_Iter) << endl;

        cout << "-------------------------" << endl;
        (*robots_Iter)->actions(this);

        if ((*robots_Iter)->PREV_KILL())
        {
            (*robots_Iter)->setPREV_KILL(false);
            upgrade(robots_Iter);
        }

        // next robot
        robots_Iter++;

        // ask for next step
        c = getchar();
    }
    cout << "Program terminated." << endl
         << endl;
    cout << "-------------------------" << endl;

    cout << "Turns: " << turn << "/" << turns_ << endl
         << endl;

    cout << "Winner: ";
    if (destroyedRobots_.size() == robots_.size() - 1)
    {
        for (auto a : robots_)
        {
            if (a->isAlive())
            {
                cout << a->id();
                break;
            }
        }
    }
    else
    {
        cout << "None";
    }
    cout << endl
         << endl;
    cout << "Final state:" << endl;
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
    string line, allLines;
    ifstream inputFile;       // file object
    inputFile.open(filename); // file object refers to this file now

    if (!inputFile)
    {
        cout << "File not found." << endl;
    }
    else
    {
        cout << "File found." << endl;
    }

    while (getline(inputFile, line))
    {
        allLines += line;
    }
    inputFile.close();
    /////////////// File Parsing, Assigning Battlefield Size and No. of Turns, Assigning Robot Values  //////////////////////
    smatch fieldMatch;
    smatch turnsMatch;
    smatch roboNumMatch;
    smatch typeMatch;
    int roboX;
    int roboY;

    regex getFieldSize(R"(M by N: (\d+) (\d+)\w*)");  // Regex to get battlefield size from allLines
    regex_search(allLines, fieldMatch, getFieldSize); // searches allLines for match base
    int fieldM = stoi(fieldMatch[1]);                 // X value for field
    int fieldN = stoi(fieldMatch[2]);                 // Y value for field
    // cout << fieldM;

    BATTLEFIELD_NUM_OF_COLS_ = fieldM; // Assigning parsed values for Battlefield size.
    BATTLEFIELD_NUM_OF_ROWS_ = fieldN;

    regex getTurns(R"(\w*(turns: (\d+))\w*)"); // Get number of turns from allLines
    regex_search(allLines, turnsMatch, getTurns);
    turns_ = stoi(turnsMatch[2]); // Assigning parsed values for number of turns.

    regex getnumRobots(R"(robots: (\d+))"); // Get nuber of robots
    regex_search(allLines, roboNumMatch, getnumRobots);
    int numRobots = stoi(roboNumMatch[1]);

    string::const_iterator textStart(allLines.cbegin());                                     // iterator for allLines (maybe separating the robot identifying chunk of text and iterating thru that is better?)
    regex getType(R"((([a-zA-Z]*Robot) (\w{4})\w*\s*([1-9]?[0-9]|\w+) ([1-9]?[0-9]|\w+)))"); // Get all Robot information from allLines
    while (regex_search(textStart, allLines.cend(), typeMatch, getType))
    {
        string roboType = typeMatch[2]; // Robot Type capture group
        string roboName = typeMatch[3]; // Robot Name capture group

        if (typeMatch[4] == "random")
        {
            roboX = (rand() % fieldM);
        }
        else
        {
            roboX = stoi(typeMatch[4]);
        }

        if (typeMatch[5] == "random")
        {
            roboX = (rand() % fieldN);
        }
        else
        {
            roboY = stoi(typeMatch[5]);
        }

        textStart = typeMatch.suffix().first;

        if (roboType == "GenericRobot")
        {
            Robot *newBot = new GenericRobot(roboName, roboX, roboY);
            robots_.push_back(newBot);
            // cout << roboName << roboX << roboY << endl;
        }
        else if (roboType == "HideBot")
        {
            Robot *newBot = new HideBot(roboName, roboX, roboY);
            robots_.push_back(newBot);
        }
        else if (roboType == "JumpBot")
        {
            Robot *newBot = new JumpBot(roboName, roboX, roboY);
        }
        else if (roboType == "ScoutBot")
        {
            Robot *newBot = new ScoutBot(roboName, roboX, roboY);
        }
        else if (roboType == "TrackBot")
        {
            Robot *newBot = new TrackBot(roboName, roboX, roboY);
        }
    }
}

void Battlefield::placeRobots()
{
    if (battlefield_.empty())
    {
        for (int i = 0; i < BATTLEFIELD_NUM_OF_ROWS_; i++)
        {
            vector<string> a(BATTLEFIELD_NUM_OF_COLS_);
            battlefield_.push_back(a);
        }
    }

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

bool Battlefield::strike(int x, int y, int successPercent, Robot *bot)
{
    // success rate is successPercent%
    cout << "> " << bot->id() << " fires at (" << x << ", " << y << ") with a success rate of " << successPercent << "%" << endl;
    string val = peek(x, y);

    if (val == "*" || val == "#" && val == "")
    { // if unsuccessful
        return false;
    }

    Robot *enemy = findRobotById(val);

    if (!enemy)
    {
        return false;
    }

    int random = rand() % 100;
    if (random < successPercent)
    {
        // successful kill
        enemy->reduceLife();

        // if still has lives left, add to waiting
        if (enemy->isAlive())
        {
            cout << *enemy << " has been killed. " << enemy->numOfLives() << " lives remaining." << endl;
            enemy->setIS_WAITING(true);
            waitingRobots_.push(enemy);
        }
        else
        { // else destroyed
            cout << *enemy << " has been destroyed." << endl;
            destroyedRobots_.push(enemy);
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

        (*a)->setIS_WAITING(true);
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
    cout << "Upgrading " << (*botIter)->UPGRADED_MOVINGROBOT() << (*botIter)->UPGRADED_SEEINGROBOT() << (*botIter)->UPGRADED_SHOOTINGROBOT() << " to ";
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

    cout << upgradedClass << endl;

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

void Battlefield::respawnWaiting()
{
    if (!waitingRobots_.empty())
    {
        // getting and popping first item in queue
        Robot *respawningBot = waitingRobots_.front();
        waitingRobots_.pop();

        // {x, y}
        // generating valid respawn locations
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
        // clearing locations
        for (int i = 0; i < validRespawnPoints.size(); i++)
        {
            if (validRespawnPoints[i])
            {
                delete validRespawnPoints[i];
            }
        }

        // setting location to randomised location
        respawningBot->setLocation(x, y);
        vector<Robot *>::iterator rspBotIter = robots_.end();
        for (rspBotIter = robots_.begin(); rspBotIter != robots_.end(); rspBotIter++)
        {
            if (respawningBot == *rspBotIter)
            {
                break;
            }
        }

        if (rspBotIter == robots_.end())
        {
            return;
        }

        // changing to generic robot
        *rspBotIter = new GenericRobot(*respawningBot);
        delete respawningBot;
        respawningBot = nullptr;

        // set waiting to false
        (*rspBotIter)->setIS_WAITING(false);

        cout << "Respawning " << **rspBotIter << endl;
    }
}

void Battlefield::justifyIter(vector<Robot *>::iterator &robots_Iter)
{
    if (robots_Iter == robots_.end())
    {
        robots_Iter = robots_.begin();
    }
    while (!(*robots_Iter)->isAlive() || (*robots_Iter)->IS_WAITING())
    {
        robots_Iter++;
        if (robots_Iter == robots_.end())
        {
            robots_Iter = robots_.begin();
        }
    }
}
