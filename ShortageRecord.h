#ifndef SHORTAGE_RECORD_H
#define SHORTAGE_RECORD_H

#include "Date.h"
#include <string>

class ShortageRecord {
private:
    std::string recordId;
    std::string goodsId;
    std::string goodsName;
    int currentQuantity;
    int requiredQuantity;
    int shortageQuantity;
    Date registerDate;
    std::string status;
    std::string remark;

public:
    ShortageRecord();
    ShortageRecord(const std::string& recordId,
                   const std::string& goodsId,
                   const std::string& goodsName,
                   int currentQuantity,
                   int requiredQuantity,
                   int shortageQuantity,
                   const Date& registerDate,
                   const std::string& status,
                   const std::string& remark);

    std::string toCSV() const;
    static ShortageRecord fromCSV(const std::string& line);
    void display() const;
};

#endif
