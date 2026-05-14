#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Goods.h"

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
    
    // 可以在这里添加根据编号查找、删除等逻辑
};

#endif