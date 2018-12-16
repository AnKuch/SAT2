#include <iostream>
#include "main.h"

using namespace std;


string input;


int main()
{
    cout << "Hello world!" << endl;
    cout << "What file do you want to be analyzed?" << endl;
    cin >> input;
    cnfRead(input);

    return 0;
}
