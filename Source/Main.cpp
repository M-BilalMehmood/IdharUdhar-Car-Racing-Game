#include<iostream>
//#include"/Git Dev/DS-Project/DS-Project/Libraries/header.h"
//#include"/Git Dev/DS-Project/Libraries/header.h"
<<<<<<< Updated upstream
#include"../Libraries/header.h"
=======
#include "../Libraries/AutomaticCar_GameManager.h"
#include"../Libraries/Game_Manager.h"

>>>>>>> Stashed changes
//#include"header.h"
using namespace std;

// This temp code was just to check if the files are communicating with each other or not.

int main()
{
    cout << "Mode: " << endl;
    cout << "1. Manual" << endl;
    cout << "2. Automatic" << endl;
    cout << "::> ";
    int mode;
    cin >> mode;
    if (mode == 1)
    {
        cout << "Enter the size of the grid: ";
        int m;
        cin >> m;
        Graph g(m);
        g.moveCar(m);
    }
    else
    {
        cout << "Enter the size of the grid: ";
        int m;
        cin >> m;
        AutoCarGraph g(m);
        g.moveCar(m);
    }
    return 0;
}

// All rights reserved by the Affan Hameed and Bilal Mehmood.