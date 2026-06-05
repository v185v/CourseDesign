#ifndef DATE_H
#define DATE_H

#include <string>

/// @brief 表示日期的类，包含年、月、日三个成员变量，并提供了将日期转换为字符串和从字符串解析日期的方法。
/// @details 该类用于在项目中处理日期相关的功能，例如显示日期和从CSV文件中读取日期。
class Date {
public:
    int year, month, day;

    Date(int y = 2000, int m = 1, int d = 1);
    
    // 将日期转换为字符串 (用于显示和保存到CSV)
    std::string toString() const;

    // 将日期转换为一个整数，格式为 YYYYMMDD，便于比较和排序,例如 2026-6-5 转成 20260605
    int toNumber() const;
    
    // 从字符串解析日期 (用于从CSV读取)
    static Date fromString(const std::string& str);

};
#endif // DATE_H