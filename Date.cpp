#include "Date.h"
#include <iomanip>
#include <sstream>

/**
 * @brief 构造日期对象。
 * @param y 年份。
 * @param m 月份。
 * @param d 日期。
 * @details 构造函数只负责保存年月日，不主动判断合法性；需要时由调用方使用 isValid() 校验。
 */
Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

/**
 * @brief 将日期转换为字符串。
 * @return 返回 "年-月-日" 格式的字符串。
 * @details CSV 保存和控制台显示都依赖该格式。
 */
std::string Date::toString() const {
    std::stringstream ss;
    ss << year << "-" << month << "-" << day;
    return ss.str();
}

/**
 * @brief 从字符串解析日期。
 * @param str 期望格式为 "年-月-日"。
 * @return 解析成功时返回对应日期；解析失败时返回 Date(0, 0, 0)。
 * @details 该方法会严格检查两个分隔符是否都是 '-'，并拒绝尾部带多余字符的字符串。
 */
Date Date::fromString(const std::string& str) {
    Date d(0, 0, 0);
    char dash1, dash2; // 用于保存并校验两个日期分隔符。
    std::stringstream ss(str);

    if (!(ss >> d.year >> dash1 >> d.month >> dash2 >> d.day)) {
        return Date(0, 0, 0); // 读取年月日失败时返回非法日期。
    }
    if (dash1 != '-' || dash2 != '-') {
        return Date(0, 0, 0); // 分隔符不是 '-' 时视为格式错误。
    }

    ss >> std::ws; // 跳过末尾空白，便于判断是否还有其它非法字符。
    if (!ss.eof()) {
        return Date(0, 0, 0);
    }
    return d;
}

/**
 * @brief 将日期转换为整数。
 * @return 返回 YYYYMMDD 格式的整数。
 * @details 日期范围查询和排序时可以直接比较该整数。
 */
int Date::toNumber() const {
    return year * 10000 + month * 100 + day;
}

/**
 * @brief 判断日期是否合法。
 * @return 日期符合年份、月份和天数规则时返回 true，否则返回 false。
 * @details 年份限定在 1900 到 2100，二月天数会根据闰年规则调整。
 */
bool Date::isValid() const {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;

    int days[] = {0,31,28,31,30,31,30,31,31,30,31,30,31}; // 下标直接对应月份。
    bool leap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    if (leap) days[2] = 29; // 闰年时二月允许 29 天。

    return day >= 1 && day <= days[month];
}
