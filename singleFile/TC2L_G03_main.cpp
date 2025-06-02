//*********************************************************
// Program: ASG_CCP6124_2510_TC2L_G03_AbdullahH_BongWeiQiangL_Prabu_Yoshenan.cpp
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

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <queue>
#include <regex>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                     //
//                                            START OF HEADERS                                                         //
//                                                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// class prototypes/forward declarations
class Battlefield;
class GenericRobot;

class Robot
{
public:
    // PC + DC
    Robot(string id = "", string name = "", int x = -1, int y = -1) : id_(id), robotName_(name), robotPositionX(x), robotPositionY(y) {}
    virtual ~Robot();
    Robot(const Robot &other);
    Robot &operator=(const Robot &other);

    // Getter and Setter functions
    int x() const
    {
        return robotPositionX;
    }
    void setX(int x)
    {
        robotPositionX = x;
    }
    int y() const
    {
        return robotPositionY;
    }
    void setY(int y)
    {
        robotPositionY = y;
    }
    virtual string id() const
    {
        return id_;
    }
    virtual string ApparentId() const
    {
        return id_;
    }
    void setId(string id)
    {
        id_ = id;
    }
    string robotType() const
    {
        return robotType_;
    }
    void setRobotType(string robotType)
    {
        robotType_ = robotType;
    }
    string robotName() const
    {
        return robotName_;
    }
    void setRobotName(string robotName)
    {
        robotName_ = robotName;
    }
    int numOfLives() const
    {
        return numOfLives_;
    }
    void setNumOfLives(int numOfLives)
    {
        numOfLives_ = numOfLives;
    }
    int numOfKills() const
    {
        return numOfKills_;
    }
    void setNumOfKills(int numOfKills)
    {
        numOfKills_ = numOfKills;
    }
    void reduceLife()
    {
        if (numOfLives_ > 0)
            numOfLives_--;
    }
    void incrementKills()
    {
        numOfKills_++;
    }
    bool isAlive() const
    {
        return numOfLives_ > 0;
    }

    // Overloading the << operator for Robot class
    friend ostream &operator<<(ostream &out, const Robot &r)
    {
        out << r.robotType_ << " " << r.id_ << " at (" << r.robotPositionX << ", " << r.robotPositionY << ")";
        return out;
    }

    // Pure virtual functions
    virtual void setLocation(int x, int y) = 0;
    virtual void actions(Battlefield *battlefield) = 0;

    string UPGRADED_MOVINGROBOT() const
    {
        return UPGRADED_MOVINGROBOT_;
    }
    string UPGRADED_SHOOTINGROBOT() const
    {
        return UPGRADED_SHOOTINGROBOT_;
    }
    string UPGRADED_SEEINGROBOT() const
    {
        return UPGRADED_SEEINGROBOT_;
    }

    bool PREV_KILL() const
    {
        return PREV_KILL_;
    }
    void setPREV_KILL(bool a)
    {
        PREV_KILL_ = a;
    }

    bool IS_WAITING() const
    {
        return IS_WAITING_;
    }
    void setIS_WAITING(bool val)
    {
        IS_WAITING_ = val;
    }

    int SHELL_COUNT()
    {
        return SHELL_COUNT_;
    }

protected:
    int robotPositionX = -1;
    int robotPositionY = -1;
    string id_ = ""; // eg GRO1, to display robot id on the Battlefield
    string robotType_ = "";
    string robotName_ = ""; // Robot id underscore robot name, eg GROS5_Star
    int numOfLives_ = 3;
    int numOfKills_ = 0;
    bool PREV_KILL_ = false;
    bool IS_WAITING_ = false;
    string UPGRADED_MOVINGROBOT_ = "";
    string UPGRADED_SHOOTINGROBOT_ = "";
    string UPGRADED_SEEINGROBOT_ = "";
    int SHELL_COUNT_;

    class location
    {
    public:
        location(int x, int y, string val = "");
        int locX;
        int locY;
        string value;
    };

    // Chebyshev relative distance between target and object, object defaults to robot's position if unspecified
    int locationRelativeDistanceChebyshev(location *locTarget, location *locObject = nullptr) const;
    // Taxicab relative distance between target and object, object defaults to robot's position if unspecified
    int locationRelativeDistanceTaxicab(location *locTarget, location *locObject = nullptr) const;
    // sorts location vector by ascending distance from target, target defaults to robot's position if unspecified.
    void locationSortVector(vector<location *> &locvec, location *locTarget = nullptr);

private:
};

class MovingRobot : virtual public Robot
{
public:
    MovingRobot();
    virtual ~MovingRobot();
    MovingRobot(const Robot &other);
    MovingRobot &operator=(const Robot &other);

    virtual void actionMove(Battlefield *battlefield) = 0; // Pure virtual function for moving

protected:
    virtual int moveStartCols() = 0;
    virtual int moveStartRows() = 0;

    vector<location *> move_;

private:
};

class SeeingRobot : virtual public Robot
{
public:
    SeeingRobot();
    virtual ~SeeingRobot();
    SeeingRobot(const Robot &other);
    SeeingRobot &operator=(const Robot &other);

    virtual void actionLook(Battlefield *battlefield) = 0; // Pure virtual function for looking

protected:
    virtual int viewStartCols() = 0;
    virtual int viewStartRows() = 0;

    vector<location *> view_;

private:
};

class ShootingRobot : virtual public Robot
{
public:
    ShootingRobot();
    virtual ~ShootingRobot();
    ShootingRobot(const Robot &other);
    ShootingRobot &operator=(const Robot &other);
    virtual void actionFire(Battlefield *battlefield) = 0; // Pure virtual function for firing

protected:
    virtual int shootStartCols() = 0;
    virtual int shootStartRows() = 0;

    int SHOOT_SUCCESS_PERCENTAGE;
    vector<location *> shoot_;

private:
};

class ThinkingRobot : virtual public Robot
{
public:
    ThinkingRobot();
    virtual ~ThinkingRobot();
    ThinkingRobot(const Robot &other);
    ThinkingRobot &operator=(const Robot &other);

    virtual void actionThink(Battlefield *battlefield) = 0; // Pure virtual function for stepping

protected:
private:
};

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

class HideBot : virtual public GenericRobot
{
public:
    HideBot(string id = "", string name = "", int x = -1, int y = -1);
    virtual ~HideBot();
    HideBot(const Robot &other);
    HideBot &operator=(const Robot &other);
    virtual void actionMove(Battlefield *battlefield) final;
    virtual string ApparentId() const
    {
        if (isHidden_)
        {
            return "#";
        }
        else
        {
            return id_;
        }
    }

protected:
    bool isHidden_ = false;
    int HIDE_COUNT = 3;

private:
};

class JumpBot : virtual public GenericRobot
{
public:
    JumpBot(string id = "", string name = "", int x = -1, int y = -1);
    virtual ~JumpBot();
    JumpBot(const Robot &other);
    JumpBot &operator=(const Robot &other);
    virtual void actionMove(Battlefield *battlefield) final;

protected:
    int SUPERJUMP_COUNT = 3;
    virtual int moveStartCols() final { return 0; }
    virtual int moveStartRows() final { return 0; }

private:
};

class LifeStealBot : virtual public GenericRobot
{
public:
    LifeStealBot(string id = "", string name = "", int x = -1, int y = -1);
    virtual ~LifeStealBot();
    LifeStealBot(const Robot &other);
    LifeStealBot &operator=(const Robot &other);

    virtual void actionFire(Battlefield *battlefield) override;

protected:
    bool hasStolen_ = false;

private:
};

class LongShotBot : virtual public GenericRobot
{
public:
    LongShotBot(string id = "", string name = "", int x = -1, int y = -1);
    virtual ~LongShotBot();
    LongShotBot(const Robot &other);
    LongShotBot &operator=(const Robot &other);

    virtual void actionFire(Battlefield *battlefield) final;

protected:
    virtual int shootStartCols() override { return robotPositionX - 3; }
    virtual int shootStartRows() override { return robotPositionY - 3; }

private:
};

