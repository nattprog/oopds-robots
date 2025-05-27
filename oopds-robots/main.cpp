#include "Battlefield.h"
#include "RobotFileWriter.h"

using namespace std;

int main()
{

    // 243UC247BM
    // static cast to shut up compiler warnings
    srand(static_cast<unsigned int>(243213247213));

    Battlefield battlefield;

    vector<Robot *> *rbtPtr = new vector<Robot *>;
    Robot *b;
    for (size_t i = 0; i < 10; i++)
    {
        Robot *a = new GenericRobot("GR0" + to_string(i), i + (rand() % 2), i);
        if (i == 0) // you're controlling only GR00 for now
        {
            b = a;
        }
        rbtPtr->push_back(a);
    }
    battlefield.setRobots(*rbtPtr);
    battlefield.placeRobots();
    battlefield.displayBattlefield();

    for (int i = 0; i < 20; i++) // simulate actions for GR00, all others are frozen
    {
        b->actions(&battlefield);
        battlefield.placeRobots();
        battlefield.displayBattlefield();
    }

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