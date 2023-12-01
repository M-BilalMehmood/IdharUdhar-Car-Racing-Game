#include <iostream>
#include <ctime>
#include "../Libraries/Objects_Manager.h"
#include "../Libraries/Scoring_List.h"
#include "../Libraries/Queue.h"

using namespace std;

Collected_Items* Collected_Items::instance = nullptr; //this should be added outside the class definition so that it can stay accurate to its pattern.

void affan_score_implementation() {
    Object_Factory* factory = new Object_Factory();

    for (int i=0; i<10; i++) {      
        srand(time(0));
        int choice = (rand() % 3+1);

        Object* object = factory->Create_Object(choice);
        cout << object->Create_Object() << endl;
        cout << object->Object_Value() << endl;
        //on creating object we already get the name of the object and value is gotten the traditional way.
        Collected_Items::get_instance()->add_item(object->Create_Object(), object->Object_Value());
        cout<<"Score: "<<Collected_Items::get_instance()->get_total_score()<<endl;

        //clear screen then pause before next iteration
        system("pause");
        system("cls");
    }

    cout<<"Printing the items in the list"<<endl;
}