class ScoutBot : virtual public GenericRobot
{
public:
    ScoutBot(string id = "", string name = "", int x = -1, int y = -1);
    virtual ~ScoutBot();
    ScoutBot(const Robot &other);
    ScoutBot &operator=(const Robot &other);
    virtual void actionLook(Battlefield *battlefield) final;

protected:
    virtual int viewStartCols() { return 0; };
    virtual int viewStartRows() { return 0; };

private:
};

class SemiAutoBot : virtual public GenericRobot
{
public:
    SemiAutoBot(string id = "", string name = "", int x = -1, int y = -1);
    virtual ~SemiAutoBot();
    SemiAutoBot(const Robot &other);
    SemiAutoBot &operator=(const Robot &other);

    virtual void actionFire(Battlefield *battlefield) final;

protected:
private:
};

class ShotgunBot : virtual public GenericRobot
{
public:
    ShotgunBot(string id = "", string name = "", int x = -1, int y = -1);
    virtual ~ShotgunBot();
    ShotgunBot(const Robot &other);
    ShotgunBot &operator=(const Robot &other);

    virtual void actionFire(Battlefield *battlefield) final;

protected:
    int SPREAD_SHOOT_SUCCESS_PERCENTAGE;
    void setShotgunSpread(location *shootLoc);
    vector<location *> shotgun_spread;

private:
};

class ThirtyShotBot : virtual public GenericRobot
{
public:
    ThirtyShotBot(string id = "", string name = "", int x = -1, int y = -1);
    virtual ~ThirtyShotBot();
    ThirtyShotBot(const Robot &other);
    ThirtyShotBot &operator=(const Robot &other);

    virtual void actionFire(Battlefield *battlefield) final;

protected:
private:
};

