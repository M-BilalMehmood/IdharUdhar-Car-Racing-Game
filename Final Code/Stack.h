#pragma once
#include <iostream>
using namespace std;

class Stack
{
    struct Node
    {
        int data;
        Node* next;
    };

    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    void push(int data)
    {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = top;
        top = newNode;
    }

    void pop()
    {
        if (!isEmpty())
        {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    int peek()
    {
        if (!isEmpty())
        {
            return top->data;
        }
        return -1; // Return -1 if the stack is empty
    }

    bool isEmpty()
    {
        return top == nullptr;
    }
};