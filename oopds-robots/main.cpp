#include "Battlefield.h"
// #include "RobotFileWriter.h"

using namespace std;

int main()
{

    // 243UC247BM
    // static cast to shut up compiler warnings
    srand(static_cast<unsigned int>(243213247213));

    // create battlefield
    Battlefield battlefield;

    // ask for file name
    string i;
    cout << "Enter input file name:" << endl;
    cin >> i;
    cout << endl;

    // initialise battlefield from input file
    battlefield.readFile(i);

    // run turns
    battlefield.MAIN();

    return 0;
}
