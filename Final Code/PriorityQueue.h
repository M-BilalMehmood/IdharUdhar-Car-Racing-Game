#pragma once
#include <iostream>
using namespace std;

class PriorityQueue
{
    int* arr;
    int size;
public:
    PriorityQueue(int size) : size(size)
    {
        arr = new int[size];
        for (int i = 0; i < size; ++i)
        {
            arr[i] = INT_MAX;
        }
    }
    void push(int node, int priority)
    {
        arr[node] = priority;
    }
    int pop()
    {
        int minNode = -1;
        for (int i = 0; i < size; ++i) 
        {
            if (arr[i] != INT_MAX && (minNode == -1 || arr[i] < arr[minNode]))
            {
                minNode = i;
            }
        }
        if (minNode != -1)
        {
            arr[minNode] = INT_MAX;
        }
        return minNode;
    }
    bool empty()
    {
        for (int i = 0; i < size; ++i)
        {
            if (arr[i] != INT_MAX)
            {
                return false;
            }
        }
        return true;
    }
};