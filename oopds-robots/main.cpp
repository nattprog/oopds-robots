#include "Battlefield.h"
// #include "RobotFileWriter.h"

using namespace std;

int main()
{

    // 243UC247BM
    // static cast to shut up compiler warnings
    srand(static_cast<unsigned int>(243213247213));

    Battlefield battlefield;

    // NOTE THAT THIS IS NOT TO BE THE FINAL WAY TO RUN PROGRAM
    vector<Robot *> *rbtPtr = new vector<Robot *>;
    for (size_t i = 0; i < 5; i++)
    {
        Robot *a = new GenericRobot("GR0" + to_string(i), i, i);
        rbtPtr->push_back(a);
    }
    battlefield.setRobots(*rbtPtr);
    delete rbtPtr;
    // IGNORE TILL HERE

    battlefield.MAIN();

    return 0;
}
