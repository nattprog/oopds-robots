#include "Battlefield.h"
#include "RobotFileWriter.h"

using namespace std;

int main()
{

    // 243UC247BM
    // static cast to shut up compiler warnings
    srand(static_cast<unsigned int>(243213247213));

    Battlefield Battlefield;

    return 0;
}

// RobotFileWriter writer;
// std::string filename;

// std::cout << "Enter filename to save robot data: ";
// std::getline(std::cin, filename);

// writer.createFileFromUserInput(filename);

// vector<Robot *> *rbtPtr = new vector<Robot *>;
// for (int i = 0; i < 10; i++)
// {
//     GenericRobot *a = new GenericRobot("GRO1", i, i);
//     rbtPtr->push_back(a);
// }

// battlefield.setRobots(*rbtPtr);

// battlefield.placeRobots();

// battlefield.displayBattlefield();

// Battlefield battlefield;
// Robot *robotGenericRobot = new GenericRobot("GRO1", 4, 4);
// std::cout << *robotGenericRobot << endl;
// robotGenericRobot->actions(&battlefield);
// delete robotGenericRobot;
// robotGenericRobot = nullptr;