#ifndef DATA_READER_H
#define DATA_READER_H

#include <iostream>
#include <fstream>
#include <string>

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
        std::cerr << "Error: ไม่สามารถเปิดไฟล์ " << filename << " ได้\n";
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