#include <iostream>

#include <ctime>

//#include"/Git Dev/DS-Project/DS-Project/Libraries/header.h"
//#include"/Git Dev/DS-Project/Libraries/header.h"
#include "../Libraries/AutomaticCar_GameManager.h"
#include "../Libraries/Game_Manager.h"
#include <Windows.h>

#include "../Source/affan_feature_implemtation.cpp"

//MUSIC COMMENT #1
// #pragma comment(lib, "winmm.lib") 



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

    const char* options[] = { "Start", "Score Board", "Store", "Exit!" };
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



int main()
{   
    // //MUSIC COMMENT #2
    // // PlaySound(TEXT("LOBBY.wav"), NULL, SND_ASYNC | SND_LOOP);
    // int selectedOption = 0;
    // int selectedOption1 = 0;
    // int menukey;
    
    // while (true)
    // {
    //     system("cls");
    //     printMenu(selectedOption);

    //     int key = _getch(); // Capture the arrow key input
    //     if (key == 72) selectedOption = (selectedOption - 1 + 4) % 4; // Up arrow key
    //     else if (key == 80) selectedOption = (selectedOption + 1) % 4; // Down arrow key
    //     else if (key == 13) break; // Enter key
    // }

    // // Now selectedOption contains the index of the selected menu option
    // // You can use a switch statement to handle each option
    // switch (selectedOption)
    // {
    // case 0: // Start New Game
    //     while (true)
    //     {
    //         system("cls");
    //         printStartNewGame(selectedOption1);
    //         menukey = _getch(); // Capture the arrow key input
    //         if (menukey == 72) selectedOption1 = (selectedOption1 - 1 + 2) % 2; // Up arrow key
    //         else if (menukey == 80) selectedOption1 = (selectedOption1 + 1) % 2; // Down arrow key
    //         else if (menukey == 13) break; // Enter key

    //     }
    //     if (selectedOption1 == 0)
    //     {
    //         cout << "Enter the size of the grid: ";
    //         int m;
    //         cin >> m;
    //         Graph g(m);
    //         g.moveCar(m);
    //         break;
    //     }
    //     else if (selectedOption1 == 1)
    //     {
    //         cout << "Enter the size of the grid: ";
    //         int m;
    //         cin >> m;
    //         AutoCarGraph g(m);
    //         g.moveCar(m);
    //         break;
    //     }
    //     // Handle the selected option in the "Start New Game" menu

    //     break;
    // case 1: // Leaderboard
    //     // ...
    //     system("cls");
    //     cout << "Leaderboard" << endl;
    //     break;
    // case 2: // Shop
    //     // ...
    //     break;
    // }

    // return 0;


    // helper_function();
    // Create_And_Display_Leaderboard("Player Records.txt");

    Binary_Tree tree;
    tree.Populate_Tree();
    tree.Print_LeaderBoard();
}

// All rights reserved by the Affan Hameed and Bilal Mehmood.