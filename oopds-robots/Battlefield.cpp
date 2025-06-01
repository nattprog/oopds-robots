#include "Battlefield.h"
#include <regex>

Battlefield::Battlefield()
{
    // ctor

    outputFile.open("output.txt");
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
    *this << "Press [Enter] key or enter any key to start." << endl;
    *this << "Enter [q] to quit." << endl
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
        *this << "Turn " << turn << ":" << endl;

        *this << *(*robots_Iter) << endl;

        *this << "-------------------------" << endl;
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
    *this << "Program terminated." << endl
          << endl;
    *this << "-------------------------" << endl;

    *this << "Turns: " << turn << "/" << turns_ << endl
          << endl;

    *this << "Winner: ";
    if (destroyedRobots_.size() == robots_.size() - 1)
    {
        for (auto a : robots_)
        {
            if (a->isAlive())
            {
                *this << "> " << a->robotType() << " " << a->id() << endl;
                break;
            }
        }
    }
    else
    {
        *this << "None";
    }
    *this << endl
          << endl;
    *this << "Final state:" << endl;
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
        *this << "File not found." << endl;
    }
    else
    {
        *this << "File found." << endl;
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
    //*this << fieldM;

    BATTLEFIELD_NUM_OF_COLS_ = fieldM; // Assigning parsed values for Battlefield size.
    BATTLEFIELD_NUM_OF_ROWS_ = fieldN;

    regex getTurns(R"(\w*(turns: (\d+))\w*)"); // Get number of turns from allLines
    regex_search(allLines, turnsMatch, getTurns);
    turns_ = stoi(turnsMatch[2]); // Assigning parsed values for number of turns.

    regex getnumRobots(R"(robots: (\d+))"); // Get nuber of robots
    regex_search(allLines, roboNumMatch, getnumRobots);
    int numRobots = stoi(roboNumMatch[1]);

    string::const_iterator textStart(allLines.cbegin());                                                           // iterator for allLines (maybe separating the robot identifying chunk of text and iterating thru that is better?)
    regex getType(R"((([a-zA-Z]*[bB]ot) +(([a-zA-Z0-9]{1,4})_\w*) +([1-9]?[0-9]|random) +([1-9]?[0-9]|random)))"); // Get all Robot information from allLines
    while (regex_search(textStart, allLines.cend(), typeMatch, getType))
    {
        int a = 0;
        for (auto i : typeMatch)
        {
            cout << a << " " << i << endl;
            a++;
        }
        string roboType = typeMatch[2]; // Robot Type capture group
        string roboId = typeMatch[4];   // Robot Name capture group

        if (typeMatch[5] == "random")
        {
            roboX = (rand() % fieldM);
        }
        else
        {
            roboX = stoi(typeMatch[5]);
        }

        if (typeMatch[6] == "random")
        {
            roboX = (rand() % fieldN);
        }
        else
        {
            roboY = stoi(typeMatch[6]);
        }

        textStart = typeMatch.suffix().first;

        if (roboType == "GenericRobot")
        {
            Robot *newBot = new GenericRobot(roboId, roboX, roboY);
            robots_.push_back(newBot);
        }
        else if (roboType == "HideBot")
        {
            Robot *newBot = new HideBot(roboId, roboX, roboY);
            robots_.push_back(newBot);
        }
        else if (roboType == "JumpBot")
        {
            Robot *newBot = new JumpBot(roboId, roboX, roboY);
            robots_.push_back(newBot);
        }
        else if (roboType == "DodgeBot")
        {
            Robot *newBot = new DodgeBot(roboId, roboX, roboY);
            robots_.push_back(newBot);
        }
        else if (roboType == "LongShotBot")
        {
            Robot *newBot = new LongShotBot(roboId, roboX, roboY);
            robots_.push_back(newBot);
        }
        else if (roboType == "SemiAutoBot")
        {
            Robot *newBot = new SemiAutoBot(roboId, roboX, roboY);
            robots_.push_back(newBot);
        }
        else if (roboType == "ThirtyShotBot")
        {
            Robot *newBot = new ThirtyShotBot(roboId, roboX, roboY);
            robots_.push_back(newBot);
        }
        else if (roboType == "ShotgunBot")
        {
            Robot *newBot = new ShotgunBot(roboId, roboX, roboY);
            robots_.push_back(newBot);
        }
        else if (roboType == "LifeStealBot")
        {
            Robot *newBot = new LifeStealBot(roboId, roboX, roboY);
            robots_.push_back(newBot);
        }
        else if (roboType == "ScoutBot")
        {
            Robot *newBot = new ScoutBot(roboId, roboX, roboY);
            robots_.push_back(newBot);
        }
        else if (roboType == "TrackBot")
        {
            Robot *newBot = new TrackBot(roboId, roboX, roboY);
            robots_.push_back(newBot);
        }
    }
    cout << "Field size: " << fieldM << ", " << fieldN << endl; // To display at beginning of program
    cout << "Number of robots: " << numRobots << endl;
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
            *this << "Error message: Invalid location for the robot " << robots_[i]->id() << endl;
            exit(1);
        }
    }
}