class TrackBot : virtual public GenericRobot
{
public:
    TrackBot(string id = "", string name = "", int x = -1, int y = -1);
    virtual ~TrackBot();
    TrackBot(const Robot &other);
    TrackBot &operator=(const Robot &other);
    virtual void actionLook(Battlefield *battlefield) final;

protected:
    vector<string> trackedBotsIds_;

private:
};

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

    // overloaded operator so that we can << numbers or string into the battlefield object, and it will automatically save to outputfile and cout
    template <typename T>
    Battlefield &operator<<(const T &t)
    {
        outputFile << t;
        cout << t;
        return *this;
    }

    // for the cout manipulators
    Battlefield &operator<<(ostream &(*manip)(ostream &))
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                     //
//                                            END OF HEADERS                                                           //
//                                                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                     //
//                                            START OF DEFINITIONS                                                     //
//                                                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Battlefield::Battlefield()
{
    // ctor
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

    // flushing cus old newline was automatically triggering start
    while ((c = getchar()) != '\n' && c != EOF)
    {
        continue;
    }

    c = getchar();

    vector<Robot *>::iterator robots_Iter = robots_.begin();

    while (c != 'q' && static_cast<int>(destroyedRobots_.size()) < static_cast<int>(robots_.size()) - 1 && turn < turns_)
    {
        // increment turn
        turn++;

        // if at the end, or if bot is waiting, go back to start or skip
        justifyIter(robots_Iter);

        placeRobots();

        *this << endl
              << endl;

        // respawn any waiting bot in waiting
        respawnWaiting();

        placeRobots();

        displayBattlefield();

        *this << "Turn " << turn << ":" << endl;

        *this << *(*robots_Iter) << endl;
        *this << "Lives left: " << (*robots_Iter)->numOfLives() << endl;
        *this << "Shells left: " << (*robots_Iter)->SHELL_COUNT() << endl;
        *this << "Kills: " << (*robots_Iter)->numOfKills() << endl;

        *this << "-------------------------" << endl;
        (*robots_Iter)->actions(this);

        if ((*robots_Iter)->PREV_KILL())
        {
            (*robots_Iter)->setPREV_KILL(false);
            upgrade(robots_Iter);
        }

        if ((*robots_Iter)->SHELL_COUNT() <= 0)
        {
            selfDestruct(robots_Iter);
        }

        // next robot
        robots_Iter++;

        // ask for next step
        *this << endl;
        *this << "Press [Enter] key or enter any key to continue." << endl;
        *this << "Enter [q] to terminate." << endl;
        c = getchar();
    }
    *this << "-------------------------" << endl;
    *this << "Program terminated." << endl;
    *this << "-------------------------" << endl
          << endl;

    *this << "Turns: " << endl;
    *this << turn << "/" << turns_ << endl
          << endl;

    *this << "Final results:" << endl;
    for (Robot *i : robots_)
    {
        *this << i->robotType() << " " << i->id() << endl;
        *this << "> Lives left: " << i->numOfLives() << endl;
        *this << "> Shells left: " << i->SHELL_COUNT() << endl;
        *this << "> Kills: " << i->numOfKills() << endl;
        *this << "> MovingRobot: " << i->UPGRADED_MOVINGROBOT() << endl;
        *this << "> ShootingRobot: " << i->UPGRADED_SHOOTINGROBOT() << endl;
        *this << "> SeeingRobot: " << i->UPGRADED_SEEINGROBOT() << endl;
    }
    *this << endl;

    *this << "Winner: " << endl;
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
        *this << "None" << endl;
        ;
    }
    *this << endl;

    *this << "Final state of battlefield:" << endl;
    placeRobots();
    displayBattlefield();

    cout << endl
         << endl;

    cout << "Enter [q] to end program." << endl;

    while ((c = getchar()) != 'q')
    {
        cout << "Enter [q] to end program.";
        continue;
    }
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

    try
    {
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
            string roboType = typeMatch[2]; // Robot Type capture group
            string roboName = typeMatch[3]; // Robot Name capture group
            string roboId = typeMatch[4];   // Robot Id capture group

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
                Robot *newBot = new GenericRobot(roboId, roboName, roboX, roboY);
                robots_.push_back(newBot);
            }
            else if (roboType == "HideBot")
            {
                Robot *newBot = new HideBot(roboId, roboName, roboX, roboY);
                robots_.push_back(newBot);
            }
            else if (roboType == "JumpBot")
            {
                Robot *newBot = new JumpBot(roboId, roboName, roboX, roboY);
                robots_.push_back(newBot);
            }
            else if (roboType == "DodgeBot")
            {
                Robot *newBot = new DodgeBot(roboId, roboName, roboX, roboY);
                robots_.push_back(newBot);
            }
            else if (roboType == "LongShotBot")
            {
                Robot *newBot = new LongShotBot(roboId, roboName, roboX, roboY);
                robots_.push_back(newBot);
            }
            else if (roboType == "SemiAutoBot")
            {
                Robot *newBot = new SemiAutoBot(roboId, roboName, roboX, roboY);
                robots_.push_back(newBot);
            }
            else if (roboType == "ThirtyShotBot")
            {
                Robot *newBot = new ThirtyShotBot(roboId, roboName, roboX, roboY);
                robots_.push_back(newBot);
            }
            else if (roboType == "ShotgunBot")
            {
                Robot *newBot = new ShotgunBot(roboId, roboName, roboX, roboY);
                robots_.push_back(newBot);
            }
            else if (roboType == "LifeStealBot")
            {
                Robot *newBot = new LifeStealBot(roboId, roboName, roboX, roboY);
                robots_.push_back(newBot);
            }
            else if (roboType == "ScoutBot")
            {
                Robot *newBot = new ScoutBot(roboId, roboName, roboX, roboY);
                robots_.push_back(newBot);
            }
            else if (roboType == "TrackBot")
            {
                Robot *newBot = new TrackBot(roboId, roboName, roboX, roboY);
                robots_.push_back(newBot);
            }
        }
        cout << "Field size: " << fieldM << ", " << fieldN << endl; // To display at beginning of program
        cout << "Number of robots: " << numRobots << endl;
        outputFile.open(filename + "_OUTPUT.txt");
    }
    catch (...)
    {
        cout << "Error reading file contents. Ensure file name is correct and file contents formatted properly." << endl;
        exit(1);
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
                robots_[i]->ApparentId();
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

bool Battlefield::isValidFireLocation(int x, int y) const
{
    const string val = peek(x, y);

    if (val != "")
    {
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

void Battlefield::selfDestruct(vector<Robot *>::iterator botIter)
{

    *this << **botIter << " has run out of shells and self-destructed." << endl;
    (*botIter)->reduceLife();

    if ((*botIter)->isAlive())
    {
        (*botIter)->setIS_WAITING(true);
        waitingRobots_.push((*botIter));
    }
    else
    { // else destroyed
        *this << *(*botIter) << " has been destroyed." << endl;
        destroyedRobots_.push((*botIter));
    }
}

void Battlefield::upgrade(vector<Robot *>::iterator botIter)
{
    *this << endl;
    *this << (*botIter)->id() << " has already been upgraded to:" << endl;
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
    if ((*botIter)->UPGRADED_MOVINGROBOT() == "" && (*botIter)->UPGRADED_SHOOTINGROBOT() == "" && (*botIter)->UPGRADED_SEEINGROBOT() == "")
    {
        *this << "None" << endl;
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

Robot::~Robot()
{
    // dtor
}

Robot::Robot(const Robot &other)
{
    // copy ctor
}

Robot &Robot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

Robot::location::location(int x, int y, string val)
{
    locX = x;
    locY = y;
    value = val;
}

int Robot::locationRelativeDistanceChebyshev(location *locTarget, location *locObject) const
{
    int relx, rely;
    if (locObject)
    {
        relx = locTarget->locX - locObject->locX;
        rely = locTarget->locY - locObject->locY;
    }
    else
    {
        relx = locTarget->locX - robotPositionX;
        rely = locTarget->locY - robotPositionY;
    }
    if (relx < 0)
    {
        relx = -relx;
    }
    if (rely < 0)
    {
        rely = -rely;
    }
    if (relx > rely)
    {
        return relx;
    }
    else
    {
        return rely;
    }
}

int Robot::locationRelativeDistanceTaxicab(location *locTarget, location *locObject) const
{
    int relx, rely;
    if (locObject)
    {
        relx = locTarget->locX - locObject->locX;
        rely = locTarget->locY - locObject->locY;
    }
    else
    {
        relx = locTarget->locX - robotPositionX;
        rely = locTarget->locY - robotPositionY;
    }
    if (relx < 0)
    {
        relx = -relx;
    }
    if (rely < 0)
    {
        rely = -rely;
    }
    return relx + rely;
}

void Robot::locationSortVector(vector<location *> &locvec, location *locTarget)
{
    const int MAX_MOVE = locvec.size();
    int minIndex, minValue;
    location *temp;
    for (int start = 0; start < (MAX_MOVE - 1); start++)
    {
        minIndex = start;
        minValue = locationRelativeDistanceChebyshev(locvec.at(start), locTarget);
        for (int index = start + 1; index < MAX_MOVE; index++)
        {
            if (locationRelativeDistanceChebyshev(locvec.at(index), locTarget) < minValue)
            {
                minValue = locationRelativeDistanceChebyshev(locvec.at(index), locTarget);
                minIndex = index;
            }
        }
        temp = locvec.at(start);
        locvec.at(start) = locvec.at(minIndex);
        locvec.at(minIndex) = temp;
        temp = nullptr;
    }
}

MovingRobot::MovingRobot()
{
    // ctor
}

MovingRobot::~MovingRobot()
{
    // dtor
    for (int i = 0; i < move_.size(); i++)
    {
        if (move_[i])
        {
            delete move_[i];
        }
        move_[i] = nullptr;
    }
}

MovingRobot::MovingRobot(const Robot &other)
{
    // copy ctor
}

MovingRobot &MovingRobot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

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

ShootingRobot::ShootingRobot()
{
    // ctor
}

ShootingRobot::~ShootingRobot()
{
    // dtor
    for (int i = 0; i < shoot_.size(); i++)
    {
        if (shoot_[i])
        {
            delete shoot_[i];
        }
        shoot_[i] = nullptr;
    }
}

ShootingRobot::ShootingRobot(const Robot &other)
{
    // copy ctor
}

ShootingRobot &ShootingRobot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

ThinkingRobot::ThinkingRobot()
{
    // ctor
}

ThinkingRobot::~ThinkingRobot()
{
    // dtor
}

ThinkingRobot::ThinkingRobot(const Robot &other)
{
    // copy ctor
}

ThinkingRobot &ThinkingRobot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

GenericRobot::GenericRobot(string id, string name, int x, int y)
{
    id_ = id;
    robotName_ = name;
    robotPositionX = x;
    robotPositionY = y;
    robotAutoIncrementInt_++;
    robotType_ = "GenericRobot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
}

GenericRobot::~GenericRobot()
{
    // dtor
}

GenericRobot::GenericRobot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotName_ = other.robotName();
    numOfKills_ = other.numOfKills();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "GenericRobot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    PREV_KILL_ = other.PREV_KILL();
    IS_WAITING_ = other.IS_WAITING();

    UPGRADED_MOVINGROBOT_ = other.UPGRADED_MOVINGROBOT();
    UPGRADED_SHOOTINGROBOT_ = other.UPGRADED_SHOOTINGROBOT();
    UPGRADED_SEEINGROBOT_ = other.UPGRADED_SEEINGROBOT();
    numOfLives_ = other.numOfLives();
}

GenericRobot &GenericRobot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void GenericRobot::setLocation(int x, int y)
{
    robotPositionX = x;
    robotPositionY = y;
}

void GenericRobot::actions(Battlefield *battlefield)
{
    // getting a random number from 0 to 5
    int randomActionThink = rand();

    // executing actions based on random number genned. (Robot always has to think and look first)
    if (randomActionThink % 2 == 0)
    {
        actionThink(battlefield);
        actionLook(battlefield);
        actionFire(battlefield);
        battlefield->placeRobots();
        actionMove(battlefield);
        battlefield->placeRobots();
    }
    else if (randomActionThink % 2 == 1)
    {
        actionThink(battlefield);
        actionLook(battlefield);
        actionMove(battlefield);
        battlefield->placeRobots();
        actionFire(battlefield);
        battlefield->placeRobots();
    }
}

int GenericRobot::robotAutoIncrementInt() { return robotAutoIncrementInt_; }

void GenericRobot::actionThink(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionThink" << endl;
    *battlefield << "> Robot " << id_ << " is thinking..." << endl;
}

void GenericRobot::actionLook(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionLook" << endl;

    const int startCol = viewStartCols();
    const int startRow = viewStartRows();
    const int viewColsWidth = 3;
    const int viewRowsWidth = 3;

    for (size_t i = 0; i < view_.size(); i++)
    {
        if (view_[i])
        {
            delete view_[i];
        }
        view_[i] = nullptr;
    }
    view_.clear();

    string val;
    location *newLoc;

    for (int j = 0; j < viewRowsWidth; j++)
    {
        *battlefield << ">";
        for (int i = 0; i < viewColsWidth; i++)
        {
            const int x = startCol + i;
            const int y = startRow + j;
            val = battlefield->peek(x, y);

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                *battlefield << " " << left << setfill(' ') << setw(4) << id_;
                continue;
            }

            if (val != "") // remove out of bound areas
            {
                newLoc = new location(x, y, val);
                view_.push_back(newLoc);
                *battlefield << " " << left << setfill(' ') << setw(4) << val;
            }
        }

        *battlefield << " " << endl;
    }
}

void GenericRobot::actionMove(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionMove" << endl;

    const int startCols = moveStartCols();
    const int startRows = moveStartRows();
    const int moveColsWidth = 3;
    const int moveRowsWidth = 3;

    // clear previous round valid move locations
    for (size_t i = 0; i < move_.size(); i++)
    {
        if (move_[i])
        {
            delete move_[i];
        }
        move_[i] = nullptr;
    }
    move_.clear();

    // find valid move locations
    location *newLoc;
    for (int j = 0; j < moveRowsWidth; j++)
    {
        for (int i = 0; i < moveColsWidth; i++)
        {
            const int x = startCols + i;
            const int y = startRows + j;

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                continue;
            }

            if (battlefield->isValidMoveLocation(x, y)) // remove out of bound areas and other robots
            {
                newLoc = new location(x, y);
                move_.push_back(newLoc);
            }
        }
    }

    // terminate if no valid move locations
    if (move_.size() == 0)
    {
        *battlefield << "No valid move locations." << endl;
        return;
    }

    // find closest enemy from view
    location *foundEnemy = nullptr;
    locationSortVector(view_);
    for (size_t i = 0; i < view_.size() && !foundEnemy; i++)
    {
        if (view_[i]->value != "*" && view_[i]->value != "#")
        {
            foundEnemy = view_[i];
        }
    }

    // perform move based on if foundenemy or not
    if (foundEnemy)
    {
        locationSortVector(move_, foundEnemy);
        if (locationRelativeDistanceChebyshev(foundEnemy) > 1)
        {
            setLocation(move_[0]->locX, move_[0]->locY); // move to location that's towards enemy
            *battlefield << "> " << id_ << " moves to position (" << move_[0]->locX << "," << move_[0]->locY << ")" << endl;
        }
    }
    else
    {
        const int randIndex = rand() % (move_.size());
        setLocation(move_[randIndex]->locX, move_[randIndex]->locY); // random move
        *battlefield << "> " << id_ << " moves to position (" << move_[randIndex]->locX << "," << move_[randIndex]->locY << ")" << endl;
    }
}

int GenericRobot::robotAutoIncrementInt_ = 0;

void GenericRobot::actionFire(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionFire" << endl;

    if (SHELL_COUNT_ <= 0) // skip if no more shells
    {
        return;
    }

    const int startCols = shootStartCols();
    const int startRows = shootStartRows();
    const int shootColsWidth = 3;
    const int shootRowsWidth = 3;
    bool temp = false;
    setPREV_KILL(false);

    // clear previous round valid move locations
    for (size_t i = 0; i < shoot_.size(); i++)
    {
        if (shoot_[i])
        {
            delete shoot_[i];
        }
        shoot_[i] = nullptr;
    }
    shoot_.clear();

    // find valid move locations
    location *newLoc;
    for (int j = 0; j < shootRowsWidth; j++)
    {
        for (int i = 0; i < shootColsWidth; i++)
        {
            const int x = startCols + i;
            const int y = startRows + j;

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                continue;
            }

            if (battlefield->isValidFireLocation(x, y)) // remove out of bound areas and other robots
            {
                newLoc = new location(x, y);
                shoot_.push_back(newLoc);
            }
        }
    }

    // find closest enemy from view
    location *foundEnemy = nullptr;
    locationSortVector(view_);
    for (size_t i = 0; i < view_.size() && !foundEnemy; i++)
    {
        if (view_[i]->value != "*" && view_[i]->value != "#")
        {
            foundEnemy = view_[i];
        }
    }

    // perform shoot based on if foundenemy or not
    if (foundEnemy)
    {
        locationSortVector(shoot_, foundEnemy);
        if (locationRelativeDistanceChebyshev(foundEnemy, shoot_[0]) == 0)
        {
            if (SHELL_COUNT_ > 0)
            {
                temp = battlefield->strike(shoot_[0]->locX, shoot_[0]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
                SHELL_COUNT_--;
                if (temp)
                {
                    setPREV_KILL(true);
                    incrementKills();
                }
            }
        }
        else // random shoot bc enemy is too far away
        {
            if (SHELL_COUNT_ > 0)
            {
                const int randIndex = rand() % (shoot_.size());
                temp = battlefield->strike(shoot_[randIndex]->locX, shoot_[randIndex]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
                SHELL_COUNT_--;
                if (temp)
                {
                    setPREV_KILL(true);
                    incrementKills();
                }
            }
        }
    }
    else
    {
        if (SHELL_COUNT_ > 0)
        {
            const int randIndex = rand() % (shoot_.size());
            temp = battlefield->strike(shoot_[randIndex]->locX, shoot_[randIndex]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
            SHELL_COUNT_--;
            if (temp)
            {
                setPREV_KILL(true);
                incrementKills();
            }
        }
    }
}

DodgeBot::DodgeBot(string id, string name, int x, int y)
{
    // ctor
    id_ = id;
    robotName_ = name;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "DodgeBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    UPGRADED_MOVINGROBOT_ = robotType_;

    DODGE_COUNT = 3;
}

DodgeBot::~DodgeBot()
{
    // dtor
}

DodgeBot::DodgeBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotName_ = other.robotName();
    numOfKills_ = other.numOfKills();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "DodgeBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    PREV_KILL_ = other.PREV_KILL();
    IS_WAITING_ = other.IS_WAITING();
    UPGRADED_MOVINGROBOT_ = robotType_;

    DODGE_COUNT = 3;

    UPGRADED_SHOOTINGROBOT_ = other.UPGRADED_SHOOTINGROBOT();
    UPGRADED_SEEINGROBOT_ = other.UPGRADED_SEEINGROBOT();
    numOfLives_ = other.numOfLives();
}

DodgeBot &DodgeBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void DodgeBot::actionMove(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionMove" << endl;
    const int startCols = moveStartCols();
    const int startRows = moveStartRows();
    const int moveColsWidth = 3;
    const int moveRowsWidth = 3;

    // clear previous round valid move locations
    for (size_t i = 0; i < move_.size(); i++)
    {
        if (move_[i])
        {
            delete move_[i];
        }
        move_[i] = nullptr;
    }
    move_.clear();

    // find valid move locations
    location *newLoc;
    for (int j = 0; j < moveRowsWidth; j++)
    {
        for (int i = 0; i < moveColsWidth; i++)
        {
            const int x = startCols + i;
            const int y = startRows + j;

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                continue;
            }

            if (battlefield->isValidMoveLocation(x, y)) // remove out of bound areas and other robots
            {
                newLoc = new location(x, y);
                move_.push_back(newLoc);
            }
        }
    }

    // terminate if no valid move locations
    if (move_.size() == 0)
    {
        *battlefield << "No valid move locations." << endl;
        return;
    }

    // find closest enemy from view
    location *foundEnemy = nullptr;
    locationSortVector(view_);
    for (size_t i = 0; i < view_.size() && !foundEnemy; i++)
    {
        if (view_[i]->value != "*" && view_[i]->value != "#")
        {
            foundEnemy = view_[i];
        }
    }

    // perform move based on if foundenemy or not
    if (foundEnemy)
    {
        locationSortVector(move_, foundEnemy);

        if (DODGE_COUNT > 0) // if still has dodges left
        {
            setLocation(move_.back()->locX, move_.back()->locY); // move to location that's towards enemy
            DODGE_COUNT--;
        } // else do generic robot's actions
        else if (locationRelativeDistanceChebyshev(foundEnemy) > 1)
        {
            setLocation(move_[0]->locX, move_[0]->locY); // move to location that's towards enemy
            *battlefield << "> " << id_ << " moves to position (" << move_[0]->locX << "," << move_[0]->locY << ")" << endl;
        }
    }
    else
    {
        const int randIndex = rand() % (move_.size());
        setLocation(move_[randIndex]->locX, move_[randIndex]->locY); // random move
        *battlefield << "> " << id_ << " moves to position (" << move_[randIndex]->locX << "," << move_[randIndex]->locY << ")" << endl;
    }
}

HideBot::HideBot(string id, string name, int x, int y)
{
    // ctor
    id_ = id;
    robotName_ = name;
    robotName_ = name;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "HideBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    UPGRADED_MOVINGROBOT_ = robotType_;
}

HideBot::~HideBot()
{
    // dtor
}

HideBot::HideBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotName_ = other.robotName();
    numOfKills_ = other.numOfKills();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "HideBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    PREV_KILL_ = other.PREV_KILL();
    IS_WAITING_ = other.IS_WAITING();
    UPGRADED_MOVINGROBOT_ = robotType_;

    UPGRADED_SHOOTINGROBOT_ = other.UPGRADED_SHOOTINGROBOT();
    UPGRADED_SEEINGROBOT_ = other.UPGRADED_SEEINGROBOT();
    numOfLives_ = other.numOfLives();
}

HideBot &HideBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void HideBot::actionMove(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionMove" << endl;

    isHidden_ = false;
    const int startCols = moveStartCols();
    const int startRows = moveStartRows();
    const int moveColsWidth = 3;
    const int moveRowsWidth = 3;

    // clear previous round valid move locations
    for (size_t i = 0; i < move_.size(); i++)
    {
        if (move_[i])
        {
            delete move_[i];
        }
        move_[i] = nullptr;
    }
    move_.clear();

    // find valid move locations
    location *newLoc;
    for (int j = 0; j < moveRowsWidth; j++)
    {
        for (int i = 0; i < moveColsWidth; i++)
        {
            const int x = startCols + i;
            const int y = startRows + j;

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                continue;
            }

            if (battlefield->isValidMoveLocation(x, y)) // remove out of bound areas and other robots
            {
                newLoc = new location(x, y);
                move_.push_back(newLoc);
            }
        }
    }

    // terminate if no valid move locations
    if (move_.size() == 0)
    {
        *battlefield << "No valid move locations." << endl;
        return;
    }

    // find closest enemy from view
    location *foundEnemy = nullptr;
    locationSortVector(view_);
    for (size_t i = 0; i < view_.size() && !foundEnemy; i++)
    {
        if (view_[i]->value != "*" && view_[i]->value != "#")
        {
            foundEnemy = view_[i];
        }
    }

    // perform move based on if foundenemy or not
    if (foundEnemy)
    {
        locationSortVector(move_, foundEnemy);
        if (locationRelativeDistanceChebyshev(foundEnemy) == 1 && HIDE_COUNT > 0)
        {
            isHidden_ = true;
            HIDE_COUNT--;
            *battlefield << "> " << id_ << " hides" << endl;
        }
        else if (locationRelativeDistanceChebyshev(foundEnemy) > 1)
        {
            isHidden_ = false;
            setLocation(move_[0]->locX, move_[0]->locY); // move to location that's towards enemy
            *battlefield << "> " << id_ << " moves to position (" << move_[0]->locX << "," << move_[0]->locY << ")" << endl;
        }
    }
    else
    {
        isHidden_ = false;
        const int randIndex = rand() % (move_.size());
        setLocation(move_[randIndex]->locX, move_[randIndex]->locY); // random move
        *battlefield << "> " << id_ << " moves to position (" << move_[randIndex]->locX << "," << move_[randIndex]->locY << ")" << endl;
    }
};

