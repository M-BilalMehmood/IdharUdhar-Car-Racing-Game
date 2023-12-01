#pragma once
#include <iostream>
#include <ctime>
using namespace std;

//using factory design pattern for creating obstacles.
class Object {
public:
	//pure virtual created => imperitive for derived classes to implement this function.
	string object_name;
	int object_value;
	virtual string Create_Object() = 0;
	virtual int Object_Value() =0;
};

class Obstacle : public Object {
public:
	Obstacle() {
		object_name = "\033[31m/===\\\033[0m";
		object_value = -1;
	}
	string Create_Object() override {
		return object_name;
	}
	int Object_Value() override {
		return object_value;
	}
};

class Coin : public Object {
public:
	Coin() {
		object_name = "\033[32m>>$<<\033[0m";
		object_value = 3;
	}
	string Create_Object() override {
		return object_name;
	}
	int Object_Value() override {
		return object_value;
	}
};

class Multiplier : public Object {
public:
	Multiplier() {
		object_name = "\033[36m<{~}>\033[0m";
		object_value = 2;
	}
	string Create_Object() override {
		return object_name;
	}
	int Object_Value() override {
		return object_value;
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

