#include "Battlefield.h"
// #include "RobotFileWriter.h"

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
    b = new LifestealBot("GR05", 8, 8);
    rbtPtr->push_back(b);

    battlefield.setRobots(*rbtPtr);
    battlefield.placeRobots();
    battlefield.displayBattlefield();
    auto ptr = rbtPtr->begin();

    // Press enter to advance through the turns, enter any other key to stop.
    do
    {
        if (ptr == rbtPtr->end())
        {
            ptr = rbtPtr->begin();
        }
        cout << endl;
        cout << *(*ptr) << endl;
        (*ptr)->actions(&battlefield);
        battlefield.placeRobots();
        battlefield.displayBattlefield();
        ptr++;

    } while (getchar() == '\n');

    return 0;
}
