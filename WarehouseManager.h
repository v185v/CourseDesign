#ifndef WAREHOUSE_MANAGER_H
#define WAREHOUSE_MANAGER_H

#include "LinkedList.h"

class WarehouseManager {
private:
    LinkedList inventory;   // 核心：我们的自定义链表，作为仓库的内存载体
    // std::string dataFile; // 预留：下一步做文件读写时使用

public:
    WarehouseManager();
    ~WarehouseManager();

    // 启动系统的主循环
    void run();

private:
    // 界面显示与交互的辅助方法
    void showMenu() const;
    void addGoodsUI();
    void removeGoodsUI();
    void queryGoodsUI();
    void displayAllUI() const;
};

#endif