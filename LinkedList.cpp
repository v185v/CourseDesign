#include "LinkedList.h"
#include <iostream>
#include <iomanip>

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

bool LinkedList::searchById(const std::string& targetId) const {
   
    Node* current = head;

    
    while (current != nullptr) {

        if (current->data.getId() == targetId) {
            std::cout << "\n✅ 找到货物信息：" << std::endl;
            std::cout << std::string(80, '-') << std::endl;
            // 打印表头 (这里简单输出，后续可以在菜单类里统一格式)
            std::cout << std::left << std::setw(10) << "编号"
                << std::setw(15) << "名称"
                << std::setw(10) << "单价"
                << std::setw(10) << "数量"
                << std::setw(15) << "生产日期" << std::endl;
            std::cout << std::string(80, '-') << std::endl;
            current->data.display();
            std::cout << std::string(80, '-') << std::endl;

            return true;
        }


        current = current->next;
    }

    std::cout << "\n❌ 仓库中未找到编号为 [" << targetId << "] 的货物。" << std::endl;
    return false;
}

bool LinkedList::removeById(const std::string& targetId) {
    //如果仓库（链表）是空的，直接返回失败
    if (head == nullptr) {
        std::cout << "\n❌ 仓库为空，无法删除！" << std::endl;
        return false;
    }

    if (head->data.getId() == targetId) {
        Node* temp = head;       
        head = head->next;     
        delete temp;         
        std::cout << "\n✅ 成功删除编号为 [" << targetId << "] 的货物！" << std::endl;
        return true;
    }

    Node* current = head;      
    Node* prev = nullptr;       

    while (current != nullptr && current->data.getId() != targetId) {
        prev = current;      
        current = current->next; 
    }

    if (current == nullptr) {
        //找遍了都没找到
        std::cout << "\n❌ 删除失败：未找到编号为 [" << targetId << "] 的货物。" << std::endl;
        return false;
    }

    // 此时 current 停在我们要删的车厢，prev 停在它前面那节
    prev->next = current->next; 

    delete current;        

    std::cout << "\n✅ 成功删除编号为 [" << targetId << "] 的货物！" << std::endl;
    return true;
}

Goods* LinkedList::findById(const std::string& targetId) {
    Node* current = head;

    while (current != nullptr) {
        if (current->data.getId() == targetId) {
            return &(current->data);
        }
        current = current->next;
    }

    return nullptr;
}

void LinkedList::displayAll() const {
    if (!head) {
        std::cout << "当前仓库为空！" << std::endl;
        return;
    }
    
    std::cout << std::string(80, '-') << std::endl;
    std::cout << std::left << std::setw(10) << "编号" 
              << std::setw(15) << "名称" 
              << std::setw(15) << "厂家" 
              << std::setw(15) << "生产日期" 
              << std::setw(10) << "单价" 
              << std::setw(10) << "数量" 
              << std::setw(15) << "入库时间" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    Node* current = head;
    while (current) {
        // current->data.display() 这里会调用 Goods 类的 display() const 方法
        current->data.display(); 
        current = current->next;
    }
    std::cout << std::string(80, '-') << std::endl;
}