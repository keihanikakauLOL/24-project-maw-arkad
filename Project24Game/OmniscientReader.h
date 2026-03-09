#ifndef DATA_READER_H
#define DATA_READER_H

#include <iostream>
#include <fstream>
#include <string>
#include <utility>

class DataNode {
public:
    std::string textData;
    int num1;
    int num2;
    DataNode* next;

    DataNode(std::string t, int n1, int n2) {
        textData = t;
        num1 = n1;
        num2 = n2;
        next = nullptr;
    }
};

class DataLinkedList {
public:
    DataNode* head;
    DataNode* tail;

    DataLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void append(std::string t, int n1, int n2) {
        DataNode* newNode = new DataNode(t, n1, n2);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void sortDescending() {
        if (head == nullptr || head->next == nullptr) return;

        bool swapped;
        DataNode* ptr1;
        DataNode* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                if (ptr1->num1 < ptr1->next->num1) { 
                    std::swap(ptr1->textData, ptr1->next->textData);
                    std::swap(ptr1->num1, ptr1->next->num1);
                    std::swap(ptr1->num2, ptr1->next->num2);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }

    DataNode* getNode(int index) {
        DataNode* current = head;
        int count = 0;
        
        while (current != nullptr) {
            if (count == index) {
                return current;
            }
            count++;
            current = current->next;
        }
        return nullptr;
    }

    ~DataLinkedList() {
        DataNode* current = head;
        while (current != nullptr) {
            DataNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

inline DataLinkedList* loadDataFromFile(const std::string& filename = "data.txt") {
    DataLinkedList* list = new DataLinkedList();
    std::ifstream file(filename);

    if (!file.is_open()) {
        return list;
    }

    std::string t;
    int n1, n2;

    while (file >> t >> n1 >> n2) {
        list->append(t, n1, n2);
    }

    file.close();
    return list;
}

#endif