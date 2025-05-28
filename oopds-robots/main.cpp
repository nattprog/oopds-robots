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
    for (size_t i = 0; i < 4; i++)
    {
        Robot *a = new GenericRobot("GR0" + to_string(i), (i + (rand() % 2)) * 2, i * 2);
        if (i == 0) // you're controlling only GR00 for now
        {
            b = a;
        }
        rbtPtr->push_back(a);
    }

    // set test robot type here:
    b = new HideBot("GR05", 19, 0);
    rbtPtr->push_back(b);

    battlefield.setRobots(*rbtPtr);
    battlefield.placeRobots();
    battlefield.displayBattlefield();

    // Press enter to advance through the turns, enter any other key to stop.
    while (getchar() == '\n')
    {
        cout << endl;
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