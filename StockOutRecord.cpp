#include "StockOutRecord.h"
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
    std::vector<std::string> fields = splitCsvFields(line);
    if (fields.size() != 9) {
        throw std::invalid_argument("invalid stock-out csv field count");
    }

    requireNonEmpty(fields[0], "recordId");
    requireNonEmpty(fields[1], "goodsId");
    requireNonEmpty(fields[2], "goodsName");
    requireNonEmpty(fields[6], "receiver");
    requireNonEmpty(fields[7], "operatorName");

    int quantity = parsePositiveInt(fields[3], "quantity");
    double price = parseNonNegativeDouble(fields[4], "price");
    Date outDate = parseValidDate(fields[5], "outDate");

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
