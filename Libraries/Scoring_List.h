#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class Item {
public:
    string type;
    int value;
    Item* next;
    Item* prev;
    Item(string Item_Type, int Score_Value): type(Item_Type), value(Score_Value), next(nullptr), prev(nullptr) {}
};

class Collected_Items {
private:
    Item* head;
	Item* tail;

    static Collected_Items* instance;
    //private contructor:
    Collected_Items() : head(nullptr), tail(nullptr) {}
public:
    static Collected_Items* get_instance() {
        if (instance == nullptr) {
            instance = new Collected_Items();
        }
        return instance;
    }

    //when called, the function will create a new node and add it to the end of the list.
    void add_item(string Item_Type, int Score_Value) {
        Item* new_item = new Item(Item_Type, Score_Value);
        if (head == nullptr) {
            head = tail = new_item;
        } else {
            tail->next = new_item;
            new_item->prev = tail;
            tail = new_item;
        }
        cout<<"Item added"<<endl;
    }

    void remove_item(bool remove_from_head) {
        if (remove_from_head && head != nullptr) {
            Item* nextItem = head->next;
            delete head;
            head = nextItem;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            else {
                tail = nullptr;
            }
        }
        else if (!remove_from_head && tail != nullptr) {
            Item* prevItem = tail->prev;
            delete tail;
            tail = prevItem;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
            else {
                head = nullptr;
            }
        }
    }

    int get_coin_count() {
        int coin_count = 0;
        Item* temp = head;
        while (temp != nullptr) {
            if (temp->type == "\033[32m>>$<<\033[0m") {
                coin_count++;
            }
            temp = temp->next;
        }
        return coin_count;
    }

    int get_multiplier_count() {
        int multiplier_count = 0;
        Item* temp = head;
        while (temp != nullptr) {
            if (temp->type == "\033[36m<{~}>\033[0m") {
                multiplier_count++;
            }
            temp = temp->next;
        }
        return multiplier_count;
    }

    int get_obstacle_count() {
        int obstacle_count = 0;
        Item* temp = head;
        while (temp != nullptr) {
            if (temp->type == "\033[31m/===\\\033[0m") {
                obstacle_count++;
            }
            temp = temp->next;
        }
        return obstacle_count;
    }

    int get_total_score() {
        int total_score = 0;
        Item* temp = head;
        while (temp != nullptr) {
            total_score += temp->value;
            temp = temp->next;
        }
        return total_score;
    }


    //to be used in case player selects the "NEW PLAYER" opetion then at the end of the game, the player's record will be added to the file 
    //via THIS particualr function.
    void new_player_record(string player_name) {
        ofstream file;
        file.open("../Source/Player Records.txt", ios::app);
        if (!file) {
            cout << "Error opening file" << endl;
            return;
        }
        file << player_name<<" "<<get_total_score()<<" "<<get_coin_count()<<" "<<get_multiplier_count()<<" "<<get_obstacle_count()<<endl;
        //just to check if the file is being written to or not
        cout<<"Player record added"<<endl;
        file.close();
    }

    //based on discussion, when user selects the "EXISTING PLAYER" option, the game will ask player to confirrm his/her name and then the game will
    //call this function and check name (includeing necessary input validation) and then the appropriate bool value will be returned.
    bool check_if_player_exists(string player_name) {
        ifstream file;
        file.open("../Source/Player Records.txt");
        if (!file) {
            cout << "Error opening file" << endl;
            return false;
        }
        string name; 
        int attempts=0; 
        for (int i=0; i<3; i++) {
            file.clear();
            file.seekg(0, ios::beg);
            while (file >> name) {
                if (name == player_name) {
                    file.close();
                    return true;
                }
            }
            cout<<"Player name not found. Please try again."<<endl;
            attempts++;
            if (attempts == 3) {
                cout<<"You have exceeded the maximum number of attempts. Re-directing to PLAYER SELECT"<<endl;
                file.close();
                return false;
            }
        }
    }


    


    void print_items() {
        Item* temp = head;
        while (temp != nullptr) {
            cout << temp->type << " " << temp->value << endl;
            temp = temp->next;
        }
    }

    ~Collected_Items() {
        while (head != nullptr) {
            Item* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

