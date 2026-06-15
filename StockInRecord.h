#ifndef STOCK_IN_RECORD_H
#define STOCK_IN_RECORD_H

#include "Date.h"
#include <string>

/**
 * @brief 表示一条入库单记录。
 * @details 每次新增货物时都会生成一条入库单，用来保存入库流水。
 */
class StockInRecord {
private:
    // 入库单编号，用于唯一标识一条入库记录。
    std::string recordId;
    // 货物编号，对应库存中的 Goods::id。
    std::string goodsId;
    // 货物名称，便于单据直接查看。
    std::string goodsName;
    // 本次入库数量。
    int quantity;
    // 本次入库时的货物单价。
    double price;
    // 入库发生的日期。
    Date inDate;
    // 负责入库操作的人员。
    std::string operatorName;
    // 单据备注，用于记录补充说明。
    std::string remark;

public:
    /**
     * @brief 构造空入库单。
     * @details 数值字段会初始化为 0，便于默认构造和临时对象使用。
     */
    StockInRecord();

    /**
     * @brief 使用完整字段构造入库单。
     * @param recordId 入库单编号。
     * @param goodsId 货物编号。
     * @param goodsName 货物名称。
     * @param quantity 入库数量。
     * @param price 入库单价。
     * @param inDate 入库日期。
     * @param operatorName 经办人。
     * @param remark 备注。
     */
    StockInRecord(const std::string& recordId,
                  const std::string& goodsId,
                  const std::string& goodsName,
                  int quantity,
                  double price,
                  const Date& inDate,
                  const std::string& operatorName,
                  const std::string& remark);

    /**
     * @brief 序列化为 CSV 一行。
     * @return 字段顺序为 recordId,goodsId,goodsName,quantity,price,inDate,operatorName,remark。
     */
    std::string toCSV() const;

    /**
     * @brief 从 CSV 行反序列化入库单。
     * @param line CSV 文件中的一行文本。
     * @return 解析出的入库单对象。
     * @throws std::invalid_argument 字段数量或字段内容不合法时抛出异常。
     */
    static StockInRecord fromCSV(const std::string& line);

    /**
     * @brief 按固定列宽输出入库单记录。
     * @details 用于“查看入库单记录”界面。
     */
    void display() const;
};

#endif
