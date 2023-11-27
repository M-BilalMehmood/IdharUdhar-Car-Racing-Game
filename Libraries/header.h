#include<iostream>
using namespace std;

//This temp code was just to check if the files are communicating with each other or not.

class Tree
{
private:
    int data;
    Tree* left;
    Tree* right;
public:
    Tree() : data(0), left(NULL), right(NULL) {};
    void print()
    {
        cout << "Testing tree" << endl;
        cout << "Data: " << data << endl;
        cout << "Left: " << &left << endl;
        cout << "Right: " << &right << endl;
    }
};