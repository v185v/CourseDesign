#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::add(const Goods& g) {
    Node* newNode = new Node(g);
    if (!head) {
        head = newNode;
    }
    else {
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

void LinkedList::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}