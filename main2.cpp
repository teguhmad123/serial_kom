#include <iostream>
#include <string>
#include <vector>
#include "variabel.h"
using namespace std;

// class MyClass
// {       // The class
// public: // Access specifier
//     struct Mpos
//     {
//         float x, y, z;
//     };
//     static Mpos mpos;
//     int myNum;       // Attribute (int variable)
//     string myString; // Attribute (string variable)
// };

// MyClass::Mpos MyClass::mpos;

void second()
{
    cout << "second\n";
    cout << Variabel::mpos.x << "\n";
    cout << Variabel::mpos.y << "\n";
    cout << Variabel::mpos.z;
}

int main()
{
    // Variabel myObj; // Create an object of Variabel

    // Access attributes and set values
    // myObj.myNum = 15;
    // myObj.myString = "Some text";

    std::vector<float> mpos;
    mpos.push_back(10);
    mpos.push_back(11);
    mpos.push_back(12);

    Variabel::mpos.x = mpos[0];
    Variabel::mpos.y = mpos[1];
    Variabel::mpos.z = mpos[2];

    // Print values
    cout << "Main\n";
    cout << Variabel::mpos.x << "\n";
    cout << Variabel::mpos.y << "\n";
    cout << Variabel::mpos.z;

    second();
    return 0;
}
