#include "Goods.h"
#include <iostream>
#include <iomanip>

Goods::Goods() : price(0), quantity(0) {}

Goods::Goods(std::string id, std::string name, std::string mfg, 
             Date pDate, double price, int qty, Date sDate)
    : id(id), name(name), manufacturer(mfg), productionDate(pDate), 
      price(price), quantity(qty), storageDate(sDate) {}

std::string Goods::toCSV() const {
    return id + "," + name + "," + manufacturer + "," + 
           productionDate.toString() + "," + std::to_string(price) + "," + 
           std::to_string(quantity) + "," + storageDate.toString();
}

void Goods::display() const {
    std::cout << std::left << std::setw(10) << id 
              << std::setw(15) << name 
              << std::setw(10) << price 
              << std::setw(10) << quantity 
              << std::setw(15) << productionDate.toString() << std::endl;
}