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

        // current 是指针，用 -> 访问里面的 data
        // data 是对象本体，用 . 调用它的 getId() 方法
        if (current->data.getId() == targetId) {

            // 如果找到了，打印出来并返回 true
            std::cout << "\n✅ 找到货物信息：" << std::endl;
            std::cout << std::string(80, '-') << std::endl;
            // 打印表头 (这里简单输出，后续可以在菜单类里统一格式)
            std::cout << std::left << std::setw(10) << "编号"
                << std::setw(15) << "名称"
                << std::setw(10) << "单价"
                << std::setw(10) << "数量"
                << std::setw(15) << "生产日期" << std::endl;
            std::cout << std::string(80, '-') << std::endl;

            // 打印这节车厢的货物数据
            current->data.display();
            std::cout << std::string(80, '-') << std::endl;

            return true; // 任务成功，结束寻找
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

    //如果要删除的刚好是第一节车厢（头节点）
    if (head->data.getId() == targetId) {
        Node* temp = head;       // 记住这节车厢的位置，等下要销毁它
        head = head->next;       // 把火车头往后移一节，认第二节当老大
        delete temp;             // 💥 彻底销毁原来的第一节车厢（释放内存）
        std::cout << "\n✅ 成功删除编号为 [" << targetId << "] 的货物！" << std::endl;
        return true;
    }

    //要删除的是中间或尾部的车厢
    Node* current = head;        // 探路员：负责找目标
    Node* prev = nullptr;        // 跟屁虫：负责记录探路员的前一步位置

    // 只要没走到尽头，且当前车厢不是我们要找的，就继续往后走
    while (current != nullptr && current->data.getId() != targetId) {
        prev = current;          // 跟屁虫走到探路员现在的位置
        current = current->next; // 探路员往前走一步
    }

    // 循环结束了，看看是因为什么结束的
    if (current == nullptr) {
        //找遍了都没找到
        std::cout << "\n❌ 删除失败：未找到编号为 [" << targetId << "] 的货物。" << std::endl;
        return false;
    }

    // 此时 current 停在我们要删的车厢，prev 停在它前面那节
    prev->next = current->next; // 让前面那节的挂钩，直接挂到后面那节上

    delete current;             // 💥 销毁当前车厢（释放内存）

    std::cout << "\n✅ 成功删除编号为 [" << targetId << "] 的货物！" << std::endl;
    return true;
}