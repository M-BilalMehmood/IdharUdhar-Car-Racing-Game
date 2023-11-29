#pragma once
#include <iostream>
#include <ctime>
using namespace std;

//templatized node class for queue
template <typename T> class Node {
public:
    T data;
    Node<T>* next;

    Node(T data) : data(data), next(nullptr) {}
};


//using factory design pattern for creating obstacles.
class Object {
public:
	//pure virtual created => imperitive for derived classes to implement this function.
	virtual void Create_Object() = 0;
};

class Obstacle : public Object {
public:
	void Create_Object() override {
		cout << "Obstacle created!" << endl;
	}
};

class Coin : public Object {
public:
	void Create_Object() override {
		cout << "Coin created!" << endl;
	}
};

class Multiplier : public Object {
public:
	void Create_Object() override {
		cout << "Multiplier created!" << endl;
	}
};

//this is the factory class => client will send message of creation here and the factory will create the object.
class Object_Factory {
public:
    //Game_Flow::get_NumberOfNodes() => returns the number of nodes in the grid 
    //----> this is from which the number of objects can be formulated. 
    //for now, we will suppose Node_Num=10 

	/*Object* Create_Object(int choice) {
		switch (choice) {
		case 1:
			return new Obstacle();
		case 2:
			return new Coin();
		case 3:
			return new Multiplier();
		default:
			return nullptr;
		}
	}*/

    //randomly generate an object from the factory

    Object* Create_Object(int choice) {
        switch (choice) {
		case 1:
			return new Obstacle();
		case 2:
			return new Coin();
		case 3:
			return new Multiplier();
		default:
			return nullptr;
		}
	}
};


template <typename T> 
class Object_Queue {
private:
    
    Node<T>* front;
    Node<T>* rear;

public:
    Object_Queue() : front(nullptr),rear(nullptr) {} 

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
            std::cout << "Queue is empty!\n";
            return;
        }
        Node<T>* temp = front;
        front = front->next;
        delete temp;
    }

    T Get_Front() {
        if (front == nullptr) {
            std::cout << "Queue is empty!\n";
            return T();
        }
        return front->data;
    }

    bool Is_Empty() const { return front == nullptr; }

    ~Object_Queue() {
        while (front != nullptr) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