JumpBot::JumpBot(string id, string name, int x, int y)
{
    // ctor
    id_ = id;
    robotName_ = name;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "JumpBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    UPGRADED_MOVINGROBOT_ = robotType_;
}

JumpBot::~JumpBot()
{
    // dtor
}

JumpBot::JumpBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotName_ = other.robotName();
    numOfKills_ = other.numOfKills();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "JumpBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    PREV_KILL_ = other.PREV_KILL();
    IS_WAITING_ = other.IS_WAITING();
    UPGRADED_MOVINGROBOT_ = robotType_;

    UPGRADED_SHOOTINGROBOT_ = other.UPGRADED_SHOOTINGROBOT();
    UPGRADED_SEEINGROBOT_ = other.UPGRADED_SEEINGROBOT();
    numOfLives_ = other.numOfLives();
}

JumpBot &JumpBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void JumpBot::actionMove(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionMove" << endl;

    int moveStartCols, moveStartRows, moveColsWidth, moveRowsWidth;
    if (SUPERJUMP_COUNT > 0)
    {
        moveStartCols = JumpBot::moveStartCols();
        moveStartRows = JumpBot::moveStartRows();
        moveColsWidth = battlefield->BATTLEFIELD_NUM_OF_COLS();
        moveRowsWidth = battlefield->BATTLEFIELD_NUM_OF_ROWS();
    }
    else
    {
        moveStartCols = GenericRobot::moveStartCols();
        moveStartRows = GenericRobot::moveStartRows();
        moveColsWidth = 3;
        moveRowsWidth = 3;
    }

    // clear previous round valid move locations
    for (size_t i = 0; i < move_.size(); i++)
    {
        if (move_[i])
        {
            delete move_[i];
        }
        move_[i] = nullptr;
    }
    move_.clear();

    // find valid move locations
    location *newLoc;
    for (int j = 0; j < moveRowsWidth; j++)
    {
        for (int i = 0; i < moveColsWidth; i++)
        {
            const int x = moveStartCols + i;
            const int y = moveStartRows + j;

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                continue;
            }

            if (battlefield->isValidMoveLocation(x, y)) // remove out of bound areas and other robots
            {
                newLoc = new location(x, y);
                move_.push_back(newLoc);
            }
        }
    }

    // terminate if no valid move locations
    if (move_.size() == 0)
    {
        *battlefield << "No valid move locations." << endl;
        return;
    }

    // find closest enemy from view
    location *foundEnemy = nullptr;
    locationSortVector(view_);
    for (size_t i = 0; i < view_.size() && !foundEnemy; i++)
    {
        if (view_[i]->value != "*" && view_[i]->value != "#")
        {
            foundEnemy = view_[i];
        }
    }

    // perform move based on if foundenemy or not
    if (foundEnemy)
    {
        locationSortVector(move_, foundEnemy);
        if (locationRelativeDistanceChebyshev(foundEnemy) > 1)
        {
            if (locationRelativeDistanceChebyshev(move_[0]) > 1)
            {
                SUPERJUMP_COUNT--;
            }
            setLocation(move_[0]->locX, move_[0]->locY); // move to location that's towards enemy
            *battlefield << "> " << id_ << " moves to position (" << move_[0]->locX << "," << move_[0]->locY << ")" << endl;
        }
    }
    else
    {
        location *randloc = move_[rand() % (move_.size())];
        if (locationRelativeDistanceChebyshev(randloc) > 1)
        {
            SUPERJUMP_COUNT--;
        }
        setLocation(randloc->locX, randloc->locY); // random move
        *battlefield << "> " << id_ << " moves to position (" << randloc->locX << "," << randloc->locY << ")" << endl;
    }
}

