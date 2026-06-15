#ifndef STOCK_OUT_RECORD_H
#define STOCK_OUT_RECORD_H

#include "Date.h"
#include <string>

/**
 * @brief 表示一条出库单记录。
 * @details 每次执行出库操作时都会生成一条出库单，用来保存库存减少的流水信息。
 */
class StockOutRecord {
private:
    // 出库单编号，用于唯一标识一条出库记录。
    std::string recordId;
    // 货物编号，对应库存中的 Goods::id。
    std::string goodsId;
    // 货物名称，便于单据直接查看。
    std::string goodsName;
    // 本次出库数量。
    int quantity;
    // 出库时使用的货物单价。
    double price;
    // 出库发生的日期。
    Date outDate;
    // 领用人或客户名称。
    std::string receiver;
    // 负责出库操作的经办人。
    std::string operatorName;
    // 单据备注，用于记录补充说明。
    std::string remark;

public:
    /**
     * @brief 构造空出库单。
     * @details 数值字段会初始化为 0，便于默认构造和临时对象使用。
     */
    StockOutRecord();

    /**
     * @brief 使用完整字段构造出库单。
     * @param recordId 出库单编号。
     * @param goodsId 货物编号。
     * @param goodsName 货物名称。
     * @param quantity 出库数量。
     * @param price 出库单价。
     * @param outDate 出库日期。
     * @param receiver 领用人或客户。
     * @param operatorName 经办人。
     * @param remark 备注。
     */
    StockOutRecord(const std::string& recordId,
                   const std::string& goodsId,
                   const std::string& goodsName,
                   int quantity,
                   double price,
                   const Date& outDate,
                   const std::string& receiver,
                   const std::string& operatorName,
                   const std::string& remark);

    /**
     * @brief 序列化为 CSV 一行。
     * @return 字段顺序为 recordId,goodsId,goodsName,quantity,price,outDate,receiver,operatorName,remark。
     */
    std::string toCSV() const;

    /**
     * @brief 从 CSV 行反序列化出库单。
     * @param line CSV 文件中的一行文本。
     * @return 解析出的出库单对象。
     * @throws std::invalid_argument 字段数量或字段内容不合法时抛出异常。
     */
    static StockOutRecord fromCSV(const std::string& line);

    /**
     * @brief 按固定列宽输出出库单记录。
     * @details 用于“查看出库单记录”界面。
     */
    void display() const;
};

#endif
