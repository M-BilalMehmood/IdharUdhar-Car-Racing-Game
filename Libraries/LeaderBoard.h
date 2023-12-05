#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

struct Player{
    string name;
    int score; 
};

class DynamicArray {
private:
    Player* arr;
    int capacity;
    int size; //size will help indicate the number of elements in the array.
public:
    DynamicArray() : capacity(1), size(0) {
        arr = new Player[capacity];
    }

    void push(Player player) { //as the name suggests, a new player is added to the end of the list. 
        // If the array is full, it is resized to twice its current capacity.
        if (size == capacity) {
            Player* temp = new Player[2 * capacity];
            for (int i = 0; i < capacity; i++){
                temp[i] = arr[i];
            }
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
        arr[size] = player; 
        size++; //since the size is incremented after the player is added, the player is always added to the last position. 
    }

    void pop() { //as name suggests, the last player is removed from the array.
        if (size > 0) {
            size--;
            if (size <= capacity / 4) {
                Player* temp = new Player[capacity / 2];
                for (int i = 0; i < size; i++)
                    temp[i] = arr[i];
                delete[] arr;
                capacity /= 2;
                arr = temp;
            }
        }
    }
    
    Player& operator[](int i) {
        return arr[i];
    }
    
    int getSize() {
        return size;
    }
};

class LeaderBoard {
private:
    DynamicArray heap;

    void heapify(int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < heap.getSize() && heap[left].score > heap[largest].score)
            largest = left;
        
        if (right < heap.getSize() && heap[right].score > heap[largest].score)
            largest = right;
        
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify(largest);
        }
    }
public:
    void insert(Player player) {
        heap.push(player);
        int i = heap.getSize() - 1;
        while (i != 0 && heap[(i - 1) / 2].score < heap[i].score) {
            swap(heap[(i - 1) / 2], heap[i]);
            i = (i - 1) / 2;
        }
        buildHeap();
        if (heap.getSize() > 5) {
            // Remove the smallest score
            swap(heap[0], heap[heap.getSize() - 1]);
            heap.pop();
            heapify(0);
        }
    }
    void buildHeap() {
        for (int i = heap.getSize() / 2 - 1; i >= 0; i--)
            heapify(i);
    }
    void displayTop5() {
        for (int i = 0; i < 5 && i < heap.getSize(); i++)
            cout << heap[i].name << ": " << heap[i].score << endl;
    }
    void populateFromFile(string filename) {
        ifstream file(filename);
        string name;
        int score;
        while (file >> name >> score) {
            insert({name, score});
        }
    }
};


