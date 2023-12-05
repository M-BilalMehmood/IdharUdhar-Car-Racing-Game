#pragma once
#include <iostream>
using namespace std;

//templatized node class for queue
template <typename T> 
class Node {
public:
    T data;
    Node<T>* next;

    Node(T data) : data(data), next(nullptr) {}
};

template <typename T> 
class Queue {
private:
    Node<T>* front;
    Node<T>* rear;

public:
    Queue() : front(nullptr),rear(nullptr) {} 

    void Push(T data) {
        Node<T>* temp = new Node<T>(data);
        if (front == nullptr) {
            front = rear = temp;
        }
        else {
            rear->next = temp;
            rear = temp;
        }
    }

    void Pop() {
        if (front == nullptr) {
            cout << "Queue is empty!\n";
            return;
        }
        Node<T>* temp = front;
        front = front->next;
        delete temp;
    }

    T Get_Front() {
        if (front == nullptr) {
            cout << "Queue is empty!\n";
            return T();
        }
        return front->data;
    }

    bool Is_Empty() const { 
        return front == nullptr; 
    }

    ~Queue() {
        while (front != nullptr) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
    }
};