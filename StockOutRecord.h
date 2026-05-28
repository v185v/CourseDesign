#ifndef STOCK_OUT_RECORD_H
#define STOCK_OUT_RECORD_H

#include "Date.h"
#include <string>

class StockOutRecord {
private:
    std::string recordId;
    std::string goodsId;
    std::string goodsName;
    int quantity;
    double price;
    Date outDate;
    std::string receiver;
    std::string operatorName;
    std::string remark;

public:
    StockOutRecord();
    StockOutRecord(const std::string& recordId,
                   const std::string& goodsId,
                   const std::string& goodsName,
                   int quantity,
                   double price,
                   const Date& outDate,
                   const std::string& receiver,
                   const std::string& operatorName,
                   const std::string& remark);

    std::string toCSV() const;
    static StockOutRecord fromCSV(const std::string& line);
    void display() const;
};

#endif
