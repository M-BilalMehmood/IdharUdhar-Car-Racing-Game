#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include "Queue.h"
using namespace std;

struct PLayer_Data{
    string name;
    int score;
};


struct Binary_Tree_Node{
    PLayer_Data data;
    Binary_Tree_Node* left;
    Binary_Tree_Node* right;
};

class Binary_Tree{
private:
    Binary_Tree_Node* root;
    PLayer_Data top_of_the_leaderboard[5] = {};

    Binary_Tree_Node* Create_Node(PLayer_Data player) {
        Binary_Tree_Node* newNode = new Binary_Tree_Node();
        if (!newNode) {
            cout << "Memory error\n";
            return nullptr;
        }
        newNode->data = player;
        newNode->left = newNode->right = nullptr;
        return newNode;
    }

    Binary_Tree_Node* Insert_Node(Binary_Tree_Node* root, PLayer_Data player) {
        if (root == nullptr) {
            root = Create_Node(player);
        } else if (player.score < root->data.score) {
            root->left = Insert_Node(root->left, player);
        } else {
            root->right = Insert_Node(root->right, player);
        }
        return root;
    }
public:
    Binary_Tree() {
        root = nullptr;
    }

    void insert(PLayer_Data player) {
        root = Insert_Node(root, player);
    }

    void Populate_Tree(){
        // Binary_Tree* tree;
        ifstream I_File;
        I_File.open("Player Records.txt", ios::in);
        if (!I_File){
            cout << "Error opening file" << endl;
            return;
        }
        
        string line;
        string temp_name;
        size_t first_sapce;
        size_t second_space;
        int temp_score;

        while (getline(I_File, line)){
            first_sapce = line.find(" "); 
            second_space = line.find(" ", first_sapce + 1); //the space after the score entry in the file. 

            if (second_space == string::npos) {
                second_space = line.length(); //rest of the line is taken. 
            }
            temp_name = line.substr(0, line.find(" "));
            temp_score = stoi (line.substr(first_sapce + 1, second_space - first_sapce - 1));
            PLayer_Data temp_player = {temp_name, temp_score};
            this->insert(temp_player);
        }
    }

    void Breadth_First_Trversal(){
        if (root == nullptr){
            return;
        }
        Queue<Binary_Tree_Node*> q;
        q.Push(root);
        
        while (!q.Is_Empty()){
            Binary_Tree_Node* temp = q.Get_Front();
            q.Pop();

            for (int i=0; i<5; i++){
                if (temp->data.score > top_of_the_leaderboard[i].score){
                    for (int j=4; j>i; j--){
                        top_of_the_leaderboard[j] = top_of_the_leaderboard[j-1];
                    }
                    top_of_the_leaderboard[i] = temp->data; //since the data has name and score, it will be copied.
                    break;
                }
                else if (temp->data.score == top_of_the_leaderboard[i].score){
                    for (int j=4; j>i+1; j--){
                        top_of_the_leaderboard[j] = top_of_the_leaderboard[j-1];
                    }
                    top_of_the_leaderboard[i+1] = temp->data; //since the data has name and score, it will be copied.
                    break;
                }
            }

            if (temp->left != nullptr){
                q.Push(temp->left);
            }
            if (temp->right != nullptr){
                q.Push(temp->right);
            }
        }
    }

    void Print_LeaderBoard(){
        Breadth_First_Trversal(); //by calling the breadth first traversal, the leaderboard will be updated.
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        int newlines = (height - 18) / 2;
        // Print the newlines
        cout << string(newlines, '\n');
        // Print the leaderboard
        cout << string(width / 2 - 5, ' ') << "\033[36mLEADERBOARD\033[0m" << endl;
        for (int i=0; i<5;i++){

            cout << string(width / 2 - 10, ' ') << "\033[34mName: \033[35m" << top_of_the_leaderboard[i].name << "\033[34m Score: \033[35m" << top_of_the_leaderboard[i].score << "\033[0m" << endl;
        }
    }
};

