#include "ShortageRecord.h"
#include "InputValidator.h"
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

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
    std::vector<std::string> fields = InputValidator::splitCsvFields(line);
    if (fields.size() != 9) {
        throw std::invalid_argument("invalid shortage csv field count");
    }

    InputValidator::requireNonEmpty(fields[0], "recordId");
    InputValidator::requireNonEmpty(fields[1], "goodsId");
    InputValidator::requireNonEmpty(fields[2], "goodsName");
    InputValidator::requireNonEmpty(fields[7], "status");

    int currentQuantity = InputValidator::parseNonNegativeInt(fields[3], "currentQuantity");
    int requiredQuantity = InputValidator::parsePositiveInt(fields[4], "requiredQuantity");
    int shortageQuantity = InputValidator::parsePositiveInt(fields[5], "shortageQuantity");
    Date registerDate = InputValidator::parseValidDate(fields[6], "registerDate");

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
