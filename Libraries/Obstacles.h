#pragma once
#include <iostream>
#include <ctime>
using namespace std;


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

