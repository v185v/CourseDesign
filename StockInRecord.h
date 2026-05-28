#ifndef STOCK_IN_RECORD_H
#define STOCK_IN_RECORD_H

#include "Date.h"
#include <string>

class StockInRecord {
private:
    std::string recordId;
    std::string goodsId;
    std::string goodsName;
    int quantity;
    double price;
    Date inDate;
    std::string operatorName;
    std::string remark;

public:
    StockInRecord();
    StockInRecord(const std::string& recordId,
                  const std::string& goodsId,
                  const std::string& goodsName,
                  int quantity,
                  double price,
                  const Date& inDate,
                  const std::string& operatorName,
                  const std::string& remark);

    std::string toCSV() const;
    static StockInRecord fromCSV(const std::string& line);
    void display() const;
};

#endif
