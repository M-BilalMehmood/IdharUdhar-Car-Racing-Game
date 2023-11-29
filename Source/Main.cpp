#include<iostream>
#include"/Git Dev/DS-Project/Libraries/header.h"
//#include"header.h"
using namespace std;

// This temp code was just to check if the files are communicating with each other or not.

int main()
{
    while (1)
    {
        srand(time(0)); // Seed the random number generator with the current time
        cout << "::>";
        int m;
        cin >> m;

        Graph g(m);

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rand() % 2) { // 50% chance to add a horizontal edge
                    if (j < m - 1) { // Don't add a horizontal edge for the last column
                        g.addEdge(i, j, i, j + 1, rand() % 100 + 1); // Random weight between 1 and 100
                    }
                }
                if (rand() % 2) { // 50% chance to add a vertical edge
                    if (i < m - 1) { // Don't add a vertical edge for the last row
                        g.addEdge(i, j, i + 1, j, rand() % 100 + 1); // Random weight between 1 and 100
                    }
                }
            }
        }

        g.print();
    }
    return 0;
}

// All rights reserved by the Affan Hameed and Bilal Mehmood.