#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Goods.h"
#include <string>

struct Node {
    Goods data;
    Node* next;
    Node(const Goods& g) : data(g), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList();
    ~LinkedList();

    void add(const Goods& g);
    void clear();
    Node* getHead() const { return head; }

    bool searchById(const std::string& targetId) const;
    bool removeById(const std::string& targetId);
    Goods* findById(const std::string& targetId);

    void displayAll() const;
};

#endif