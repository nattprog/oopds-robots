#include <iostream>
#include <fstream>
#include <string>
#include "RobotFileWriter.h"
using namespace std;

class file_output
{

private:
public:
    void run(ofstream &outfile)
    {
        int m, n;
        cout << "Enter battlefield size (M N): ";
        cin >> m >> n;
        outfile << "M by N : " << m << " " << n << endl;

        int steps;
        cout << "Enter number of steps: ";
        cin >> steps;
        outfile << "steps: " << steps << endl;

        // Number of robots
        int robotCount;
        cout << "Enter number of robots: ";
        cin >> robotCount;
        outfile << "robots: " << robotCount << endl;

        // Clear input buffer before getline
        cin.ignore();

        // Robot data
        for (int i = 0; i < robotCount; ++i)
        {
            string type, name, x, y;

            cout << "Enter robot " << i + 1 << " (type name x y): ";
            getline(cin, type, ' ');
            getline(cin, name, ' ');
            getline(cin, x, ' ');
            getline(cin, y);

            outfile << type << " " << name << " " << x << " " << y << endl;
        }
    }
};

// int main(){

// ofstream outfile;

//  string fn;
//  cout<<"Enter your file name:";
//  getline(cin , fn);

//  outfile.open(fn);

//   if (outfile.is_open()){
//   file_output* ptr  = new file_output();

//     ptr -> run(outfile);
//     delete ptr;

//  outfile.close();

//      cout << "Data written to file."<<fn << endl;
//   }
//   else {
//   cerr<<"Error!"<<fn <<endl;
//   }
//   return 0;
// }
