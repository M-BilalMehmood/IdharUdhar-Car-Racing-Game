#pragma once
#include <iostream>
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

    void print_items() {
        Item* temp = head;
        while (temp != nullptr) {
            cout << temp->type << " " << temp->value << endl;
            temp = temp->next;
        }
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

    

    ~Collected_Items() {
        while (head != nullptr) {
            Item* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

