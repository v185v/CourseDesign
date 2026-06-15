#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include "Date.h"
#include <string>
#include <vector>

/**
 * @brief 输入和文件字段合法性检查工具类。
 * @details 该类只包含 static 方法，不需要创建对象。WarehouseManager 使用它读取并校验控制台输入，
 *          各类单据记录使用它解析和校验 CSV 字段。统一放在这里可以避免各个功能中重复写 cin.fail()
 *          和数值范围判断。
 */
class InputValidator {
public:
    /**
     * @brief 清理 cin 的错误状态和缓冲区。
     * @details 当用户输入字母到数字字段等导致 cin 失败时，调用该方法恢复后续输入。
     */
    static void clearInputError();

    /**
     * @brief 按逗号切分 CSV 行。
     * @param line CSV 文件中的一行文本。
     * @return 切分后的字段数组。
     * @details 当前项目使用简单 CSV 格式，字段本身不允许包含逗号。
     */
    static std::vector<std::string> splitCsvFields(const std::string& line);

    /**
     * @brief 判断字符串是否包含会破坏 CSV 格式的字符。
     * @param value 待检查字符串。
     * @return 包含逗号或换行符时返回 true，否则返回 false。
     */
    static bool hasCsvUnsafeChar(const std::string& value);

    /**
     * @brief 读取一个不含空格的字符串字段。
     * @param prompt 输入提示文本。
     * @param value 输出参数，保存读取到的字符串。
     * @param fieldName 字段名称，用于错误提示。
     * @param allowNone 是否允许输入 "none" 作为备注等空值占位。
     * @return 输入合法时返回 true，否则返回 false。
     * @details 会检查读取失败、空字符串、非法 CSV 字符等问题。
     */
    static bool readToken(const std::string& prompt,
                          std::string& value,
                          const std::string& fieldName,
                          bool allowNone = false);

    /**
     * @brief 读取 y/n 选择。
     * @param prompt 输入提示文本。
     * @param value 输出参数，y/Y 时为 true，n/N 时为 false。
     * @return 输入为 y/Y/n/N 时返回 true，否则返回 false。
     */
    static bool readYesNo(const std::string& prompt, bool& value);

    /**
     * @brief 读取整数并检查最小值。
     * @param prompt 输入提示文本。
     * @param value 输出参数，保存读取到的整数。
     * @param minValue 允许的最小值。
     * @param fieldName 字段名称，用于错误提示。
     * @return 输入为整数且不小于 minValue 时返回 true，否则返回 false。
     */
    static bool readIntMin(const std::string& prompt,
                           int& value,
                           int minValue,
                           const std::string& fieldName);

    /**
     * @brief 读取整数并检查闭区间范围。
     * @param prompt 输入提示文本。
     * @param value 输出参数，保存读取到的整数。
     * @param minValue 允许的最小值。
     * @param maxValue 允许的最大值。
     * @param fieldName 字段名称，用于错误提示。
     * @return 输入为整数且落在 [minValue, maxValue] 内时返回 true，否则返回 false。
     */
    static bool readIntRange(const std::string& prompt,
                             int& value,
                             int minValue,
                             int maxValue,
                             const std::string& fieldName);

    /**
     * @brief 读取小数并检查最小值。
     * @param prompt 输入提示文本。
     * @param value 输出参数，保存读取到的小数。
     * @param minValue 允许的最小值。
     * @param fieldName 字段名称，用于错误提示。
     * @return 输入为数字且不小于 minValue 时返回 true，否则返回 false。
     */
    static bool readDoubleMin(const std::string& prompt,
                              double& value,
                              double minValue,
                              const std::string& fieldName);

    /**
     * @brief 读取年月日并生成 Date 对象。
     * @param prompt 输入提示文本。
     * @param date 输出参数，保存读取到的日期。
     * @param fieldName 字段名称，用于错误提示。
     * @return 输入格式正确且日期合法时返回 true，否则返回 false。
     * @details 用户需要按“年 月 日”三个数字输入，例如 2026 6 15。
     */
    static bool readDateValue(const std::string& prompt,
                              Date& date,
                              const std::string& fieldName);

    /**
     * @brief 校验日期范围是否合法。
     * @param startDate 起始日期。
     * @param endDate 结束日期。
     * @return 两个日期都合法且起始日期不晚于结束日期时返回 true。
     */
    static bool validateDateRange(const Date& startDate, const Date& endDate);

    /**
     * @brief 要求字符串字段不能为空。
     * @param value 待检查字符串。
     * @param fieldName 字段名称，用于异常信息。
     * @throws std::invalid_argument 字段为空时抛出异常。
     * @details 主要用于 CSV 记录解析，异常会被显示记录列表的函数捕获并跳过坏行。
     */
    static void requireNonEmpty(const std::string& value, const std::string& fieldName);

    /**
     * @brief 将字符串解析为非负整数。
     * @param value 待解析字符串。
     * @param fieldName 字段名称，用于异常信息。
     * @return 解析后的整数。
     * @throws std::invalid_argument 数值为负数时抛出异常。
     */
    static int parseNonNegativeInt(const std::string& value, const std::string& fieldName);

    /**
     * @brief 将字符串解析为正整数。
     * @param value 待解析字符串。
     * @param fieldName 字段名称，用于异常信息。
     * @return 解析后的整数。
     * @throws std::invalid_argument 数值小于等于 0 时抛出异常。
     */
    static int parsePositiveInt(const std::string& value, const std::string& fieldName);

    /**
     * @brief 将字符串解析为非负小数。
     * @param value 待解析字符串。
     * @param fieldName 字段名称，用于异常信息。
     * @return 解析后的 double 数值。
     * @throws std::invalid_argument 数值为负数时抛出异常。
     */
    static double parseNonNegativeDouble(const std::string& value, const std::string& fieldName);

    /**
     * @brief 将字符串解析为合法日期。
     * @param value 待解析字符串。
     * @param fieldName 字段名称，用于异常信息。
     * @return 解析后的 Date 对象。
     * @throws std::invalid_argument 日期格式或日期值非法时抛出异常。
     */
    static Date parseValidDate(const std::string& value, const std::string& fieldName);
};

#endif
