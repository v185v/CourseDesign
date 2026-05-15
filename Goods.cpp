#include "Goods.h"
#include <iostream>
#include <iomanip>

Goods::Goods() : price(0), quantity(0) {}

/// <summary>
/// 货物编号、货物名称、生产厂家、生产日期、货物单价、货物数量，入库时间
/// </summary>
/// <param name="id"></param>
/// <param name="name"></param>
/// <param name="mfg"></param>
/// <param name="pDate"></param>
/// <param name="price"></param>
/// <param name="qty"></param>
/// <param name="sDate"></param>
Goods::Goods(std::string id, std::string name, std::string mfg, 
             Date pDate, double price, int qty, Date sDate)
    : id(id), name(name), manufacturer(mfg), productionDate(pDate), 
      price(price), quantity(qty), storageDate(sDate) {}

/// <summary>
/// 将 Goods 对象序列化为以逗号分隔的 CSV 字符串（字段顺序：id、name、manufacturer、productionDate、price、quantity、storageDate）。
/// </summary>
/// <returns>包含对象各字段的 std::string，字段按顺序以逗号分隔；日期通过 productionDate.toString()/storageDate.toString() 转为字符串，数值通过 std::to_string 转为字符串。</returns>
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