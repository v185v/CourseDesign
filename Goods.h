#ifndef GOODS_H
#define GOODS_H

#include <string>
#include "Date.h"

/**
 * @brief 表示仓库中的一类货物。
 * @details 该类保存任务书要求的货物基础信息：编号、名称、生产厂家、生产日期、单价、数量和入库时间。
 *          库存链表中的每个节点都保存一个 Goods 对象。
 */
class Goods {
private:
    // 货物编号，作为仓库中识别货物的唯一标识。
    std::string id;
    // 货物名称，例如 "RAM"、"H200"。
    std::string name;
    // 生产厂家，用于显示、查询和按厂家统计。
    std::string manufacturer;
    // 生产日期，用于查询生产日期范围和判断日期合法性。
    Date productionDate;
    // 货物单价，用于库存金额统计和按单价排序。
    double price;
    // 当前库存数量，入库时增加，出库时减少。
    int quantity;
    // 入库日期，用于查询入库日期范围和库存盘点统计。
    Date storageDate;

public:
    /**
     * @brief 构造一个空货物对象。
     * @details 数值字段会被初始化为 0，主要用于临时对象或容器默认初始化。
     */
    Goods();

    /**
     * @brief 使用完整字段构造货物对象。
     * @param id 货物编号。
     * @param name 货物名称。
     * @param mfg 生产厂家。
     * @param pDate 生产日期。
     * @param price 货物单价。
     * @param qty 当前库存数量。
     * @param sDate 入库日期。
     * @details 新增货物、从 CSV 文件恢复货物时都会调用该构造函数。
     */
    Goods(std::string id, std::string name, std::string mfg,
          Date pDate, double price, int qty, Date sDate);

    /**
     * @brief 获取货物编号。
     * @return 当前货物的编号。
     */
    std::string getId() const { return id; }

    /**
     * @brief 获取货物名称。
     * @return 当前货物的名称。
     */
    std::string getName() const { return name; }

    /**
     * @brief 获取生产厂家。
     * @return 当前货物的生产厂家。
     */
    std::string getManufacturer() const { return manufacturer; }

    /**
     * @brief 获取生产日期。
     * @return 当前货物的生产日期。
     */
    Date getProductionDate() const { return productionDate; }

    /**
     * @brief 获取货物单价。
     * @return 当前货物的单价。
     */
    double getPrice() const { return price; }

    /**
     * @brief 获取库存数量。
     * @return 当前货物的库存数量。
     */
    int getQuantity() const { return quantity; }

    /**
     * @brief 获取入库日期。
     * @return 当前货物的入库日期。
     */
    Date getStorageDate() const { return storageDate; }

    /**
     * @brief 修改货物名称。
     * @param value 新的货物名称。
     */
    void setName(const std::string& value) { name = value; }

    /**
     * @brief 修改生产厂家。
     * @param value 新的生产厂家。
     */
    void setManufacturer(const std::string& value) { manufacturer = value; }

    /**
     * @brief 修改生产日期。
     * @param value 新的生产日期。
     */
    void setProductionDate(const Date& value) { productionDate = value; }

    /**
     * @brief 修改货物单价。
     * @param value 新的单价。
     */
    void setPrice(double value) { price = value; }

    /**
     * @brief 修改库存数量。
     * @param value 新的库存数量。
     * @details 出库功能会通过该方法扣减库存。
     */
    void setQuantity(int value) { quantity = value; }

    /**
     * @brief 修改入库日期。
     * @param value 新的入库日期。
     */
    void setStorageDate(const Date& value) { storageDate = value; }

    /**
     * @brief 将货物对象序列化为 CSV 一行。
     * @return 字段顺序为 id,name,manufacturer,productionDate,price,quantity,storageDate。
     * @details WarehouseManager 保存库存文件时会调用该方法。
     */
    std::string toCSV() const;

    /**
     * @brief 按固定列宽输出货物信息。
     * @details 用于显示库存清单、查询结果、排序结果和低库存结果。
     */
    void display() const;
};

#endif
