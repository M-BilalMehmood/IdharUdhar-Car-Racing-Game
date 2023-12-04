#include <iostream>
#include <ctime>
#include "../Libraries/Objects_Manager.h"
#include "../Libraries/Scoring_List.h"
#include "../Libraries/Templatized_Queue.h"

using namespace std;

Collected_Items* Collected_Items::instance = nullptr; //this should be added outside the class definition so that it can stay accurate to its pattern.

void helper_function(){
    srand(time(0));
    Queue<Object*> object_queue;
    Object_Factory object_factory;

    for (int i=0; i<10; i++) {
        int choice = (rand() % 3+1);
        Object* object = object_factory.Create_Object(choice);
        object_queue.Push(object);
    }

    while (!object_queue.Is_Empty()) {
        Object* object = object_queue.Get_Front();
        cout << object->Create_Object() << endl;
        object_queue.Pop();
        Collected_Items::get_instance()->add_item(object->object_name, object->object_value);
    }

}