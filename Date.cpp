#include "Date.h"
#include <sstream>
#include <iomanip>

Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

std::string Date::toString() const {
    std::stringstream ss;
    ss << year << "-" << month << "-" << day;
    return ss.str();
}

Date Date::fromString(const std::string& str) {
    Date d;
    char dash; // 用于跳过 '-' 符号
    std::stringstream ss(str);
    ss >> d.year >> dash >> d.month >> dash >> d.day;
    return d;
}

int Date::toNumber() const {
    return year * 10000 + month * 100 + day;
}