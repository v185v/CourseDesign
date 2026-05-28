#include "StockOutRecord.h"
#include <iomanip>
#include <iostream>
#include <sstream>

StockOutRecord::StockOutRecord() : quantity(0), price(0) {}

StockOutRecord::StockOutRecord(const std::string& recordId,
                               const std::string& goodsId,
                               const std::string& goodsName,
                               int quantity,
                               double price,
                               const Date& outDate,
                               const std::string& receiver,
                               const std::string& operatorName,
                               const std::string& remark)
    : recordId(recordId),
      goodsId(goodsId),
      goodsName(goodsName),
      quantity(quantity),
      price(price),
      outDate(outDate),
      receiver(receiver),
      operatorName(operatorName),
      remark(remark) {}

std::string StockOutRecord::toCSV() const {
    return recordId + "," + goodsId + "," + goodsName + "," +
           std::to_string(quantity) + "," + std::to_string(price) + "," +
           outDate.toString() + "," + receiver + "," + operatorName + "," +
           remark;
}

StockOutRecord StockOutRecord::fromCSV(const std::string& line) {
    std::stringstream ss(line);
    std::string recordId, goodsId, goodsName, quantityStr, priceStr;
    std::string outDateStr, receiver, operatorName, remark;

    getline(ss, recordId, ',');
    getline(ss, goodsId, ',');
    getline(ss, goodsName, ',');
    getline(ss, quantityStr, ',');
    getline(ss, priceStr, ',');
    getline(ss, outDateStr, ',');
    getline(ss, receiver, ',');
    getline(ss, operatorName, ',');
    getline(ss, remark);

    return StockOutRecord(recordId,
                          goodsId,
                          goodsName,
                          std::stoi(quantityStr),
                          std::stod(priceStr),
                          Date::fromString(outDateStr),
                          receiver,
                          operatorName,
                          remark);
}

void StockOutRecord::display() const {
    std::cout << std::left
              << std::setw(30) << recordId
              << std::setw(12) << goodsId
              << std::setw(16) << goodsName
              << std::setw(10) << quantity
              << std::setw(10) << price
              << std::setw(14) << outDate.toString()
              << std::setw(14) << receiver
              << std::setw(14) << operatorName
              << std::setw(20) << remark
              << std::endl;
}