void Battlefield::displayBattlefield()
{
    *this << "Display Battlefield";
    *this << endl
          << "    ";
    for (unsigned int j = 0; j < battlefield_[0].size(); ++j)
    {
        *this << "  " << right << setfill('0') << setw(2) << j << " ";
    }
    *this << endl;
    for (unsigned int i = 0; i < battlefield_.size(); ++i)
    {
        *this << "    ";
        for (unsigned int j = 0; j < battlefield_[i].size(); ++j)
        {
            *this << "+----";
        }
        *this << "+" << endl;
        *this << "  " << right << setfill('0') << setw(2) << i;
        for (unsigned int j = 0; j < battlefield_[0].size(); ++j)
        {
            if (battlefield_[i][j] == "")
            {
                *this << "|" << "    ";
            }
            else
            {
                *this << "|" << left << setfill(' ') << setw(4) << battlefield_[i][j];
            }
        }
        *this << "|" << endl;
    }
    *this << "    ";
    for (unsigned int j = 0; j < battlefield_[0].size(); ++j)
    {
        *this << "+----";
    }
    *this << "+" << endl;
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
    *this << "> " << bot->id() << " fires at (" << x << ", " << y << ") with a success rate of " << successPercent << "%" << endl;
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
            *this << *enemy << " has been killed. " << enemy->numOfLives() << " lives remaining." << endl;
            enemy->setIS_WAITING(true);
            waitingRobots_.push(enemy);
        }
        else
        { // else destroyed
            *this << *enemy << " has been destroyed." << endl;
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

    *this << *bot << " has run out of shells and self-destructed." << endl;
    bot->reduceLife();

    if (bot->isAlive())
    {
        Robot *temp = *a;
        *a = new GenericRobot(**a);

        (*a)->setIS_WAITING(true);
        waitingRobots_.push(*a);
    }
    else
    {
        destroyedRobots_.push(bot);

        *this << *bot << " has been destroyed." << endl;
    }
}

void Battlefield::upgrade(vector<Robot *>::iterator botIter)
{
    *this << **botIter << "Has already been upgraded to:" << endl;
    if ((*botIter)->UPGRADED_MOVINGROBOT() != "")
    {
        *this << "> MovingRobot: " << (*botIter)->UPGRADED_MOVINGROBOT() << endl;
    }
    if ((*botIter)->UPGRADED_SHOOTINGROBOT() != "")
    {
        *this << "> ShootingRobot: " << (*botIter)->UPGRADED_SHOOTINGROBOT() << endl;
    }
    if ((*botIter)->UPGRADED_SEEINGROBOT() != "")
    {
        *this << "> SeeingRobot: " << (*botIter)->UPGRADED_SEEINGROBOT() << endl;
    }

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
        *this << "No remaining areas to upgrade" << endl;
        return; // terminate if for any reason there's nothing to upgrade
    }
    const vector<string> upgradeAction = possibleUpgrades[rand() % possibleUpgrades.size()]; // randomly choosing which action to upgrade

    const string upgradedClass = upgradeAction[rand() % upgradeAction.size()]; // choosing which upgraded class

    *this << "Upgrading to:" << endl;

    Robot *temp = *botIter;

    if (upgradedClass == "HideBot")
    {
        *botIter = new HideBot(**botIter);
        *this << "> MovingRobot: " << (*botIter)->UPGRADED_MOVINGROBOT() << endl;
    }
    else if (upgradedClass == "JumpBot")
    {
        *botIter = new JumpBot(**botIter);
        *this << "> MovingRobot: " << (*botIter)->UPGRADED_MOVINGROBOT() << endl;
    }
    else if (upgradedClass == "DodgeBot")
    {
        *botIter = new DodgeBot(**botIter);
        *this << "> MovingRobot: " << (*botIter)->UPGRADED_MOVINGROBOT() << endl;
    }
    else if (upgradedClass == "LongShotBot")
    {
        *botIter = new LongShotBot(**botIter);
        *this << "> ShootingRobot: " << (*botIter)->UPGRADED_SHOOTINGROBOT() << endl;
    }
    else if (upgradedClass == "SemiAutoBot")
    {
        *botIter = new SemiAutoBot(**botIter);
        *this << "> ShootingRobot: " << (*botIter)->UPGRADED_SHOOTINGROBOT() << endl;
    }
    else if (upgradedClass == "ThirtyShotBot")
    {
        *botIter = new ThirtyShotBot(**botIter);
        *this << "> ShootingRobot: " << (*botIter)->UPGRADED_SHOOTINGROBOT() << endl;
    }
    else if (upgradedClass == "ShotgunBot")
    {
        *botIter = new ShotgunBot(**botIter);
        *this << "> ShootingRobot: " << (*botIter)->UPGRADED_SHOOTINGROBOT() << endl;
    }
    else if (upgradedClass == "LifeStealBot")
    {
        *botIter = new LifeStealBot(**botIter);
        *this << "> ShootingRobot: " << (*botIter)->UPGRADED_SHOOTINGROBOT() << endl;
    }
    else if (upgradedClass == "ScoutBot")
    {
        *botIter = new ScoutBot(**botIter);
        *this << "> SeeingRobot: " << (*botIter)->UPGRADED_SEEINGROBOT() << endl;
    }
    else if (upgradedClass == "TrackBot")
    {
        *botIter = new TrackBot(**botIter);
        *this << "> SeeingRobot: " << (*botIter)->UPGRADED_SEEINGROBOT() << endl;
    }

    delete temp; // delete old robot
    temp = nullptr;
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

        *this << "Respawning " << **rspBotIter << endl;
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
