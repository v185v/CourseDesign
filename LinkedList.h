#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Goods.h"
#include <string>

/**
 * @brief 单链表节点。
 * @details 每个节点保存一个货物对象，并通过 next 指针连接到下一个节点。
 */
struct Node {
    // 当前节点保存的货物数据。
    Goods data;
    // 指向下一个节点的指针；如果为 nullptr，表示当前节点是链表尾部。
    Node* next;

    /**
     * @brief 使用货物对象构造一个链表节点。
     * @param g 要保存到节点中的货物对象。
     * @details 新节点默认没有下一个节点，因此 next 初始化为 nullptr。
     */
    Node(const Goods& g) : data(g), next(nullptr) {}
};

/**
 * @brief 保存库存货物的单链表。
 * @details WarehouseManager 使用该链表作为内存中的库存容器，支持新增、删除、查找和遍历显示。
 */
class LinkedList {
private:
    // 链表头指针，指向第一件货物所在节点；为空时表示仓库没有货物。
    Node* head;

public:
    /**
     * @brief 构造空链表。
     * @details 初始时 head 为 nullptr，表示没有任何货物节点。
     */
    LinkedList();

    /**
     * @brief 析构链表并释放所有节点。
     * @details 调用 clear() 逐个 delete 节点，避免内存泄漏。
     */
    ~LinkedList();

    /**
     * @brief 在链表尾部追加货物。
     * @param g 要加入库存链表的货物对象。
     * @details 入库和文件加载时使用该方法把货物放入内存库存。
     */
    void add(const Goods& g);

    /**
     * @brief 清空链表。
     * @details 删除所有节点，并把 head 更新为空指针。
     */
    void clear();

    /**
     * @brief 获取链表头指针。
     * @return 返回第一个节点地址；链表为空时返回 nullptr。
     * @details WarehouseManager 需要遍历库存、保存文件和统计时使用该方法。
     */
    Node* getHead() const { return head; }

    /**
     * @brief 按货物编号查找并显示货物。
     * @param targetId 要查找的货物编号。
     * @return 找到时返回 true，否则返回 false。
     * @details 该方法会直接打印查找结果，适合简单查询场景。
     */
    bool searchById(const std::string& targetId) const;

    /**
     * @brief 按货物编号删除节点。
     * @param targetId 要删除的货物编号。
     * @return 删除成功时返回 true，否则返回 false。
     * @details 会正确处理删除头节点、中间节点和未找到的情况。
     */
    bool removeById(const std::string& targetId);

    /**
     * @brief 按货物编号返回货物对象指针。
     * @param targetId 要查找的货物编号。
     * @return 找到时返回 Goods 对象地址，未找到时返回 nullptr。
     * @details 返回指针是为了让修改、出库等功能可以直接更新链表中的原始货物数据。
     */
    Goods* findById(const std::string& targetId);

    /**
     * @brief 显示链表中的全部货物。
     * @details 以表格形式遍历并输出所有库存货物。
     */
    void displayAll() const;
};

#endif