LifeStealBot::LifeStealBot(string id, string name, int x, int y)
{
    // ctor
    id_ = id;
    robotName_ = name;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "LifeStealBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    UPGRADED_SHOOTINGROBOT_ = robotType_;
}

LifeStealBot::~LifeStealBot()
{
    // dtor
}

LifeStealBot::LifeStealBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotName_ = other.robotName();
    numOfKills_ = other.numOfKills();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "LifeStealBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    PREV_KILL_ = other.PREV_KILL();
    IS_WAITING_ = other.IS_WAITING();
    UPGRADED_SHOOTINGROBOT_ = robotType_;

    UPGRADED_MOVINGROBOT_ = other.UPGRADED_MOVINGROBOT();
    UPGRADED_SEEINGROBOT_ = other.UPGRADED_SEEINGROBOT();
    numOfLives_ = other.numOfLives();
}

LifeStealBot &LifeStealBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void LifeStealBot::actionFire(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionFire" << endl;

    if (SHELL_COUNT_ <= 0) // skip if no more shells
    {
        return;
    }

    const int startCols = shootStartCols();
    const int startRows = shootStartRows();
    const int shootColsWidth = 3;
    const int shootRowsWidth = 3;
    setPREV_KILL(false);
    bool temp = false;

    // clear previous round valid move locations
    for (size_t i = 0; i < shoot_.size(); i++)
    {
        if (shoot_[i])
        {
            delete shoot_[i];
        }
        shoot_[i] = nullptr;
    }
    shoot_.clear();

    // find valid move locations
    location *newLoc;
    for (int j = 0; j < shootRowsWidth; j++)
    {
        for (int i = 0; i < shootColsWidth; i++)
        {
            const int x = startCols + i;
            const int y = startRows + j;

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                continue;
            }

            if (battlefield->isValidFireLocation(x, y)) // remove out of bound areas and other robots
            {
                newLoc = new location(x, y);
                shoot_.push_back(newLoc);
            }
        }
    }

    // find closest enemy from view
    location *foundEnemy = nullptr;
    locationSortVector(view_);
    for (size_t i = 0; i < view_.size() && !foundEnemy; i++)
    {
        if (view_[i]->value != "*" && view_[i]->value != "#")
        {
            foundEnemy = view_[i];
        }
    }

    // perform shoot based on if foundenemy or not
    if (foundEnemy)
    {
        locationSortVector(shoot_, foundEnemy);
        if (locationRelativeDistanceChebyshev(foundEnemy, shoot_[0]) == 0)
        {
            if (SHELL_COUNT_ > 0)
            {
                temp = battlefield->strike(shoot_[0]->locX, shoot_[0]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
                SHELL_COUNT_--;
                if (temp)
                {
                    if (!hasStolen_)
                    {
                        numOfLives_++;
                        hasStolen_ = true;
                    }

                    setPREV_KILL(true);
                    incrementKills();
                }
            }
        }
    }
    else
    {
        if (SHELL_COUNT_ > 0)
        {
            const int randIndex = rand() % (shoot_.size());
            temp = battlefield->strike(shoot_[randIndex]->locX, shoot_[randIndex]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
            SHELL_COUNT_--;
            if (temp)
            {
                if (!hasStolen_)
                {
                    numOfLives_++;
                    hasStolen_ = true;
                }

                setPREV_KILL(true);
                incrementKills();
            }
        }
    }
}

LongShotBot::LongShotBot(string id, string name, int x, int y)
{
    // ctor
    id_ = id;
    robotName_ = name;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "LongShotBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    UPGRADED_SHOOTINGROBOT_ = robotType_;
}

LongShotBot::~LongShotBot()
{
    // dtor
}

LongShotBot::LongShotBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotName_ = other.robotName();
    numOfKills_ = other.numOfKills();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "LongShotBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    PREV_KILL_ = other.PREV_KILL();
    IS_WAITING_ = other.IS_WAITING();
    UPGRADED_SHOOTINGROBOT_ = robotType_;

    UPGRADED_MOVINGROBOT_ = other.UPGRADED_MOVINGROBOT();
    UPGRADED_SEEINGROBOT_ = other.UPGRADED_SEEINGROBOT();
    numOfLives_ = other.numOfLives();
}

