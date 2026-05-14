#ifndef GOODS_H
#define GOODS_H

#include <string>
#include "Date.h"

class Goods {
private:
    std::string id;
    std::string name;
    std::string manufacturer;
    Date productionDate;
    double price;
    int quantity;
    Date storageDate;

public:
    Goods();
    Goods(std::string id, std::string name, std::string mfg, 
          Date pDate, double price, int qty, Date sDate);

    // Getters
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    // 将对象转换为CSV格式的一行数据
    std::string toCSV() const;
    
    // 显示格式化信息
    void display() const;
};

#endif