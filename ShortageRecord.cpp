#include "ShortageRecord.h"
#include <iomanip>
#include <iostream>
#include <sstream>

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
    std::stringstream ss(line);
    std::string recordId, goodsId, goodsName, currentQuantityStr;
    std::string requiredQuantityStr, shortageQuantityStr, registerDateStr;
    std::string status, remark;

    getline(ss, recordId, ',');
    getline(ss, goodsId, ',');
    getline(ss, goodsName, ',');
    getline(ss, currentQuantityStr, ',');
    getline(ss, requiredQuantityStr, ',');
    getline(ss, shortageQuantityStr, ',');
    getline(ss, registerDateStr, ',');
    getline(ss, status, ',');
    getline(ss, remark);

    return ShortageRecord(recordId,
                          goodsId,
                          goodsName,
                          std::stoi(currentQuantityStr),
                          std::stoi(requiredQuantityStr),
                          std::stoi(shortageQuantityStr),
                          Date::fromString(registerDateStr),
                          status,
                          remark);
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
