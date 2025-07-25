#include <iostream>
#include <vector>
#include <string>
#include "./include/termcolor.hpp" // Librería para colores en la consola

using namespace std;

int main()
{
    vector<string> msg {"Hello", "C++", "World"};

    // Usar diferentes colores para cada palabra
    cout << termcolor::red << msg[0] << " ";
    cout << termcolor::green << msg[1] << " ";
    cout << termcolor::blue << msg[2] << " ";
    cout << termcolor::reset << endl;
}
