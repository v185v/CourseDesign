#include "Goods.h"
#include <iostream>
#include <iomanip>

Goods::Goods() : price(0), quantity(0) {}

Goods::Goods(std::string id, 
             std::string name, std::string mfg, 
             Date pDate, 
             double price, 
             int qty, 
             Date sDate)
    :   id(id), 
        name(name), 
        manufacturer(mfg), 
        productionDate(pDate), 
        price(price), 
        quantity(qty), 
        storageDate(sDate) {}


std::string Goods::toCSV() const {
    return id + "," + name + "," + manufacturer + "," + 
           productionDate.toString() + "," + std::to_string(price) + "," + 
           std::to_string(quantity) + "," + storageDate.toString();
}

void Goods::display() const {
    // 严格按照表头的顺序和宽度进行格式化输出
    std::cout << std::left 
              << std::setw(10) << id                         // 1. 编号
              << std::setw(15) << name                       // 2. 名称
              << std::setw(15) << manufacturer               // 3. 厂家 
              << std::setw(15) << productionDate.toString()  // 4. 生产日期
              << std::setw(10) << price                      // 5. 单价
              << std::setw(10) << quantity                   // 6. 数量
              << std::setw(15) << storageDate.toString()     // 7. 入库时间 
              << std::endl;
}