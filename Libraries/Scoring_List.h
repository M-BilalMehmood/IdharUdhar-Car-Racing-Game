#include <iostream>
using namespace std;

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
    Collected_Items() : head(nullptr), tail(nullptr) {}
public:
    Collected_Items() : head(nullptr), tail(nullptr) {}

    static Collected_Items* get_instance() {
        if (instance == nullptr) {
            instance = new Collected_Items();
        }
        return instance;
    }

    void add_item(string Item_Type, int Score_Value) {
        Item* new_item = new Item(Item_Type, Score_Value);
        if (head == nullptr) {
            head = tail = new_item;
        }
        else {
            new_item->next = head;
            head->prev = new_item;
            head = new_item;
        }
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

