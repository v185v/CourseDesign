#include "StockOutRecord.h"
#include "InputValidator.h"
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

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
    std::vector<std::string> fields = InputValidator::splitCsvFields(line);
    if (fields.size() != 9) {
        throw std::invalid_argument("invalid stock-out csv field count");
    }

    InputValidator::requireNonEmpty(fields[0], "recordId");
    InputValidator::requireNonEmpty(fields[1], "goodsId");
    InputValidator::requireNonEmpty(fields[2], "goodsName");
    InputValidator::requireNonEmpty(fields[6], "receiver");
    InputValidator::requireNonEmpty(fields[7], "operatorName");

    int quantity = InputValidator::parsePositiveInt(fields[3], "quantity");
    double price = InputValidator::parseNonNegativeDouble(fields[4], "price");
    Date outDate = InputValidator::parseValidDate(fields[5], "outDate");

    return StockOutRecord(fields[0],
                          fields[1],
                          fields[2],
                          quantity,
                          price,
                          outDate,
                          fields[6],
                          fields[7],
                          fields[8]);
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