LongShotBot &LongShotBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void LongShotBot::actionFire(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionFire" << endl;

    if (SHELL_COUNT_ <= 0) // skip if no more shells
    {
        return;
    }

    const int startCols = shootStartCols();
    const int startRows = shootStartRows();
    const int shootColsWidth = 7;
    const int shootRowsWidth = 7;
    setPREV_KILL(false);
    bool temp = false;

    // clear previous round valid move locations
    for (size_t i = 0; i < shoot_.size(); i++)
    {
        if (shoot_[i])
        {
            delete shoot_[i];
        }
        shoot_[i] = nullptr;
    }
    shoot_.clear();

    // find valid move locations
    location *newLoc;
    for (int j = 0; j < shootRowsWidth; j++)
    {
        for (int i = 0; i < shootColsWidth; i++)
        {
            const int x = startCols + i;
            const int y = startRows + j;

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                continue;
            }
            newLoc = new location(x, y);
            if (battlefield->isValidFireLocation(x, y) && locationRelativeDistanceTaxicab(newLoc) <= 3) // remove out of bound areas and other robots
            {
                shoot_.push_back(newLoc);
            }
            else
            {
                delete newLoc;
                newLoc = nullptr;
            }
        }
    }

    // find closest enemy from view
    location *foundEnemy = nullptr;
    locationSortVector(view_);
    for (size_t i = 0; i < view_.size() && !foundEnemy; i++)
    {
        if (view_[i]->value != "*" && view_[i]->value != "#")
        {
            foundEnemy = view_[i];
        }
    }

    // perform shoot based on if foundenemy or not
    if (foundEnemy)
    {
        locationSortVector(shoot_, foundEnemy);
        if (locationRelativeDistanceChebyshev(foundEnemy, shoot_[0]) == 0)
        {
            if (SHELL_COUNT_ > 0)
            {
                temp = battlefield->strike(shoot_[0]->locX, shoot_[0]->locY, SHOOT_SUCCESS_PERCENTAGE, this); // target enemy
                SHELL_COUNT_--;
                if (temp)
                {
                    setPREV_KILL(true);
                    incrementKills();
                }
            }
        }
    }
    else
    {
        if (SHELL_COUNT_ > 0)
        {
            const int randIndex = rand() % (shoot_.size());
            temp = battlefield->strike(shoot_[randIndex]->locX, shoot_[randIndex]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
            SHELL_COUNT_--;
            if (temp)
            {
                setPREV_KILL(true);
                incrementKills();
            }
        }
    }
}

ScoutBot::ScoutBot(string id, string name, int x, int y)
{
    // ctor
    id_ = id;
    robotName_ = name;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "ScoutBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    UPGRADED_SEEINGROBOT_ = robotType_;
}

ScoutBot::~ScoutBot()
{
    // dtor
}

ScoutBot::ScoutBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotName_ = other.robotName();
    numOfKills_ = other.numOfKills();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "ScoutBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    PREV_KILL_ = other.PREV_KILL();
    IS_WAITING_ = other.IS_WAITING();
    UPGRADED_SEEINGROBOT_ = robotType_;

    UPGRADED_MOVINGROBOT_ = other.UPGRADED_MOVINGROBOT();
    UPGRADED_SHOOTINGROBOT_ = other.UPGRADED_SHOOTINGROBOT();
    numOfLives_ = other.numOfLives();
}

ScoutBot &ScoutBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void ScoutBot::actionLook(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionLook" << endl;

    const int startCol = viewStartCols();
    const int startRow = viewStartRows();
    const int viewColsWidth = battlefield->BATTLEFIELD_NUM_OF_COLS();
    const int viewRowsWidth = battlefield->BATTLEFIELD_NUM_OF_ROWS();

    for (size_t i = 0; i < view_.size(); i++)
    {
        if (view_[i])
        {
            delete view_[i];
        }
        view_[i] = nullptr;
    }
    view_.clear();

    string val;
    location *newLoc;

    for (int j = 0; j < viewRowsWidth; j++)
    {
        *battlefield << ">";
        for (int i = 0; i < viewColsWidth; i++)
        {
            const int x = startCol + i;
            const int y = startRow + j;
            val = battlefield->peek(x, y);

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                *battlefield << " " << left << setfill(' ') << setw(4) << id_;
                continue;
            }

            if (val != "") // remove out of bound areas
            {
                newLoc = new location(x, y, val);
                view_.push_back(newLoc);
                *battlefield << " " << left << setfill(' ') << setw(4) << val;
            }
        }

        *battlefield << " " << endl;
    }
}

SemiAutoBot::SemiAutoBot(string id, string name, int x, int y)
{
    // ctor
    id_ = id;
    robotName_ = name;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "SemiAutoBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    UPGRADED_SHOOTINGROBOT_ = robotType_;
}

SemiAutoBot::~SemiAutoBot()
{
    // dtor
}

SemiAutoBot::SemiAutoBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotName_ = other.robotName();
    numOfKills_ = other.numOfKills();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "SemiAutoBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    PREV_KILL_ = other.PREV_KILL();
    IS_WAITING_ = other.IS_WAITING();
    UPGRADED_SHOOTINGROBOT_ = robotType_;

    UPGRADED_MOVINGROBOT_ = other.UPGRADED_MOVINGROBOT();
    UPGRADED_SEEINGROBOT_ = other.UPGRADED_SEEINGROBOT();
    numOfLives_ = other.numOfLives();
}

