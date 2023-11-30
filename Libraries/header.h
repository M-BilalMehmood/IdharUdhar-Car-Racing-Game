#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include "/Git Dev/DS-Project/DS-Project/Libraries/Queue.h"
using namespace std;

struct Node
{
    int vertex;
    int* edges;
    int* weights;
    int edgeCount;
};

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
            adjList[i].vertex = i;
            adjList[i].edges = new int[V * V];
            adjList[i].weights = new int[V * V];
            adjList[i].edgeCount = 0;
        }
    }

    void addEdge(int x1, int y1, int x2, int y2, int weight)
    {
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
        print(n);
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