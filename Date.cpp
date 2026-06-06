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

bool Date::isValid() const {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;

    int days[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    bool leap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    if (leap) days[2] = 29;

    return day >= 1 && day <= days[month];
}