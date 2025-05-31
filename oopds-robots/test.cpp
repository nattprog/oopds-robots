#include <iostream>
#include <regex>
#include <fstream>
#include <string>

using namespace std;

string getLines(string filename)
{   
    string line, allLines;
    ifstream inputFile; // file object
    inputFile.open(filename); // file object refers to this file now

    if (!inputFile)
    {
        cout << "file not found." << endl;
        return "";
    }
    else
    {
        cout << "file found." << endl;
    }

    while(getline(inputFile, line))
    {
        allLines += line;
    }
    inputFile.close();
    return allLines;
}

string regexfunc(string textinput)
{
    // string allLines = getLines("D:\\Documents\\Projects\\OOPDS\\oopds-robots\\oopds-robots\\fileinput2.txt");
    smatch fieldMatch;
    smatch turnsMatch;
    smatch roboMatch;
    smatch typeMatch;

    regex getFieldSize(R"(M by N: (\d+) (\d+)\w*)"); // to get battlefield size
    regex_search(textinput, fieldMatch, getFieldSize); // searches textinput for match
    int fieldM = stoi(fieldMatch[1]);
    int fieldN = stoi(fieldMatch[2]);
    
    regex getTurns(R"(\w*(turns: (\d+))\w*)");
    regex_search(textinput, turnsMatch, getTurns);
    int turns = stoi(turnsMatch[2]);
    
    regex getnumRobots(R"(robots: (\d+))");
    regex_search(textinput, roboMatch, getnumRobots);
    int numRobots = stoi(roboMatch[1]);

    regex getType(R"(GenericRobot)");

    return "";
}

int main()
{
    // string fileName;
    // cout << "Input file name: " << endl;
    // cin >> fileName;
    string allLines = getLines("D:\\Documents\\Projects\\OOPDS\\oopds-robots\\oopds-robots\\fileinput2.txt");
    cout << allLines << endl;
    regexfunc(allLines);

    return 0;
}