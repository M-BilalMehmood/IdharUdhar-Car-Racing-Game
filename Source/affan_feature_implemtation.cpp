#include <iostream>
#include <ctime>
#include "../Libraries/Objects_Manager.h"
#include "../Libraries/Scoring_List.h"
#include "../Libraries/Templatized_Queue.h"
#include "../Libraries/LeaderBoard_Binary_Tree.h"

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

    cout << "Total Score: " << Collected_Items::get_instance()->get_total_score() << endl;
    cout<<"coins collected: "<<Collected_Items::get_instance()->get_coin_count()<<endl;
    cout<<"multiplier collected : "<<Collected_Items::get_instance()->get_multiplier_count()<<endl;
    cout<<"obstacles hit : "<<Collected_Items::get_instance()->get_obstacle_count()<<endl;

    system("pause");
    system("cls");

    int choice_1;
    string name;
    cout<<"How would you like to continue?"<<endl;
    cout<<"[1] New Player"<<endl;
    cout<<"[2] Continue"<<endl;
    cout<<"[3] Exit"<<endl;
    cin>>choice_1;

    switch(choice_1){
        case 1:
            cout<<"Enter player name :";
            cin>>name;
            Collected_Items::get_instance()->new_player_record(name);
            break;
        case 2:
            cout<<"Player Name : ";
            cin>>name;
            Collected_Items::get_instance()->update_player_record(name);
            break;
        case 3:
            cout<<"Exiting..."<<endl;
            exit(0);
            break;
        default:
            cout<<"Invalid Input"<<endl;
            break;
    }

    
}

