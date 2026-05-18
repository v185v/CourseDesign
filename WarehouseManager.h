#ifndef WAREHOUSE_MANAGER_H
#define WAREHOUSE_MANAGER_H

#include "LinkedList.h"

class WarehouseManager {
private:
    LinkedList inventory;   //自定义链表，作为仓库的内存载体
    std::string dataFile; // 做文件读写时使用
    void loadFromFile();
    void saveToFile() const;
    void sortGoodsUI() const;
    static bool compareGoods(const Goods* a, const Goods* b, int type, bool isAscending);
    static void quickSort(const Goods** arr, int left, int right, int type, bool isAscending);

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