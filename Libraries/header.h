#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <conio.h>
//#include "/Git Dev/DS-Project/DS-Project/Libraries/Queue.h"
#include "BFSQueue.h"
using namespace std;

class Graph
{
private:
    Node* adjList;
    int vertexCount;

public:
    Graph(int V) : vertexCount(V)
    {
        adjList = new Node[V * V];
        for (int i = 0; i < V * V; ++i)
        {
            //the start and end node name should be <|S|>, <|E|>
            if (i == 0)
            {
                adjList[i].name = "<\033[32m|S|\033[35m>";
            }
            else if (i == V * V - 1)
            {
                adjList[i].name = "<\033[32m|E|\033[35m>";
            }
            else
            {
                adjList[i].name = "<<+>>";
            }
            adjList[i].vertex = i;
            adjList[i].edges = new int[V * V];
            adjList[i].weights = new int[V * V];
            adjList[i].edgeCount = 0;
        }
    }

    void addEdge(int x1, int y1, int x2, int y2, int weight)
    {
        if (x1 < 0 || x1 >= vertexCount || y1 < 0 || y1 >= vertexCount || x2 < 0 || x2 >= vertexCount || y2 < 0 || y2 >= vertexCount)
		{
			cout << "Invalid edge!\n";
			return;
		}

        int v = x1 * vertexCount + y1;
        int w = x2 * vertexCount + y2;

        adjList[v].edges[adjList[v].edgeCount] = w;
        adjList[v].weights[adjList[v].edgeCount] = weight;
        adjList[v].edgeCount++;

        adjList[w].edges[adjList[w].edgeCount] = v;
        adjList[w].weights[adjList[w].edgeCount] = weight;
        adjList[w].edgeCount++;
    }

