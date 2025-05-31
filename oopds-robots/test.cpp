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
        cout << "File not found." << endl;
        return "";
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
    return allLines;
}

string regexfunc(string textinput)
{
    // string allLines = getLines("D:\\Documents\\Projects\\OOPDS\\oopds-robots\\oopds-robots\\fileinput2.txt");
    smatch fieldMatch;
    smatch turnsMatch;
    smatch roboMatch;
    smatch typeMatch;
    int roboX;
    int roboY;

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

    string::const_iterator textStart(textinput.cbegin());
    regex getType(R"((([a-zA-Z]*Robot) (\w{4,5}_\w{1,10}) ([1-9]?[0-9]|\w+) ([1-9]?[0-9]|\w+)))");
    while (regex_search(textStart, textinput.cend(), typeMatch, getType))
    {
        string roboType = typeMatch[2];
        string roboName = typeMatch[3];
        cout << typeMatch[4] << "<--typematch[4]--" << endl;
        cout << typeMatch[5] << "<--typematch[5]--" << endl;

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
    }

    return "";
}

int main()
{
    // string fileName;
    // cout << "Input file name: " << endl;
    // cin >> fileName;
    string allLines = getLines("D:\\Documents\\Projects\\OOPDS\\oopds-robots\\oopds-robots\\fileinput2.txt");
    // cout << allLines << endl;
    regexfunc(allLines);

    return 0;
}