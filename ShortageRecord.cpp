#include "ShortageRecord.h"
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

    int parseNonNegativeInt(const std::string& value, const std::string& fieldName) {
        int result = std::stoi(value);
        if (result < 0) {
            throw std::invalid_argument(fieldName + " cannot be negative");
        }
        return result;
    }

    int parsePositiveInt(const std::string& value, const std::string& fieldName) {
        int result = std::stoi(value);
        if (result <= 0) {
            throw std::invalid_argument(fieldName + " must be positive");
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

ShortageRecord::ShortageRecord()
    : currentQuantity(0), requiredQuantity(0), shortageQuantity(0) {}

ShortageRecord::ShortageRecord(const std::string& recordId,
                               const std::string& goodsId,
                               const std::string& goodsName,
                               int currentQuantity,
                               int requiredQuantity,
                               int shortageQuantity,
                               const Date& registerDate,
                               const std::string& status,
                               const std::string& remark)
    : recordId(recordId),
      goodsId(goodsId),
      goodsName(goodsName),
      currentQuantity(currentQuantity),
      requiredQuantity(requiredQuantity),
      shortageQuantity(shortageQuantity),
      registerDate(registerDate),
      status(status),
      remark(remark) {}

std::string ShortageRecord::toCSV() const {
    return recordId + "," + goodsId + "," + goodsName + "," +
           std::to_string(currentQuantity) + "," +
           std::to_string(requiredQuantity) + "," +
           std::to_string(shortageQuantity) + "," +
           registerDate.toString() + "," + status + "," + remark;
}

ShortageRecord ShortageRecord::fromCSV(const std::string& line) {
    std::vector<std::string> fields = splitCsvFields(line);
    if (fields.size() != 9) {
        throw std::invalid_argument("invalid shortage csv field count");
    }

    requireNonEmpty(fields[0], "recordId");
    requireNonEmpty(fields[1], "goodsId");
    requireNonEmpty(fields[2], "goodsName");
    requireNonEmpty(fields[7], "status");

    int currentQuantity = parseNonNegativeInt(fields[3], "currentQuantity");
    int requiredQuantity = parsePositiveInt(fields[4], "requiredQuantity");
    int shortageQuantity = parsePositiveInt(fields[5], "shortageQuantity");
    Date registerDate = parseValidDate(fields[6], "registerDate");

    if (shortageQuantity != requiredQuantity - currentQuantity) {
        throw std::invalid_argument("shortageQuantity does not match requiredQuantity - currentQuantity");
    }

    return ShortageRecord(fields[0],
                          fields[1],
                          fields[2],
                          currentQuantity,
                          requiredQuantity,
                          shortageQuantity,
                          registerDate,
                          fields[7],
                          fields[8]);
}

void ShortageRecord::display() const {
    std::cout << std::left
              << std::setw(30) << recordId
              << std::setw(12) << goodsId
              << std::setw(16) << goodsName
              << std::setw(10) << currentQuantity
              << std::setw(10) << requiredQuantity
              << std::setw(10) << shortageQuantity
              << std::setw(14) << registerDate.toString()
              << std::setw(12) << status
              << std::setw(20) << remark
              << std::endl;
}
