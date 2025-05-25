#include "Battlefield.h"
#include "RobotFileWriter.h"

using namespace std;

int main()
{

    // 243UC247BM
    // static cast to shut up compiler warnings
    srand(static_cast<unsigned int>(243213247213));
    cout << "srand: " << rand() << " " << rand() << endl;

    Battlefield battlefield;

    // vector<Robot *> *rbtPtr = new vector<Robot *>;
    // for (int i = 0; i < 10; i++)
    // {
    //     GenericRobot *a = new GenericRobot("GRO1", i, 1);
    //     rbtPtr->push_back(a);
    // }

    // battlefield.setRobots(*rbtPtr);

    // battlefield.placeRobots();

    // battlefield.displayBattlefield();

    return 0;
}

// RobotFileWriter writer;
// std::string filename;

// std::cout << "Enter filename to save robot data: ";
// std::getline(std::cin, filename);

// writer.createFileFromUserInput(filename);

// Battlefield battlefield;
// Robot *robotGenericRobot = new GenericRobot("GRO1", 4, 4);
// std::cout << *robotGenericRobot << endl;
// robotGenericRobot->actions(&battlefield);
// delete robotGenericRobot;
// robotGenericRobot = nullptr;