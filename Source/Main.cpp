#include<iostream>
//#include"/Git Dev/DS-Project/DS-Project/Libraries/header.h"
//#include"/Git Dev/DS-Project/Libraries/header.h"
#include"../Libraries/header.h"
//#include"header.h"
using namespace std;

// This temp code was just to check if the files are communicating with each other or not.

int main()
{
    int m;
    cout << "Enter the size of the grid: ";
    cin >> m;
    Graph g(m);
    g.moveCar(m);
    return 0;
}

// All rights reserved by the Affan Hameed and Bilal Mehmood.