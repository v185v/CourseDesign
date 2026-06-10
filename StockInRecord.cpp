#include "StockInRecord.h"
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>

namespace {
    std::vector<std::string> splitCsvFields(const std::string& line) {
        std::vector<std::string> fields;
        std::string field;
        std::stringstream ss(line);
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        return fields;
    }

    void requireNonEmpty(const std::string& value, const std::string& fieldName) {
        if (value.empty()) {
            throw std::invalid_argument(fieldName + " cannot be empty");
        }
    }

    int parsePositiveInt(const std::string& value, const std::string& fieldName) {
        int result = std::stoi(value);
        if (result <= 0) {
            throw std::invalid_argument(fieldName + " must be positive");
        }
        return result;
    }

    double parseNonNegativeDouble(const std::string& value, const std::string& fieldName) {
        double result = std::stod(value);
        if (result < 0) {
            throw std::invalid_argument(fieldName + " cannot be negative");
        }
        return result;
    }

    Date parseValidDate(const std::string& value, const std::string& fieldName) {
        Date date = Date::fromString(value);
        if (!date.isValid()) {
            throw std::invalid_argument(fieldName + " is invalid");
        }
        return date;
    }
}

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
    std::vector<std::string> fields = splitCsvFields(line);
    if (fields.size() != 8) {
        throw std::invalid_argument("invalid stock-in csv field count");
    }

    requireNonEmpty(fields[0], "recordId");
    requireNonEmpty(fields[1], "goodsId");
    requireNonEmpty(fields[2], "goodsName");
    requireNonEmpty(fields[6], "operatorName");

    int quantity = parsePositiveInt(fields[3], "quantity");
    double price = parseNonNegativeDouble(fields[4], "price");
    Date inDate = parseValidDate(fields[5], "inDate");

    return StockInRecord(fields[0],
                         fields[1],
                         fields[2],
                         quantity,
                         price,
                         inDate,
                         fields[6],
                         fields[7]);
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
