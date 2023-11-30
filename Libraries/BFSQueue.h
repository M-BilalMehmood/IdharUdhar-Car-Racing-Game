#pragma once
#include<iostream>
using namespace std;

struct Node
{
    string name;
    int vertex;
    int* edges;
    int* weights;
    int edgeCount;
};

class Queue 
{
    int* arr;
    int capacity;
    int front;
    int size;

public:
    Queue(int capacity) : capacity(capacity), front(0), size(0) 
    {
        arr = new int[capacity];
    }

    ~Queue() 
    {
        delete[] arr;
    }

    void push(int x) 
    {
        if (size == capacity) throw runtime_error("Queue is full");
        int rear = (front + size) % capacity;
        arr[rear] = x;
        size++;
    }

    void pop() 
    {
        if (size == 0) throw runtime_error("Queue is empty");
        front = (front + 1) % capacity;
        size--;
    }

    int peek() 
    {
        if (size == 0) throw runtime_error("Queue is empty");
        return arr[front];
    }

    bool empty() 
    {
        return size == 0;
    }
};