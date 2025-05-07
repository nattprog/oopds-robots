#include <iostream>
#include "RoboCop.h"
#include "Terminator.h"
#include "TerminatorRoboCop.h"
#include "BlueThunder.h"
#include "Madbot.h"
#include "RoboTank.h"
#include "UltimateRobot.h"
#include "RobotFileWriter.h"


using namespace std;

int main()
{
    RoboCop a;
    cout << "Hello world!" << endl;

   RobotFileWriter writer;
    std::string filename;

    std::cout << "Enter filename to save robot data: ";
    std::getline(std::cin, filename);

    writer.createFileFromUserInput(filename);

    return 0;

}
