#include "Battlefield.h"
#include <regex>

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

int Battlefield::BATTLEFIELD_NUM_OF_COLS() { return BATTLEFIELD_NUM_OF_COLS_; }
int Battlefield::BATTLEFIELD_NUM_OF_ROWS() { return BATTLEFIELD_NUM_OF_ROWS_; }
int Battlefield::turns() { return turns_; }
int Battlefield::numOfRobots() { return numOfRobots_; }

void Battlefield::readFile(string filename)
{
    string line, allLines;
    ifstream inputFile; // file object
    inputFile.open(filename); // file object refers to this file now

    if (!inputFile)
    {
        cout << "File not found." << endl;
    }
    else
    {
        cout << "File found." << endl;
    }

    while(getline(inputFile, line))
    {
        allLines += line;
    }
    inputFile.close();
    ////////////////////////////////////
    smatch fieldMatch;
    smatch turnsMatch;
    smatch roboNumMatch;
    smatch typeMatch;
    int roboX;
    int roboY;

    regex getFieldSize(R"(M by N: (\d+) (\d+)\w*)"); // To get battlefield size
    regex_search(allLines, fieldMatch, getFieldSize); // searches allLines for match
    int fieldM = stoi(fieldMatch[1]);
    int fieldN = stoi(fieldMatch[2]);
    
    regex getTurns(R"(\w*(turns: (\d+))\w*)");
    regex_search(allLines, turnsMatch, getTurns);
    int turns = stoi(turnsMatch[2]);
    
    regex getnumRobots(R"(robots: (\d+))");
    regex_search(allLines, roboNumMatch, getnumRobots);
    int numRobots = stoi(roboNumMatch[1]);

    string::const_iterator textStart(allLines.cbegin()); // iterator for allLines (maybe separating the robot identifying chunk of text and iterating thru that is better?)
    regex getType(R"((([a-zA-Z]*Robot) (\w{4,5}_\w{1,10}) ([1-9]?[0-9]|\w+) ([1-9]?[0-9]|\w+)))");
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
        
        cout << roboType << endl;
        cout << roboName << endl;
        cout << roboX << endl;
        cout << roboY << endl;

        textStart = typeMatch.suffix().first;

        if (roboType == "GenericRobot")
        {
            Robot *newBot = new GenericRobot(roboName, roboX, roboY);
            robots_.push_back(newBot);
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

string Battlefield::look(int x, int y) const
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

    if (look(x, y) == "*")
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
    const string val = look(x, y);

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

Robot *Battlefield::bomb(int x, int y, int successPercent)
{
    string val = look(x, y);

    if (val == "*" || val == "#" && val == "")
    { // if unsuccessful
        return nullptr;
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
        return nullptr;
    }

    int random = rand() % 100;
    cout << "random is: " << random << endl;
    if (random < successPercent)
    {
        // successful kill
        (*botIter)->reduceLife();

        // if still has lives left, add to waiting
        if ((*botIter)->isAlive())
        {
            waitingRobots_.push((*botIter));
            cout << *(*botIter) << " has been killed. " << (*botIter)->numOfLives() << " lives remaining." << endl;
        }
        else
        { // else destroyed
            destroyedRobots_.push((*botIter));
            cout << (*botIter) << " has been destroyed." << endl;
        }

        robots_.erase(botIter);

        return *botIter;
    }
    return nullptr;
}