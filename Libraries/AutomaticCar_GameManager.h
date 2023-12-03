#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include "../Libraries/Stack.h"
#include "../Libraries/PriorityQueue.h"
#include "../Libraries/Objects_Manager.h"
#include "../Libraries/Queue.h"
#include "../Libraries/BFSQueue.h"
using namespace std;
#pragma comment(lib, "winmm.lib")

struct AutoCarGraphNode
{
    string name;
    int vertex;
    int* edges;
    int* weights;
    int edgeCount;
};

class AutoCarGraph
{
private:
    AutoCarGraphNode* adjList;
    //Queue<Object*> objectQueue;
    int vertexCount;
    int score = 0;
    int objectCount = 0;

public:
    AutoCarGraph(int V) : vertexCount(V)
    {
        adjList = new AutoCarGraphNode[V * V];
        for (int i = 0; i < V * V; ++i)
        {
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
                if (rand() % 10 < 6.5) // 65% chance to add a horizontal edge
                {
                    if (j < n - 1) // Don't add a horizontal edge for the last column
                    {
                        addEdge(i, j, i, j + 1, rand() % 10 + 1); // Random weight between 1 and 10
                    }
                }
                if (rand() % 10 < 6.5) // 65% chance to add a vertical edge
                {
                    if (i < n - 1) // Don't add a vertical edge for the last row
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
        PlaySound(TEXT("WhileGamming.wav"), NULL, SND_ASYNC | SND_LOOP);
        system("cls");

        AutoCarGraph g(m); // Create a graph with m*m vertices
        makeGrid(m);

        // Run BFS to ensure there's at least one path from start to end
        if (!bfs(0, m * m - 1, m))
        {
            cout << "No path found from start to end. Exiting..." << endl;
            return;
        }

        int* distances = new int[m * m];
        int* previous = new int[m * m];
        dijkstra(0, m * m - 1, distances, previous);

        if (distances[m * m - 1] != INT_MAX) {
            moveCarAutomatically(0, m * m - 1, previous, m, n);
            cout << "You win!" << endl;
        }
        else
        {
            cout << "No path found from start to end. Exiting..." << endl;
        }

        delete[] distances;
        delete[] previous;
    }

    void moveCarAutomatically(int start, int end, int* previous, int m, int n)
    {
        // Use a stack to reverse the path from end to start
        Stack path;
        for (int node = end; node != start; node = previous[node])
        {
            path.push(node);
        }
        path.push(start); // Don't forget to add the start node

        // Move the car along the path
        while (!path.isEmpty())
        {
            int node = path.peek();
            path.pop();
            this->printCar(m, node, n);
            Sleep(1200);
        }
    }

    void dijkstra(int start, int end, int* distances, int* previous)
    {
        PriorityQueue queue(this->vertexCount * this->vertexCount);
        for (int i = 0; i < this->vertexCount * this->vertexCount; ++i)
        {
            if (i == start)
            {
                distances[i] = 0;
            }
            else
            {
                distances[i] = INT_MAX;
            }
            previous[i] = -1;
            queue.push(i, distances[i]);
        }
        while (!queue.empty())
        {
            int node = queue.pop();
            for (int i = 0; i < this->adjList[node].edgeCount; ++i)
            {
                int neighbor = this->adjList[node].edges[i];
                int altDist = distances[node] + this->adjList[node].weights[i];
                if (altDist < distances[neighbor])
                {
                    int altDist = distances[node] + this->adjList[node].weights[i];
                    if (altDist < distances[neighbor])
                    {
                        distances[neighbor] = altDist;
                        previous[neighbor] = node;
                        queue.push(neighbor, altDist);
                    }
                }
            }
        }
    }

    bool bfs(int source, int destination, int m)
    {
        bool* visited = new bool[m * m];
        for (int i = 0; i < m * m; i++) visited[i] = false;
        int n = m * m;
        BFSQueue q(n);
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
            for (int i = 0; i < adjList[u].edgeCount; i++)
            {
                int v = adjList[u].edges[i];
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

        // Get the console size
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int Scorewidth = csbi.srWindow.Right - (csbi.srWindow.Left / 2) + 1;
        int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        int newlines = (height - vertexCount * 2) / 2;
        // Print the newlines
        cout << string(newlines, '\n');

        cout << string((Scorewidth + 70) / 2, ' ') << "Nodes: " << score << endl;

        for (int i = 0; i < vertexCount; ++i)
        {
            // Calculate the number of spaces needed to center the grid
            int spaces = (width - vertexCount * 8) / 2;
            // Print the spaces
            cout << string(spaces, ' ');

            for (int j = 0; j < vertexCount; ++j)
            {
                int v = i * vertexCount + j;
                if (v == carPos)
                {
                    if (adjList[v].name == "<<+>>")
                    {
                        adjList[v].name = "\033[32m<<+>>\033[0m";
                        score += 1;
                    }
                    car(m); // Print the car
                }
                else
                {
                    cout << "\033[35m" << adjList[v].name << "\033[0m";
                }
                if (find(adjList[v].edges, adjList[v].edges + adjList[v].edgeCount, v + 1) != adjList[v].edges + adjList[v].edgeCount)
                {
                    cout << "\033[37m----\033[0m";
                }
                else
                {
                    cout << "    ";
                }
            }
            cout << endl;
            if (i < vertexCount - 1)
            {
                // Print the spaces
                cout << string(spaces, ' ');

                for (int j = 0; j < vertexCount; ++j)
                {
                    int v = i * vertexCount + j;
                    if (find(adjList[v].edges, adjList[v].edges + adjList[v].edgeCount, v + vertexCount) != adjList[v].edges + adjList[v].edgeCount)
                    {
                        cout << "\033[37m  |      \033[0m";
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

    ~AutoCarGraph()
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