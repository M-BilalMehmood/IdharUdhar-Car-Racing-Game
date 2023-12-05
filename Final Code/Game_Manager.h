#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include "Objects_Manager.h"
#include "Queue.h"
#include "Scoring_List.h"
#include "BFSQueue.h"
//#include "/Git Dev/DS-Project/DS-Project/Libraries/Queue.h"
using namespace std;
// #pragma comment(lib, "winmm.lib")

void PathNodesPrint();
int main();

struct GNode
{
    string name;
    int vertex;
    int* edges;
    int* weights;
    int edgeCount;
};


class Graph
{
private:
    GNode* adjList;
    Queue<Object*> objectQueue;
    Object* obj;
    string username; 
    int user_type; 
    int vertexCount;
    int score = 0;
    int objectCount = 0;

public:
    Graph(int V) : vertexCount(V)
    {
        adjList = new GNode[V * V];
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

    void addObject(Object* obj) 
    {
        if (objectCount >= vertexCount * vertexCount - 2) 
        {
            // The grid is full, so don't try to add more objects
            return;
        }

        int pos;
        do 
        {
            pos = rand() % (vertexCount * vertexCount);
        } 
        while (pos == 0 || pos == vertexCount * vertexCount - 1 || adjList[pos].name != "<<+>>");

        objectQueue.Push(obj);
        adjList[pos].name = obj->Create_Object();
        //dequeue the object from the queue
        objectQueue.Pop(); //added this line
        objectCount++;
    }

    void makeGrid(int n)
    {
        srand(time(0));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (rand() % 10 < 6.5) { // 65% chance to add a horizontal edge
                    if (j < n - 1) { // Don't add a horizontal edge for the last column
                        addEdge(i, j, i, j + 1, 10); //weight = 10
                    }
                }
                if (rand() % 10 < 6.5) { // 65% chance to add a vertical edge
                    if (i < n - 1) { // Don't add a vertical edge for the last row
                        addEdge(i, j, i + 1, j, 10); // weight = 10
                    }
                }
            }
        }
        Object_Factory factory;
        int numObjects = n * n / 2; // Calculate the number of objects
        for (int i = 0; i < numObjects; ++i) {
            addObject(factory.Create_Object(rand() % 3 + 1)); // Add a random object to the grid
        }
        //print(n);
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

    void SelectCar(int selectedOption)
    {
        const char* options[] = { "\\o=o>", "Lo=o>", "Co=o>" };
        const int numOptions = sizeof(options) / sizeof(options[0]);

        // Get the console size
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        // Print the game name in the center
        PathNodesPrint(); cout << "\n\n";

        cout << string((width - 10) / 2, ' ') << "\033[34mSelect Your Car\033[0m" << endl;

        // Print the options in the center
        for (int i = 0; i < numOptions; ++i)
        {
            if (i == selectedOption)
            {
                cout << string((width - strlen(options[i])) / 2, ' ') << "\033[33m> " << options[i] << "\n\033[0m";
            }
            else
            {
                cout << string((width - strlen(options[i])) / 2, ' ') << "  " << options[i] << "\n";
            }
        }
    }

