#include<iostream>

#include <ctime>

//#include"/Git Dev/DS-Project/DS-Project/Libraries/header.h"
//#include"/Git Dev/DS-Project/Libraries/header.h"
#include "../Libraries/AutomaticCar_GameManager.h"
#include "../Libraries/Game_Manager.h"
#include <Windows.h>

#pragma comment(lib, "winmm.lib")

//#include"header.h"
using namespace std;

// This temp code was just to check if the files are communicating with each other or not.

void PathNodesPrint()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    int newlines = (height - 18) / 2;
    // Print the newlines
    cout << string(newlines, '\n');

    cout << string((width - 81) / 2, ' ') << " \033[4m\033[35m\\o=o>\033[0m" << endl;

    cout << "\a";

    cout << string((width - 81) / 2, ' ') << "\033[34m ________   _______    _______  _______     \033[36m  _______    _______  _______   _______" << endl;
    cout << string((width - 81) / 2, ' ') << "\033[34m/  ______\\  |  __  \\   |_   _|  | ____ \\ \033[36m     |  __  \\   |_   _|  | ____ \\  |  ___|" << endl;
    cout << string((width - 81) / 2, ' ') << "\033[34m| |         | |__)  |    | |    | |   \\ |  \033[36m   | |__)  |    | |    | |   \\ | | |___" << endl;
    cout << string((width - 81) / 2, ' ') << "\033[34m| |   ____  |  __  /     | |    | |   | |   \033[36m  |  __  /     | |    | |   | | |  ___|" << endl;
    cout << string((width - 81) / 2, ' ') << "\033[34m| |  /__  | | |  \\ \\     | |    | |   | | \033[36m    | |  \\ \\     | |    | |   | | | |" << endl;
    cout << string((width - 81) / 2, ' ') << "\033[34m| |_____| | | |   \\ \\   _| |_   | |___/ | \033[36m    | |   \\ \\   _| |_   | |___/ | | |___" << endl;
    cout << string((width - 81) / 2, ' ') << "\033[34m\\________/  |_|    \\_\\ |_____|  |______/ \033[36m     |_|    \\_\\ |_____|  |______/  |_____|" << endl;

    cout << "\033[0m" << endl;
}

void printMenu(int selectedOption)
{

    const char* options[] = { "Start", "Score Board", "Exit!" };
    const int numOptions = sizeof(options) / sizeof(options[0]);

    // Get the console size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // Print the game name in the center
    PathNodesPrint(); cout << "\n\n";

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

void printStartNewGame(int selectedOption)
{
    const char* options[] = { "Ride Your Way", "Automatic" };
    const int numOptions = sizeof(options) / sizeof(options[0]);

    // Get the console size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // Print the game name in the center
    PathNodesPrint(); cout << endl << endl;

    cout << string((width - 7) / 2, ' ') << "\033[34mSELECT MODE\033[0m" << endl;

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

void GridSize(int selectOption)
{
    const char* options[] = { "10 x 10", "15 x 15", "20 x 20" };
    const int numOptions = sizeof(options) / sizeof(options[0]);

    // Get the console size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // Print the game name in the center
    PathNodesPrint(); cout << "\n\n";
    cout << string((width - 12) / 2, ' ') << "\033[34mSELECT GRID SIZE\033[0m" << endl;

    // Print the options in the center
    for (int i = 0; i < numOptions; ++i)
    {
        if (i == selectOption)
        {
            cout << string((width - strlen(options[i])) / 2, ' ') << "\033[33m> " << options[i] << "\n\033[0m";
        }
        else
        {
            cout << string((width - strlen(options[i])) / 2, ' ') << "  " << options[i] << "\n";
        }
    }
}

int main()
{
    PlaySound(TEXT("LOBBY.wav"), NULL, SND_ASYNC | SND_LOOP);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    int selectedOption = 0;
    int selectedOption1 = 0;
    int selectOption_Grid = 0;
    int menukey;
    while (true)
    {
        system("cls");
        printMenu(selectedOption);

        int key = _getch(); // Capture the arrow key input
        if (key == 72) selectedOption = (selectedOption - 1 + 3) % 3; // Up arrow key
        else if (key == 80) selectedOption = (selectedOption + 1) % 3; // Down arrow key
        else if (key == 13) break; // Enter key
    }

    // Now selectedOption contains the index of the selected menu option
    // You can use a switch statement to handle each option
    switch (selectedOption)
    {
    case 0: // Start New Game
        while (true)
        {
            system("cls");
            printStartNewGame(selectedOption1);
            menukey = _getch(); // Capture the arrow key input
            if (menukey == 72) selectedOption1 = (selectedOption1 - 1 + 2) % 2; // Up arrow key
            else if (menukey == 80) selectedOption1 = (selectedOption1 + 1) % 2; // Down arrow key
            else if (menukey == 13) break; // Enter key

        }
        if (selectedOption1 == 0)
        {
            while (true)
            {
                system("cls");
                GridSize(selectOption_Grid);
                menukey = _getch(); // Capture the arrow key input
                if (menukey == 72) selectOption_Grid = (selectOption_Grid - 1 + 3) % 3; // Up arrow key
                else if (menukey == 80) selectOption_Grid = (selectOption_Grid + 1) % 3; // Down arrow key
                else if (menukey == 13) break; // Enter key
            }
            if (selectOption_Grid == 0)
            {
                Graph g(10);
                g.moveCar(10);
            }
            else if (selectOption_Grid == 1)
            {
                Graph g(15);
                g.moveCar(15);
            }
            else if (selectOption_Grid == 2)
            {
                Graph g(20);
                g.moveCar(20);
            }
            break;
        }
        else if (selectedOption1 == 1)
        {
            while (true)
            {
                system("cls");
                GridSize(selectOption_Grid);
                menukey = _getch(); // Capture the arrow key input
                if (menukey == 72) selectOption_Grid = (selectOption_Grid - 1 + 3) % 3; // Up arrow key
                else if (menukey == 80) selectOption_Grid = (selectOption_Grid + 1) % 3; // Down arrow key
                else if (menukey == 13) break; // Enter key
            }
            if (selectOption_Grid == 0)
            {
                AutoCarGraph g(10);
                g.moveCar(10);
            }
            else if (selectOption_Grid == 1)
            {
                AutoCarGraph g(15);
                g.moveCar(15);
            }
            else if (selectOption_Grid == 2)
            {
                AutoCarGraph g(20);
                g.moveCar(20);
            }
            break;
        }
        // Handle the selected option in the "Start New Game" menu

        break;
    case 1: // Leaderboard
        // ...
        system("cls");
        cout << "Leaderboard" << endl;
        break;
    case 2: // Shop
        // ...
        system("cls");
        int newlines = height / 2;
        cout << string(newlines, '\n');
        cout << string((width - 22) / 2, ' ') << "\033[35mThank you for playing!\033[0m" << endl;
        cout << string(newlines, '\n');
        exit(0);
        break;
    }

    return 0;
}

// All rights reserved by the Affan Hameed and Bilal Mehmood.