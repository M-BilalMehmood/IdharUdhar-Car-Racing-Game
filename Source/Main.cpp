#include<iostream>
//#include"/Git Dev/DS-Project/DS-Project/Libraries/header.h"
//#include"/Git Dev/DS-Project/Libraries/header.h"
#include"../Libraries/header.h"
//#include"header.h"
using namespace std;

// This temp code was just to check if the files are communicating with each other or not.

int main()
{
    cout << "Choose your vehicle:" << endl;
    cout << "1.\033[33m \\o=o>\033[0m" << endl;
    cout << "2.\033[33m Lo=o>\033[0m" << endl;
    cout << "3.\033[33m Co=o>\033[0m" << endl;
    while (1)
    {
        cout << "::>";
        int m;
        cin >> m;

        // Graph g(m);
        // g.makeGrid(m);

        while (true) {
            Graph g(m); // Create a graph with m*m vertices
            // ... Add edges to the graph ...

            g.makeGrid(m);

            if (g.bfs(g, 0, m * m - 1, m))
            {
                g.print(m);
                break;
            }
        }
    }
    return 0;
}

// All rights reserved by the Affan Hameed and Bilal Mehmood.