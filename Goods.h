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
    std::string getManufacturer() const { return manufacturer; }
    Date getProductionDate() const { return productionDate; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    Date getStorageDate() const { return storageDate; }


    // Setters
    void setName(const std::string& value) { name = value; }
    void setManufacturer(const std::string& value) { manufacturer = value; }
    void setProductionDate(const Date& value) { productionDate = value; }
    void setPrice(double value) { price = value; }
    void setQuantity(int value) { quantity = value; }
    void setStorageDate(const Date& value) { storageDate = value; }

    // 将对象转换为CSV格式的一行数据
    std::string toCSV() const;
    
    // 显示格式化信息
    void display() const;
};

#endif