SemiAutoBot &SemiAutoBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void SemiAutoBot::actionFire(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionFire" << endl;

    if (SHELL_COUNT_ <= 0) // skip if no more shells
    {
        return;
    }

    const int startCols = shootStartCols();
    const int startRows = shootStartRows();
    const int shootColsWidth = 3;
    const int shootRowsWidth = 3;
    setPREV_KILL(false);
    bool temp = false;

    // clear previous round valid move locations
    for (size_t i = 0; i < shoot_.size(); i++)
    {
        if (shoot_[i])
        {
            delete shoot_[i];
        }
        shoot_[i] = nullptr;
    }
    shoot_.clear();

    // find valid move locations
    location *newLoc;
    for (int j = 0; j < shootRowsWidth; j++)
    {
        for (int i = 0; i < shootColsWidth; i++)
        {
            const int x = startCols + i;
            const int y = startRows + j;

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                continue;
            }

            if (battlefield->isValidFireLocation(x, y)) // remove out of bound areas and other robots
            {
                newLoc = new location(x, y);
                shoot_.push_back(newLoc);
            }
        }
    }

    // find closest enemy from view
    location *foundEnemy = nullptr;
    locationSortVector(view_);
    for (size_t i = 0; i < view_.size() && !foundEnemy; i++)
    {
        if (view_[i]->value != "*" && view_[i]->value != "#")
        {
            foundEnemy = view_[i];
        }
    }

    // perform shoot based on if foundenemy or not
    if (foundEnemy)
    {
        locationSortVector(shoot_, foundEnemy);
        if (locationRelativeDistanceChebyshev(foundEnemy, shoot_[0]) == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                if (SHELL_COUNT_ > 0)
                {
                    temp = battlefield->strike(shoot_[0]->locX, shoot_[0]->locY, SHOOT_SUCCESS_PERCENTAGE, this); // move to location that's towards enemy
                    SHELL_COUNT_--;
                    if (temp)
                    {
                        setPREV_KILL(true);
                        incrementKills();
                    }
                }
            }
        }
    }
    else
    {
        const int randIndex = rand() % (shoot_.size());
        for (int i = 0; i < 3; i++)
        {
            if (SHELL_COUNT_ > 0)
            {

                temp = battlefield->strike(shoot_[randIndex]->locX, shoot_[randIndex]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
                SHELL_COUNT_--;
                if (temp)
                {
                    setPREV_KILL(true);
                    incrementKills();
                }
            }
        }
    }
}

ShotgunBot::ShotgunBot(string id, string name, int x, int y)
{
    // ctor
    id_ = id;
    robotName_ = name;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "ShotgunBot";
    SHOOT_SUCCESS_PERCENTAGE = 40;
    SHELL_COUNT_ = 10;
    UPGRADED_SHOOTINGROBOT_ = robotType_;

    SPREAD_SHOOT_SUCCESS_PERCENTAGE = 10; // 3*10 + 40 = 70
}

ShotgunBot::~ShotgunBot()
{
    // dtor
    for (int i = 0; i < shotgun_spread.size(); i++)
    {
        if (shotgun_spread[i])
        {
            delete shotgun_spread[i];
        }
        shotgun_spread[i] = nullptr;
    }
}

ShotgunBot::ShotgunBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotName_ = other.robotName();
    numOfKills_ = other.numOfKills();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "ShotgunBot";
    SHOOT_SUCCESS_PERCENTAGE = 40;
    SHELL_COUNT_ = 10;
    PREV_KILL_ = other.PREV_KILL();
    IS_WAITING_ = other.IS_WAITING();
    UPGRADED_SHOOTINGROBOT_ = robotType_;

    SPREAD_SHOOT_SUCCESS_PERCENTAGE = 10; // 3*10 + 40 = 70

    UPGRADED_MOVINGROBOT_ = other.UPGRADED_MOVINGROBOT();
    UPGRADED_SEEINGROBOT_ = other.UPGRADED_SEEINGROBOT();
    numOfLives_ = other.numOfLives();
}

ShotgunBot &ShotgunBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void ShotgunBot::actionFire(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionFire" << endl;

    if (SHELL_COUNT_ <= 0) // skip if no more shells
    {
        return;
    }

    const int startCols = shootStartCols();
    const int startRows = shootStartRows();
    const int shootColsWidth = 3;
    const int shootRowsWidth = 3;
    setPREV_KILL(false);
    bool temp;

    // clear previous round valid move locations
    for (size_t i = 0; i < shoot_.size(); i++)
    {
        if (shoot_[i])
        {
            delete shoot_[i];
        }
        shoot_[i] = nullptr;
    }
    shoot_.clear();

    for (int i = 0; i < shotgun_spread.size(); i++)
    {
        if (shotgun_spread[i])
        {
            delete shotgun_spread[i];
        }
        shotgun_spread[i] = nullptr;
    }
    shotgun_spread.clear();

    // find valid move locations
    location *newLoc;
    for (int j = 0; j < shootRowsWidth; j++)
    {
        for (int i = 0; i < shootColsWidth; i++)
        {
            const int x = startCols + i;
            const int y = startRows + j;

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                continue;
            }

            if (battlefield->isValidFireLocation(x, y)) // remove out of bound areas and other robots
            {
                newLoc = new location(x, y);
                shoot_.push_back(newLoc);
            }
        }
    }

    // find closest enemy from view
    location *foundEnemy = nullptr;
    locationSortVector(view_);
    for (size_t i = 0; i < view_.size() && !foundEnemy; i++)
    {
        if (view_[i]->value != "*" && view_[i]->value != "#")
        {
            foundEnemy = view_[i];
        }
    }

    // perform shoot based on if foundenemy or not

    if (foundEnemy)
    {

        locationSortVector(shoot_, foundEnemy);
        if (locationRelativeDistanceChebyshev(foundEnemy, shoot_[0]) == 0)
        {
            if (SHELL_COUNT_ > 0)
            {
                temp = battlefield->strike(shoot_[0]->locX, shoot_[0]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
                if (temp)
                {
                    setPREV_KILL(true);
                    incrementKills();
                }
                setShotgunSpread(shoot_[0]);
                for (auto a : shotgun_spread)
                {
                    if (battlefield->isValidFireLocation(a->locX, a->locY))
                    {
                        temp = battlefield->strike(a->locX, a->locY, SPREAD_SHOOT_SUCCESS_PERCENTAGE, this);
                        if (temp)
                        {
                            setPREV_KILL(true);
                            incrementKills();
                        }
                    }
                }
                SHELL_COUNT_--;
            }
        }
    }
    else
    {
        if (SHELL_COUNT_ > 0)
        {
            const int randIndex = rand() % (shoot_.size());
            temp = battlefield->strike(shoot_[randIndex]->locX, shoot_[randIndex]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
            if (temp)
            {
                setPREV_KILL(true);
                incrementKills();
            }
            setShotgunSpread(shoot_[randIndex]);
            for (auto a : shotgun_spread)
            {
                if (battlefield->isValidFireLocation(a->locX, a->locY))
                {
                    temp = battlefield->strike(a->locX, a->locY, SPREAD_SHOOT_SUCCESS_PERCENTAGE, this);
                    if (temp)
                    {
                        setPREV_KILL(true);
                        incrementKills();
                    }
                }
            }
            SHELL_COUNT_--;
        }
    }
}

void ShotgunBot::setShotgunSpread(location *shootLoc)
{
    int relx = shootLoc->locX - robotPositionX;
    int rely = shootLoc->locY - robotPositionY;
    if (relx > 0)
    {
        relx = 1;
    }
    else if (relx < 0)
    {
        relx = -1;
    };

    if (rely > 0)
    {
        rely = 1;
    }
    else if (rely < 0)
    {
        rely = -1;
    }

    if (!relx) // top bottom
    {
        /*
        T = target
        R = self
        X = shotgun spread
        top side:
        **X**
        *XTX*
        **R**
        *****
        *****

        */
        shotgun_spread.push_back(new location(shootLoc->locX, shootLoc->locY + rely));
        shotgun_spread.push_back(new location(shootLoc->locX + 1, shootLoc->locY));
        shotgun_spread.push_back(new location(shootLoc->locX - 1, shootLoc->locY));
    }
    else if (!rely) // left right
    {
        /*
        T = target
        R = self
        X = shotgun spread
        left side:
        *****
        *X***
        XTR**
        *X***
        *****

        */

        shotgun_spread.push_back(new location(shootLoc->locX + relx, shootLoc->locY));
        shotgun_spread.push_back(new location(shootLoc->locX, shootLoc->locY + 1));
        shotgun_spread.push_back(new location(shootLoc->locX, shootLoc->locY - 1));
    }
    else if (relx && rely) // corners
    {
        /*
        T = target
        R = self
        X = shotgun spread
        top left side:
        XX***
        XT***
        **R**
        *****
        *****

        */
        shotgun_spread.push_back(new location(shootLoc->locX + relx, shootLoc->locY + rely));
        shotgun_spread.push_back(new location(shootLoc->locX + relx, shootLoc->locY));
        shotgun_spread.push_back(new location(shootLoc->locX, shootLoc->locY + rely));
    }
}

ThirtyShotBot::ThirtyShotBot(string id, string name, int x, int y)
{
    // ctor
    id_ = id;
    robotName_ = name;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "ThirtyShotBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 30;
    UPGRADED_SHOOTINGROBOT_ = robotType_;
}

ThirtyShotBot::~ThirtyShotBot()
{
    // dtor
}

ThirtyShotBot::ThirtyShotBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotName_ = other.robotName();
    numOfKills_ = other.numOfKills();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "ThirtyShotBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 30;
    PREV_KILL_ = other.PREV_KILL();
    IS_WAITING_ = other.IS_WAITING();
    UPGRADED_SHOOTINGROBOT_ = robotType_;

    UPGRADED_MOVINGROBOT_ = other.UPGRADED_MOVINGROBOT();
    UPGRADED_SEEINGROBOT_ = other.UPGRADED_SEEINGROBOT();
    numOfLives_ = other.numOfLives();
}

