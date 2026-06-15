#ifndef WAREHOUSE_MANAGER_H
#define WAREHOUSE_MANAGER_H

#include "LinkedList.h"
#include "ShortageRecord.h"
#include "StockInRecord.h"
#include "StockOutRecord.h"

/**
 * @brief 仓库管理系统的核心控制类。
 * @details 该类负责菜单交互、库存链表管理、CSV 文件读写、入库/出库/缺库记录管理、
 *          查询、排序、低库存报警和库存统计。main() 中只需要创建该类对象并调用 run()。
 */
class WarehouseManager {
private:
    // 内存中的库存数据容器，使用自定义单链表保存所有 Goods 对象。
    LinkedList inventory;
    // 库存主数据文件名，用于保存和读取 warehouse.csv。
    std::string dataFile;
    // 入库单记录文件名，用于追加和查看 stock_in.csv。
    std::string stockInFile;
    // 出库单记录文件名，用于追加和查看 stock_out.csv。
    std::string stockOutFile;
    // 缺库登记记录文件名，用于追加和查看 shortage.csv。
    std::string shortageFile;

    /**
     * @brief 从库存 CSV 文件加载货物数据。
     * @details 构造 WarehouseManager 时自动调用。会逐行解析文件，跳过字段数量错误、
     *          日期非法、编号重复或数值非法的坏数据。
     */
    void loadFromFile();

    /**
     * @brief 将当前库存链表保存到库存 CSV 文件。
     * @details 析构 WarehouseManager 时自动调用，会覆盖写入 warehouse.csv。
     */
    void saveToFile() const;

    /**
     * @brief 显示排序菜单并输出排序后的临时库存视图。
     * @details 支持按编号、单价或数量排序，不改变链表中原始存储顺序。
     */
    void sortGoodsUI() const;

    /**
     * @brief 按用户输入的安全库存阈值筛查低库存货物。
     * @details 找到低库存货物后，可以继续进入缺库登记流程。
     */
    void checkLowStockUI();

    /**
     * @brief 比较两个货物对象的排序顺序。
     * @param a 第一个货物指针。
     * @param b 第二个货物指针。
     * @param type 排序字段：1 表示编号，2 表示单价，3 表示数量。
     * @param isAscending true 表示升序，false 表示降序。
     * @return a 应排在 b 前面时返回 true，否则返回 false。
     */
    static bool compareGoods(const Goods* a, const Goods* b, int type, bool isAscending);

    /**
     * @brief 对货物指针数组执行快速排序。
     * @param arr 指向货物对象的指针数组。
     * @param left 当前排序区间左下标。
     * @param right 当前排序区间右下标。
     * @param type 排序字段：1 表示编号，2 表示单价，3 表示数量。
     * @param isAscending true 表示升序，false 表示降序。
     * @details 只排序指针数组，因此不会移动或修改链表节点本身。
     */
    static void quickSort(const Goods** arr, int left, int right, int type, bool isAscending);

    /**
     * @brief 生成单据编号。
     * @param prefix 单据前缀，例如 "IN"、"OUT"、"SHORT"。
     * @return 带前缀、日期、时间戳和序号的编号字符串。
     * @details 用于入库单、出库单和缺库登记记录。
     */
    std::string generateRecordId(const std::string& prefix) const;

    /**
     * @brief 向指定文件末尾追加一行文本。
     * @param fileName 目标文件名。
     * @param line 要追加的文本内容。
     * @details 三类单据保存函数都会调用该方法。
     */
    void appendLineToFile(const std::string& fileName, const std::string& line) const;

public:
    /**
     * @brief 构造仓库管理器。
     * @details 初始化各个 CSV 文件名，并自动调用 loadFromFile() 加载库存数据。
     */
    WarehouseManager();

    /**
     * @brief 析构仓库管理器。
     * @details 程序退出时自动调用 saveToFile() 保存当前库存数据。
     */
    ~WarehouseManager();

    /**
     * @brief 启动系统主循环。
     * @details 持续显示主菜单并根据用户输入调用对应功能，直到用户选择 0 退出。
     */
    void run();

private:
    /**
     * @brief 打印主菜单。
     * @details 只负责显示菜单文字，不读取用户输入。
     */
    void showMenu() const;

    /**
     * @brief 处理入库登记界面。
     * @details 读取货物信息，校验后加入库存链表，并生成入库单记录。
     */
    void addGoodsUI();

    /**
     * @brief 处理删除货物界面。
     * @details 根据用户输入的货物编号从库存链表中删除对应货物。
     */
    void removeGoodsUI();

    /**
     * @brief 处理货物查询界面。
     * @details 支持编号/名称精确查询、名称/厂家模糊查询、生产日期/入库日期范围查询。
     */
    void queryGoodsUI();

    /**
     * @brief 显示全部库存清单。
     * @details 调用 LinkedList::displayAll() 遍历并输出所有货物。
     */
    void displayAllUI() const;

    /**
     * @brief 处理库存盘点统计界面。
     * @details 支持总量统计、按厂家统计，以及按生产日期或入库日期范围统计。
     */
    void inventoryStatisticsUI() const;

    /**
     * @brief 处理修改货物信息界面。
     * @details 根据货物编号找到原始对象后，更新名称、厂家、日期、单价和数量。
     */
    void modifyGoodsUI();

    /**
     * @brief 处理出库登记界面。
     * @details 校验库存是否足够，扣减库存数量，并生成出库单记录。
     */
    void stockOutUI();

    /**
     * @brief 处理缺库登记界面。
     * @details 当需求数量大于当前库存时，生成缺库登记记录。
     */
    void shortageRegisterUI();

    /**
     * @brief 显示入库单记录。
     * @details 从 stock_in.csv 逐行读取、解析并输出入库单。
     */
    void displayStockInRecordsUI() const;

    /**
     * @brief 显示出库单记录。
     * @details 从 stock_out.csv 逐行读取、解析并输出出库单。
     */
    void displayStockOutRecordsUI() const;

    /**
     * @brief 显示缺库登记记录。
     * @details 从 shortage.csv 逐行读取、解析并输出缺库记录。
     */
    void displayShortageRecordsUI() const;

    /**
     * @brief 保存入库单记录。
     * @param record 要保存的入库单对象。
     * @details 将 record 序列化后追加到入库单文件。
     */
    void saveStockInRecord(const StockInRecord& record) const;

    /**
     * @brief 保存出库单记录。
     * @param record 要保存的出库单对象。
     * @details 将 record 序列化后追加到出库单文件。
     */
    void saveStockOutRecord(const StockOutRecord& record) const;

    /**
     * @brief 保存缺库登记记录。
     * @param record 要保存的缺库登记对象。
     * @details 将 record 序列化后追加到缺库登记文件。
     */
    void saveShortageRecord(const ShortageRecord& record) const;
};

#endif
