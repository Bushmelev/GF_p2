#include <iostream>
#include "GF_p2.h"

using namespace std;

int main() {
    while (true) {       
        GF_p2 g1, g2;
        int m;
        cout << "Input m: ";
        cin >> m;
        if (!cin.good())
            break;
        GF_p2::setMod(m);
        GF_p2::setRes(m);
        cout << "Enter coefficients: " << endl;
        std::cin >> g1;
        cout << "Enter coefficients: " << endl;
        std::cin >> g2;
        cout << "Sum: " << g1 + g2;
        cout << "Difference: " << g1 - g2;
        cout << "Multiplication: " << g1 * g2;
        GF_p2 g6 = g1.inverse();
        cout << "Inverse: " << g1.inverse();
        cout << "Division: " << g1 / g2;    
        cout << "Power: " << g1.power(3);
    }
    return 0;
}