    void makeGrid(int n)
    {
        srand(time(0));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (rand() % 10 < 6.5)  // 65% chance to add a horizontal edge
                {
                    if (j < n - 1)  // Don't add a horizontal edge for the last column
                    {
                        addEdge(i, j, i, j + 1, rand() % 10 + 1); // Random weight between 1 and 10
                    }
                }
                if (rand() % 10 < 6.5) // 65% chance to add a vertical edge
                {
                    if (i < n - 1)  // Don't add a vertical edge for the last row
                    {
                        addEdge(i, j, i + 1, j, rand() % 10 + 1); // Random weight between 1 and 10
                    }
                }
            }
        }
    }

    void car(int n)
    {
        if (n == 1)
        {
            cout << "\033[33m\\o=o>\033[0m";
        }
        if (n == 2)
        {
            cout << "\033[33mLo=o>\033[0m";
        }
        if (n == 3)
        {
            cout << "\033[33mCo=o>\033[0m";
        }
    }

    void moveCar(int m)
    {
        cout << "Choose your vehicle:" << endl;
        cout << "1.\033[33m \\o=o>\033[0m" << endl;
        cout << "2.\033[33m Lo=o>\033[0m" << endl;
        cout << "3.\033[33m Co=o>\033[0m" << endl;
        int n;
        cout << "::> ";
        cin >> n;
        system("cls");
        while (true)
        {
            Graph g(m); // Create a graph with m*m vertices
            // ... Add edges to the graph ...

            g.makeGrid(m);

            if (g.bfs(g, 0, m * m - 1, m))
            {
                int carPos = 0; // The car starts at node 0
                while (true)
                {
                    g.printCar(m, carPos, n);
                    int key = _getch(); // Capture the arrow key input
                    int newPos = carPos;
                    if (key == 72) newPos -= m; // Up arrow key
                    else if (key == 80) newPos += m; // Down arrow key
                    else if (key == 75) newPos--; // Left arrow key
                    else if (key == 77) newPos++; // Right arrow key
                    // Check if the move is valid
                    if (find(g.adjList[carPos].edges, g.adjList[carPos].edges + g.adjList[carPos].edgeCount, newPos) != g.adjList[carPos].edges + g.adjList[carPos].edgeCount)
                    {
                        carPos = newPos;
                    }
                    if (carPos == m * m - 1) // We reached the destination
                    {
                        // system("cls");
                        g.printCar(m, carPos, n);
                        cout << "You win!" << endl;
                        break;
                    }
                }
                break;
            }
        }
    }

    bool bfs(Graph& g, int source, int destination, int m) 
    {
        bool* visited = new bool[m * m];
        for (int i = 0; i < m * m; i++) visited[i] = false;
        int n = m * m;
        Queue q(n);
        q.push(source);
        visited[source] = true;
        while (!q.empty()) 
        {
            int u = q.peek();
            q.pop();
            if (u == destination) 
            {
                delete[] visited;
                return true; // We found a path to the destination
            }
            for (int i = 0; i < g.adjList[u].edgeCount; i++) 
            {
                int v = g.adjList[u].edges[i];
                if (!visited[v]) 
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        delete[] visited;
        return false; // No path found to the destination
    }

    void print(int n)
    {
        system("cls");
        for (int i = 0; i < vertexCount; ++i)
        {
            for (int j = 0; j < vertexCount; ++j)
            {
                int v = i * vertexCount + j;
                // cout << i << j;
                if (i == 0 && j == 0)
                {
                    cout << "\033[35m<\033[32m|S|\033[35m>\033[0m";
                    //cout << "\033[33mCo=o>\033[0m";
                }
                else if (i == n - 1 && j == n - 1)
                {
                    cout << "\033[35m<\033[32m|E|\033[35m>\033[0m";
                }
                else
                {
                    cout << "\033[35m<^-^>\033[0m";
                }
                if (find(adjList[v].edges, adjList[v].edges + adjList[v].edgeCount, v + 1) != adjList[v].edges + adjList[v].edgeCount)
                {
                    cout << "\033[36m----\033[0m";
                }
                else
                {
                    cout << "    ";
                }
            }
            cout << endl;
            if (i < vertexCount - 1)
            {
                for (int j = 0; j < vertexCount; ++j)
                {
                    int v = i * vertexCount + j;
                    if (find(adjList[v].edges, adjList[v].edges + adjList[v].edgeCount, v + vertexCount) != adjList[v].edges + adjList[v].edgeCount)
                    {
                        cout << "\033[36m  |      \033[0m";
                    }
                    else
                    {
                        cout << "         ";
                    }
                }
                cout << endl;
            }
        }
    }

    void printCar(int n, int carPos, int m)
    {
        system("cls");
        for (int i = 0; i < vertexCount; ++i)
        {
            for (int j = 0; j < vertexCount; ++j)
            {
                int v = i * vertexCount + j;
                if (v == carPos)
                {
                    car(m); // Print the car
                }
                else
                {
                    cout << "\033[35m" << adjList[v].name << "\033[0m";
                }
                if (find(adjList[v].edges, adjList[v].edges + adjList[v].edgeCount, v + 1) != adjList[v].edges + adjList[v].edgeCount)
                {
                    cout << "\033[36m----\033[0m";
                }
                else
                {
                    cout << "    ";
                }
            }
            cout << endl;
            if (i < vertexCount - 1)
            {
                for (int j = 0; j < vertexCount; ++j)
                {
                    int v = i * vertexCount + j;
                    if (find(adjList[v].edges, adjList[v].edges + adjList[v].edgeCount, v + vertexCount) != adjList[v].edges + adjList[v].edgeCount)
                    {
                        cout << "\033[36m  |      \033[0m";
                    }
                    else
                    {
                        cout << "         ";
                    }
                }
                cout << endl;
            }
        }
    }

    ~Graph()
    {
        for (int i = 0; i < vertexCount * vertexCount; ++i)
        {
            delete[] adjList[i].edges;
            delete[] adjList[i].weights;
        }
        delete[] adjList;
    }
};

// All rights reserved by Affan Hameed and Bilal Mehmood.