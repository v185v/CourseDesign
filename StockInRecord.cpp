#include "StockInRecord.h"
#include <iomanip>
#include <iostream>
#include <sstream>

StockInRecord::StockInRecord() : quantity(0), price(0) {}

StockInRecord::StockInRecord(const std::string& recordId,// 进货记录编号
                             const std::string& goodsId,// 货物编号
                             const std::string& goodsName,// 货物名称
                             int quantity,// 进货数量
                             double price,// 进货单价
                             const Date& inDate,// 进货日期
                             const std::string& operatorName,// 经办人
                             const std::string& remark)// 备注
    : recordId(recordId),
      goodsId(goodsId),
      goodsName(goodsName),
      quantity(quantity),
      price(price),
      inDate(inDate),
      operatorName(operatorName),
      remark(remark) {}

std::string StockInRecord::toCSV() const {
    return recordId + "," + goodsId + "," + goodsName + "," +
           std::to_string(quantity) + "," + std::to_string(price) + "," +
           inDate.toString() + "," + operatorName + "," + remark;
}

StockInRecord StockInRecord::fromCSV(const std::string& line) {
    std::stringstream ss(line);
    std::string recordId, goodsId, goodsName, quantityStr, priceStr;
    std::string inDateStr, operatorName, remark;

    getline(ss, recordId, ',');
    getline(ss, goodsId, ',');
    getline(ss, goodsName, ',');
    getline(ss, quantityStr, ',');
    getline(ss, priceStr, ',');
    getline(ss, inDateStr, ',');
    getline(ss, operatorName, ',');
    getline(ss, remark);

    return StockInRecord(recordId,
                         goodsId,
                         goodsName,
                         std::stoi(quantityStr),
                         std::stod(priceStr),
                         Date::fromString(inDateStr),
                         operatorName,
                         remark);
}

void StockInRecord::display() const {
    std::cout << std::left
              << std::setw(30) << recordId
              << std::setw(12) << goodsId
              << std::setw(16) << goodsName
              << std::setw(10) << quantity
              << std::setw(10) << price
              << std::setw(14) << inDate.toString()
              << std::setw(14) << operatorName
              << std::setw(20) << remark
              << std::endl;
}
