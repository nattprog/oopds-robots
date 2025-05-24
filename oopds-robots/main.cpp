#include <iostream>
#include "Battlefield.h"
#include "GenericRobot.h"
#include "HideBot.h"
#include "JumpBot.h"
#include "LongShotBot.h"
#include "SemiAutoBot.h"
#include "ThirtyShotBot.h"
#include "ScoutBot.h"
#include "TrackBot.h"

#include "RobotFileWriter.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    GenericRobot a;

    // RobotFileWriter writer;
    // std::string filename;

    // std::cout << "Enter filename to save robot data: ";
    // std::getline(std::cin, filename);

    // writer.createFileFromUserInput(filename);

    cout << "C++ version: " << __cplusplus << endl;
    return 0;
}