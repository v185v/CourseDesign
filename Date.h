#ifndef DATE_H
#define DATE_H

#include <string>

/**
 * @brief 表示一个日期。
 * @details 该类只保存年、月、日三项数据，并提供字符串转换、数值转换和合法性校验。
 *          项目中的货物生产日期、入库日期、出库日期和缺库登记日期都使用该类。
 */
class Date {
public:
    // 年份，例如 2026。
    int year;
    // 月份，合法范围通常为 1 到 12。
    int month;
    // 日期，具体合法范围由年份和月份共同决定。
    int day;

    /**
     * @brief 构造日期对象。
     * @param y 年份，默认值为 2000。
     * @param m 月份，默认值为 1。
     * @param d 日期，默认值为 1。
     * @details 可以直接用用户输入的年月日创建对象，之后再调用 isValid() 判断是否合法。
     */
    Date(int y = 2000, int m = 1, int d = 1);

    /**
     * @brief 将日期转换成字符串。
     * @return 返回形如 "2026-6-15" 的字符串。
     * @details 主要用于控制台显示，以及写入 CSV 文件。
     */
    std::string toString() const;

    /**
     * @brief 将日期转换成便于比较的整数。
     * @return 返回 YYYYMMDD 格式的整数，例如 2026-6-15 会转换成 20260615。
     * @details 查询、排序、日期范围统计时可以直接比较该整数。
     */
    int toNumber() const;

    /**
     * @brief 从字符串解析日期。
     * @param str 期望格式为 "年-月-日"，例如 "2026-6-15"。
     * @return 解析成功时返回对应日期；解析失败时返回一个非法日期 Date(0, 0, 0)。
     * @details 主要用于从 CSV 文件读取日期字段。
     */
    static Date fromString(const std::string& str);

    /**
     * @brief 判断日期是否合法。
     * @return 日期在允许范围内时返回 true，否则返回 false。
     * @details 会检查年份范围、月份范围、每月天数以及闰年二月 29 日。
     */
    bool isValid() const;
};

#endif