ThirtyShotBot &ThirtyShotBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void ThirtyShotBot::actionFire(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionFire" << endl;

    if (SHELL_COUNT_ <= 0) // skip if no more shells
    {
        return;
    }

    const int startCols = shootStartCols();
    const int startRows = shootStartRows();
    const int shootColsWidth = 3;
    const int shootRowsWidth = 3;
    setPREV_KILL(false);
    bool temp = false;

    // clear previous round valid move locations
    for (size_t i = 0; i < shoot_.size(); i++)
    {
        if (shoot_[i])
        {
            delete shoot_[i];
        }
        shoot_[i] = nullptr;
    }
    shoot_.clear();

    // find valid move locations
    location *newLoc;
    for (int j = 0; j < shootRowsWidth; j++)
    {
        for (int i = 0; i < shootColsWidth; i++)
        {
            const int x = startCols + i;
            const int y = startRows + j;

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                continue;
            }

            if (battlefield->isValidFireLocation(x, y)) // remove out of bound areas and other robots
            {
                newLoc = new location(x, y);
                shoot_.push_back(newLoc);
            }
        }
    }

    // find closest enemy from view
    location *foundEnemy = nullptr;
    locationSortVector(view_);
    for (size_t i = 0; i < view_.size() && !foundEnemy; i++)
    {
        if (view_[i]->value != "*" && view_[i]->value != "#")
        {
            foundEnemy = view_[i];
        }
    }

    // perform shoot based on if foundenemy or not
    if (foundEnemy)
    {
        locationSortVector(shoot_, foundEnemy);
        if (locationRelativeDistanceChebyshev(foundEnemy, shoot_[0]) == 0)
        {
            if (SHELL_COUNT_ > 0)
            {
                temp = battlefield->strike(shoot_[0]->locX, shoot_[0]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
                SHELL_COUNT_--;
                if (temp)
                {
                    setPREV_KILL(true);
                    incrementKills();
                }
            }
        }
    }
    else
    {
        if (SHELL_COUNT_ > 0)
        {
            const int randIndex = rand() % (shoot_.size());
            temp = battlefield->strike(shoot_[randIndex]->locX, shoot_[randIndex]->locY, SHOOT_SUCCESS_PERCENTAGE, this);
            SHELL_COUNT_--;
            if (temp)
            {
                setPREV_KILL(true);
                incrementKills();
            }
        }
    }
}

TrackBot::TrackBot(string id, string name, int x, int y)
{
    // ctor
    id_ = id;
    robotName_ = name;
    robotPositionX = x;
    robotPositionY = y;
    robotType_ = "TrackBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    UPGRADED_SEEINGROBOT_ = robotType_;
}

TrackBot::~TrackBot()
{
    // dtor
}

TrackBot::TrackBot(const Robot &other)
{
    // copy ctor
    id_ = other.id();
    robotName_ = other.robotName();
    numOfKills_ = other.numOfKills();
    robotPositionX = other.x();
    robotPositionY = other.y();
    robotType_ = "TrackBot";
    SHOOT_SUCCESS_PERCENTAGE = 70;
    SHELL_COUNT_ = 10;
    PREV_KILL_ = other.PREV_KILL();
    IS_WAITING_ = other.IS_WAITING();
    UPGRADED_SEEINGROBOT_ = robotType_;

    UPGRADED_MOVINGROBOT_ = other.UPGRADED_MOVINGROBOT();
    UPGRADED_SHOOTINGROBOT_ = other.UPGRADED_SHOOTINGROBOT();
    numOfLives_ = other.numOfLives();
}

TrackBot &TrackBot::operator=(const Robot &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    // assignment operator
    return *this;
}

void TrackBot::actionLook(Battlefield *battlefield)
{
    *battlefield << robotType_ << " actionLook" << endl;

    const int startCol = viewStartCols();
    const int startRow = viewStartRows();
    const int viewColsWidth = 3;
    const int viewRowsWidth = 3;

    for (size_t i = 0; i < view_.size(); i++)
    {
        if (view_[i])
        {
            delete view_[i];
        }
        view_[i] = nullptr;
    }
    view_.clear();

    string val;
    location *newLoc;

    for (int j = 0; j < viewRowsWidth; j++)
    {
        *battlefield << ">";
        for (int i = 0; i < viewColsWidth; i++)
        {
            const int x = startCol + i;
            const int y = startRow + j;
            val = battlefield->peek(x, y);

            if (x == robotPositionX && y == robotPositionY) // remove self position
            {
                *battlefield << " " << left << setfill(' ') << setw(4) << id_;
                continue;
            }

            if (val != "") // remove out of bound areas
            {
                newLoc = new location(x, y, val);
                view_.push_back(newLoc);
                *battlefield << " " << left << setfill(' ') << setw(4) << val;

                if (trackedBotsIds_.size() < 3 && val != "*" && val != "#") // if still has space to track bots
                {
                    bool AlreadyTracking = false;
                    for (string enemyId : trackedBotsIds_)
                    {
                        if (enemyId == val)
                        {
                            AlreadyTracking = true;
                        }
                    }

                    if (!AlreadyTracking)
                    {
                        trackedBotsIds_.push_back(val);
                    }
                }
            }
        }
        *battlefield << " " << endl;
    }

    locationSortVector(view_);

    for (vector<string>::iterator Idptr = trackedBotsIds_.begin(); Idptr != trackedBotsIds_.end(); Idptr++)
    {
        Robot *enemyPtr = battlefield->findRobotById(*Idptr);
        if (enemyPtr != nullptr && enemyPtr->isAlive())
        {
            if (!enemyPtr->IS_WAITING())
            {
                *battlefield << "> Tracking " << *enemyPtr << endl;
                location *loc = new location(enemyPtr->x(), enemyPtr->x(), enemyPtr->id()); // add robot enemy's position to view, to track in the next move
                view_.push_back(loc);
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                     //
//                                            END OF DEFINITIONS                                                       //
//                                                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                     //
//                                            START OF MAIN                                                            //
//                                                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

    // 243UC247BM
    // static cast to shut up compiler warnings
    srand(static_cast<unsigned int>(243213247213));

    // create battlefield
    Battlefield battlefield;

    // ask for file name
    string i;
    cout << "Enter input file name:" << endl;
    cin >> i;
    cout << endl;

    // initialise battlefield from input file
    battlefield.readFile(i);

    // run turns
    battlefield.MAIN();

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                     //
//                                            END OF MAIN                                                              //
//                                                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
