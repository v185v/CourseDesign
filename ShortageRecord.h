#ifndef SHORTAGE_RECORD_H
#define SHORTAGE_RECORD_H

#include "Date.h"
#include <string>

/**
 * @brief 表示一条缺库登记记录。
 * @details 当库存低于需求值时生成，用于记录当前库存、需求数量和缺少数量。
 */
class ShortageRecord {
private:
    // 缺库登记编号，用于唯一标识一条缺库记录。
    std::string recordId;
    // 货物编号，对应库存中的 Goods::id。
    std::string goodsId;
    // 货物名称，便于单据直接查看。
    std::string goodsName;
    // 登记时货物的当前库存数量。
    int currentQuantity;
    // 用户输入的需求数量或安全库存数量。
    int requiredQuantity;
    // 当前库存与需求数量之间的差额。
    int shortageQuantity;
    // 缺库登记日期。
    Date registerDate;
    // 缺库处理状态，例如“未处理”“已采购”“已完成”。
    std::string status;
    // 备注信息，用于记录补充说明。
    std::string remark;

public:
    /**
     * @brief 构造空缺库登记记录。
     * @details 数值字段会初始化为 0，便于默认构造和临时对象使用。
     */
    ShortageRecord();

    /**
     * @brief 使用完整字段构造缺库登记记录。
     * @param recordId 登记编号。
     * @param goodsId 货物编号。
     * @param goodsName 货物名称。
     * @param currentQuantity 当前库存。
     * @param requiredQuantity 需求数量。
     * @param shortageQuantity 缺少数量。
     * @param registerDate 登记日期。
     * @param status 状态。
     * @param remark 备注。
     */
    ShortageRecord(const std::string& recordId,
                   const std::string& goodsId,
                   const std::string& goodsName,
                   int currentQuantity,
                   int requiredQuantity,
                   int shortageQuantity,
                   const Date& registerDate,
                   const std::string& status,
                   const std::string& remark);

    /**
     * @brief 序列化为 CSV 一行。
     * @return 字段顺序为 recordId,goodsId,goodsName,currentQuantity,requiredQuantity,shortageQuantity,registerDate,status,remark。
     */
    std::string toCSV() const;

    /**
     * @brief 从 CSV 行反序列化缺库登记记录。
     * @param line CSV 文件中的一行文本。
     * @return 解析出的缺库登记对象。
     * @throws std::invalid_argument 字段数量或字段内容不合法时抛出异常。
     */
    static ShortageRecord fromCSV(const std::string& line);

    /**
     * @brief 按固定列宽输出缺库登记记录。
     * @details 用于“查看缺库登记记录”界面。
     */
    void display() const;
};

#endif