    void moveCar(int m, string username, int user_type)
    {
        this->username = username;
        this->user_type = user_type;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int Scorewidth = csbi.srWindow.Right - (csbi.srWindow.Left / 2) + 1;
        int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        int newlines = (height - vertexCount * 2) / 2;
        // Print the newlines
        cout << string(newlines, '\n');
        int selectCar = 0;
        int key, n;

        // PlaySound(TEXT("WhileGamming.wav"), NULL, SND_ASYNC | SND_LOOP);
        while (true)
        {
            system("cls");
            SelectCar(selectCar);
            key = _getch(); // Capture the arrow key input
            if (key == 72) selectCar = (selectCar - 1 + 3) % 3; // Up arrow key
            else if (key == 80) selectCar = (selectCar + 1) % 3; // Down arrow key
            else if (key == 13) break; // Enter key
        }
        if (selectCar == 0) { n = 1; }
        if (selectCar == 1) { n = 2; }
        if (selectCar == 2) { n = 3; }
        system("cls");
        bool isPaused = false;
        while (true)
        {
            if (!isPaused)
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
                        if (key == 27) // 27 is the ASCII value of the ESC key
                        {
                            try {
                                if (isPaused)
                                {
                                    cout << string((Scorewidth - 13) / 2, ' ') << "Game resumed!" << endl;
                                }
                                else
                                {
                                    cout << endl << string((Scorewidth - 130) / 2, ' ') << string((50) / 2, ' ') << "\033[33mESC = Resume" << string((50) / 2, ' ') << "\033[34mGame paused!" << string((49) / 2, ' ') << "\033[31mR = Main Menu\033[0m" << endl;
                                    int key = _getch();
                                    if (key == 27)
                                    {
                                        isPaused = !isPaused;
                                    }
                                    else if (key == 114)
                                    {
                                        system("cls");
                                        main();
                                    }
                                }
                            }
                            catch (length_error& e) {
                                Scorewidth /= 2; // Decrease the size of Scorewidth
                                if (isPaused)
                                {
                                    cout << string((Scorewidth - 13) / 2, ' ') << "Game resumed!" << endl;
                                }
                                else
                                {
                                    cout << endl << string((Scorewidth - 20) / 2, ' ') << string((25) / 2, ' ') << "\033[33mESC = Resume" << string((25) / 2, ' ') << "\033[34mGame paused!" << string((24) / 2, ' ') << "\033[31mR = Main Menu\033[0m" << endl;
                                }
                                int key = _getch();
                                if (key == 27)
                                {
                                    isPaused = !isPaused;
                                }
                                else if (key == 114)
                                {
                                    system("cls");
                                    main();
                                }
                            }
                            isPaused = !isPaused;
                        }
                        else if (!isPaused)
                        {
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
                                printYouWon();
                                system("cls");
                                DisplayScore();
                                break;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }

    bool bfs(Graph& g, int source, int destination, int m) 
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

    void DisplayScore()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        int newlines = (height - vertexCount * 2) / 2;
        // Print the newlines
        cout << string(newlines, '\n');

        
        cout << string((width - 19) / 2, ' ') << "Your Score is: " << Collected_Items::get_instance()->get_total_score() << endl;
        cout << string((width - 19) / 2, ' ') << "Press Enter to return to the main menu" << endl;
        int key = _getch();
        if (key == 13)
        {
            system("cls");
            main();
        }
        else
        {
            cout << string((width - 19) / 2, ' ') << "\033[31mWrong Input, Returning to Main Menu\033[0m" << endl;
            Sleep(2000);
            system("cls");
            main();
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

        cout << string((Scorewidth + 70) / 2, ' ') << "Score: " << Collected_Items::get_instance()->get_total_score() << endl;

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
                    bool isRemoved = false;

                    if (adjList[v].name == "\033[32m>>$<<\033[0m")
                    {
                        adjList[v].name = "<<+>>";
                        // score += 10;
                        Collected_Items::get_instance()->add_item(adjList[v].name, 3);
                    }
                    else if (adjList[v].name == "\033[36m<{~}>\033[0m")
                    {
                        // cout<<"working"<<endl;                        
                        adjList[v].name = "<<+>>";
                        // score *= 2;
                        Collected_Items::get_instance()->add_item("\033[36m<{~}>\033[0m", 2);
                    }
                    else if (adjList[v].name == "\033[31m/===\\\033[0m")
                    {
                        // score -= 10;
                        if (isRemoved == false)
                        {
                            Collected_Items::get_instance()->add_item(adjList[v].name, -1);
                            isRemoved = true;
                        }
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
        // Collected_Items::get_instance()->print_items();
        
    }

    void printYouWon()
    {
        // PlaySound(TEXT("WIN.wav"), NULL, SND_ASYNC | SND_LOOP);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        int newlines = (height - 18) / 2;
        // Print the newlines

        for (int i = 0; i < 2; i++)
        {
            // Print "YOU WON"
            system("cls");
            //cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl ;
            cout << string(newlines, '\n');
            cout << string((width - 81) / 2, ' ') << "\033[34m___        ___   ________    __      __      __        __    ________    __       __ " << endl;
            cout << string((width - 81) / 2, ' ') << "\\  \\      /  /  /   __   \\  |  |    |  |    |  |      |  |  /   __   \\  |  \\     |  |" << endl;
            cout << string((width - 81) / 2, ' ') << " \\  \\    /  /  |   /  \\   | |  |    |  |    |  |      |  | |   /  \\   | |   \\    |  |" << endl;
            cout << string((width - 81) / 2, ' ') << "  \\  \\__/  /   |  |    |  | |  |    |  |    |  |      |  | |  |    |  | |    \\   |  |" << endl;
            cout << string((width - 81) / 2, ' ') << "   \\      /    |  |    |  | |  |    |  |    |  |  __  |  | |  |    |  | |     \\__|  |" << endl;
            cout << string((width - 81) / 2, ' ') << "    \\    /     |  |    |  | |  |    |  |    |  |_/  \\_|  | |  |    |  | |           |" << endl;
            cout << string((width - 81) / 2, ' ') << "     |  |      |  |    |  | |  |    |  |    |            | |  |    |  | |   __      |" << endl;
            cout << string((width - 81) / 2, ' ') << "     |  |      |  |    |  | |  |    |  |    |     __     | |  |    |  | |  |  \\     |" << endl;
            cout << string((width - 81) / 2, ' ') << "     |  |      |  |    |  | |  |    |  |    |    /  \\    | |  |    |  | |  |   \\    |" << endl;
            cout << string((width - 81) / 2, ' ') << "     |  |      |   \\__/   | |   \\__/   |    |   /    \\   | |   \\__/   | |  |    \\   |" << endl;
            cout << string((width - 81) / 2, ' ') << "     |__|       \\________/   \\________/     |__/      \\__|  \\________/  |__|     \\__|" << endl;

            Sleep(500);
            system("cls");
            cout << string(newlines, '\n');
            cout << string((width - 81) / 2, ' ') << "\033[36m___        ___   ________    __      __      __        __    ________    __       __ " << endl;
            cout << string((width - 81) / 2, ' ') << "\\  \\      /  /  /   __   \\  |  |    |  |    |  |      |  |  /   __   \\  |  \\     |  |" << endl;
            cout << string((width - 81) / 2, ' ') << " \\  \\    /  /  |   /  \\   | |  |    |  |    |  |      |  | |   /  \\   | |   \\    |  |" << endl;
            cout << string((width - 81) / 2, ' ') << "  \\  \\__/  /   |  |    |  | |  |    |  |    |  |      |  | |  |    |  | |    \\   |  |" << endl;
            cout << string((width - 81) / 2, ' ') << "   \\      /    |  |    |  | |  |    |  |    |  |  __  |  | |  |    |  | |     \\__|  |" << endl;
            cout << string((width - 81) / 2, ' ') << "    \\    /     |  |    |  | |  |    |  |    |  |_/  \\_|  | |  |    |  | |           |" << endl;
            cout << string((width - 81) / 2, ' ') << "     |  |      |  |    |  | |  |    |  |    |            | |  |    |  | |   __      |" << endl;
            cout << string((width - 81) / 2, ' ') << "     |  |      |  |    |  | |  |    |  |    |     __     | |  |    |  | |  |  \\     |" << endl;
            cout << string((width - 81) / 2, ' ') << "     |  |      |  |    |  | |  |    |  |    |    /  \\    | |  |    |  | |  |   \\    |" << endl;
            cout << string((width - 81) / 2, ' ') << "     |  |      |   \\__/   | |   \\__/   |    |   /    \\   | |   \\__/   | |  |    \\   |" << endl;
            cout << string((width - 81) / 2, ' ') << "     |__|       \\________/   \\________/     |__/      \\__|  \\________/  |__|     \\__|" << endl;

            Sleep(500);
            system("cls");
            cout << string(newlines, '\n');
            cout << string((width - 81) / 2, ' ') << "\033[35m___        ___   ________    __      __      __        __    ________    __       __ " << endl;
            cout << string((width - 81) / 2, ' ') << "\\  \\      /  /  /   __   \\  |  |    |  |    |  |      |  |  /   __   \\  |  \\     |  |" << endl;
            cout << string((width - 81) / 2, ' ') << " \\  \\    /  /  |   /  \\   | |  |    |  |    |  |      |  | |   /  \\   | |   \\    |  |" << endl;
            cout << string((width - 81) / 2, ' ') << "  \\  \\__/  /   |  |    |  | |  |    |  |    |  |      |  | |  |    |  | |    \\   |  |" << endl;
            cout << string((width - 81) / 2, ' ') << "   \\      /    |  |    |  | |  |    |  |    |  |  __  |  | |  |    |  | |     \\__|  |" << endl;
            cout << string((width - 81) / 2, ' ') << "    \\    /     |  |    |  | |  |    |  |    |  |_/  \\_|  | |  |    |  | |           |" << endl;
            cout << string((width - 81) / 2, ' ') << "     |  |      |  |    |  | |  |    |  |    |            | |  |    |  | |   __      |" << endl;
            cout << string((width - 81) / 2, ' ') << "     |  |      |  |    |  | |  |    |  |    |     __     | |  |    |  | |  |  \\     |" << endl;
            cout << string((width - 81) / 2, ' ') << "     |  |      |  |    |  | |  |    |  |    |    /  \\    | |  |    |  | |  |   \\    |" << endl;
            cout << string((width - 81) / 2, ' ') << "     |  |      |   \\__/   | |   \\__/   |    |   /    \\   | |   \\__/   | |  |    \\   |" << endl;
            cout << string((width - 81) / 2, ' ') << "     |__|       \\________/   \\________/     |__/      \\__|  \\________/  |__|     \\__|" << endl;

            cout << "\033[0m" << endl;
            Sleep(500);
        }
        if (user_type==1){
            Collected_Items::get_instance()->update_player_record(username);
        }
        else if (user_type==0){
            Collected_Items::get_instance()->new_player_record(username);
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