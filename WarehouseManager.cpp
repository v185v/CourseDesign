#include "WarehouseManager.h"
#include <iostream>
#include <string>
#include <fstream>  
#include <sstream> 
#include <vector>
#include <iomanip>
#include <ctime>
#include <exception>
#include <map>

using namespace std;

// --- 1. 构造函数与析构函数的修改 ---

WarehouseManager::WarehouseManager()
    : dataFile("warehouse.csv"),
      stockInFile("stock_in.csv"),
      stockOutFile("stock_out.csv"),
      shortageFile("shortage.csv") {
    cout << ">>> 正在初始化仓库系统..." << endl;
    loadFromFile(); // 🌟 系统启动时：自动从文件加载数据
}

WarehouseManager::~WarehouseManager() {
    cout << "\n>>> 正在安全退出系统..." << endl;
    saveToFile();   // 🌟 系统退出时：自动保存数据到文件
}

// --- 2. 实现文件保存功能 (写) ---

void WarehouseManager::saveToFile() const {
    // 创建一个输出文件流，如果文件不存在会自动创建，如果存在会覆盖
    ofstream file(dataFile); 
    
    if (!file.is_open()) {
        cout << "❌ 保存失败：无法打开文件！" << endl;
        return;
    }

    Node* current = inventory.getHead();
    while (current != nullptr) {
        file << current->data.toCSV() << "\n"; 
        current = current->next;
    }
    
    file.close();
    cout << ">>> 数据已成功保存到 [" << dataFile << "]！" << endl;
}

// --- 3. 实现文件读取功能 (读) ---

void WarehouseManager::loadFromFile() {
    ifstream file(dataFile);
    
    if (!file.is_open()) {
        cout << ">>> 未找到本地数据文件，系统将作为一个空仓库启动。" << endl;
        return;
    }

    string line;
    int count = 0; // 记录加载了多少条数据
    
    // 一行一行地读取文件，直到读完
    while (getline(file, line)) {
        if (line.empty()) continue; // 跳过空行

        stringstream ss(line);
        string id, name, mfg, pDateStr, priceStr, qtyStr, sDateStr;

        //用 getline 配合逗号 ',' 来切分字符串
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, mfg, ',');
        getline(ss, pDateStr, ',');
        getline(ss, priceStr, ',');
        getline(ss, qtyStr, ',');
        getline(ss, sDateStr, ',');

        // 恢复数据类型：文本转为数字和 Date 对象
        double price = stod(priceStr); // string to double
        int qty = stoi(qtyStr);        // string to integer
        Date pDate = Date::fromString(pDateStr);
        Date sDate = Date::fromString(sDateStr);

        // 组装成货物对象，重新添加回链表中
        Goods g(id, name, mfg, pDate, price, qty, sDate);
        inventory.add(g);
        count++;
    }

    file.close();
    cout << ">>> 成功加载 " << count << " 条历史货物数据！" << endl;
}


void WarehouseManager::showMenu() const {
    cout << "\n=========================================" << endl;
    cout << "          📦 智能仓库管理系统 📦          " << endl;
    cout << "=========================================" << endl;
    cout << "  1. 入库登记 (添加货物)" << endl;
    cout << "  2. 删除货物档案" << endl;
    cout << "  3. 货物查询 (编号/名称/厂家/日期范围)" << endl;
    cout << "  4. 库存盘点统计" << endl;
    cout << "  5. 货物排序 (按编号/单价/数量)" << endl;
    cout << "  6. 缺货报警 (筛查库存不足货物)" << endl;
    cout << "  7. 修改货物信息" << endl;
    cout << "  8. 出库登记" << endl;
    cout << "  9. 缺库登记" << endl;
    cout << "  10. 查看入库单记录" << endl;
    cout << "  11. 查看出库单记录" << endl;
    cout << "  12. 查看缺库登记记录" << endl;
    cout << "  0. 退出系统并保存" << endl;
    cout << "=========================================" << endl;
    cout << "请输入您的指令 (0-12): ";
}

void WarehouseManager::run() {
    int choice = -1;

    // 核心引擎：只要不输入 0，就一直循环
    while (choice != 0) {
        showMenu();
        cin >> choice;

        // 检查输入流是否崩溃
        if (cin.fail()) {
            // 清除 cin 的错误状态
            cin.clear(); 
            
            // 忽略（丢弃）缓冲区里的多余字符，直到遇到换行符 '\n'
            // 最多丢弃 10000 个字符
            cin.ignore(10000, '\n'); 
            
            cout << "❌ 检测到非法输入（数字过大或包含字母），请重新输入有效选项！" << endl;
            continue;
        }

        switch (choice) {
        case 1: addGoodsUI(); break;
        case 2: removeGoodsUI(); break;
        case 3: queryGoodsUI(); break;
        case 4: inventoryStatisticsUI(); break;
        case 5: sortGoodsUI(); break;
        case 6: checkLowStockUI(); break;
        case 7: modifyGoodsUI(); break;
        case 8: stockOutUI(); break;
        case 9: shortageRegisterUI(); break;
        case 10: displayStockInRecordsUI(); break;
        case 11: displayStockOutRecordsUI(); break;
        case 12: displayShortageRecordsUI(); break;
        case 0: break;
        default: cout << "❌ 无效的指令，请重新输入！" << endl;
        }
    }
}


void WarehouseManager::addGoodsUI() {
    string id, name, mfg, operatorName, remark;
    double price;
    int qty;
    int y, m, d;
    int sy, sm, sd;

    cout << "\n--- [入库登记] ---" << endl;
    cout << "请输入货物编号: "; cin >> id;
    if (id.empty()) {
        cout << "货物编号不能为空，入库失败。" << endl;
        return;
    }

    if (inventory.findById(id) != nullptr) {
        cout << "货物编号已存在，不能重复添加，入库失败。" << endl;
        return;
    }
    cout << "请输入货物名称: "; cin >> name;
    cout << "请输入生产厂家: "; cin >> mfg;
    cout << "请输入单价: "; cin >> price;
    cout << "请输入入库数量: "; cin >> qty;

    cout << "请输入生产日期 (年 月 日，用空格隔开): ";
    cin >> y >> m >> d;
    Date pDate(y, m, d);
        if (!pDate.isValid()) {
        cout << "生产日期不合法，入库失败。" << endl;
        return;
    }

    cout << "请输入入库日期 (年 月 日，用空格隔开): ";
    cin >> sy >> sm >> sd;
    Date sDate(sy, sm, sd);
        if (!sDate.isValid()) {
        cout << "入库日期不合法，入库失败。" << endl;
        return;
    }

    cout << "请输入经办人: "; cin >> operatorName;
    cout << "请输入备注(无备注请输入 none): "; cin >> remark;

    if (price < 0) {
        cout << "货物单价不能为负，入库失败。" << endl;
        return;
    }

    if (qty <= 0) {
        cout << "入库数量必须大于 0，入库失败。" << endl;
        return;
    }

    Goods newGoods(id, name, mfg, pDate, price, qty, sDate);
    inventory.add(newGoods);

    StockInRecord record(generateRecordId("IN"),
                         id,
                         name,
                         qty,
                         price,
                         sDate,
                         operatorName,
                         remark);
    saveStockInRecord(record);

    cout << "✅ 入库成功！" << endl;
}

void WarehouseManager::stockOutUI() {
    string targetId, receiver, operatorName, remark;
    int outQty;
    int y, m, d;

    cout << "\n--- [出库登记] ---" << endl;
    cout << "请输入出库货物编号: ";
    cin >> targetId;
    if (targetId.empty()) {
        cout << "货物编号不能为空，出库失败。" << endl;
        return;
    }

    Goods* goods = inventory.findById(targetId);
    if (goods == nullptr) {
        cout << "未找到编号为 [" << targetId << "] 的货物，出库失败。" << endl;
        return;
    }

    cout << "当前货物信息:" << endl;
    goods->display();

    cout << "请输入出库数量: ";
    cin >> outQty;

    if (outQty <= 0) {
        cout << "出库数量必须大于 0。" << endl;
        return;
    }

    if (outQty > goods->getQuantity()) {
        cout << "库存不足，当前库存为 " << goods->getQuantity() << "，出库失败。" << endl;
        return;
    }

    cout << "请输入出库日期(年 月 日): ";
    cin >> y >> m >> d;
    Date outDate(y, m, d);
    if (!outDate.isValid()) {
        cout << "出库日期不合法，出库失败。" << endl;
        return;
    }

    cout << "请输入领用人/客户: "; cin >> receiver;
    cout << "请输入经办人: "; cin >> operatorName;
    cout << "请输入备注(无备注请输入 none): "; cin >> remark;

    goods->setQuantity(goods->getQuantity() - outQty);
    StockOutRecord record(generateRecordId("OUT"),
                          goods->getId(),
                          goods->getName(),
                          outQty,
                          goods->getPrice(),
                          outDate,
                          receiver,
                          operatorName,
                          remark);
    saveStockOutRecord(record);

    cout << "出库成功，当前剩余库存为 " << goods->getQuantity() << "。" << endl;
}

void WarehouseManager::removeGoodsUI() {
    string targetId;
    cout << "\n--- [出库/删除] ---" << endl;
    cout << "请输入要删除的货物编号: ";
    cin >> targetId;

    inventory.removeById(targetId);
}

// --- 排序辅助：升级版比较规则 ---
bool WarehouseManager::compareGoods(const Goods* a, const Goods* b, int type, bool isAscending) {
    if (type == 1) { // 按编号比较
        return isAscending ? (a->getId() < b->getId()) : (a->getId() > b->getId());
    } else if (type == 2) { // 按单价比较
        return isAscending ? (a->getPrice() < b->getPrice()) : (a->getPrice() > b->getPrice());
    } else if (type == 3) { // 按数量比较
        return isAscending ? (a->getQuantity() < b->getQuantity()) : (a->getQuantity() > b->getQuantity());
    }
    return false;
}

// --- 排序辅助：升级版快速排序算法 ---
void WarehouseManager::quickSort(const Goods** arr, int left, int right, int type, bool isAscending) {
    if (left >= right) return;

    const Goods* pivot = arr[left + (right - left) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        //这里把 isAscending 传给 compareGoods
        while (compareGoods(arr[i], pivot, type, isAscending)) i++;
        while (compareGoods(pivot, arr[j], type, isAscending)) j--;
        
        if (i <= j) {
            const Goods* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    quickSort(arr, left, j, type, isAscending);
    quickSort(arr, i, right, type, isAscending);
}

void WarehouseManager::sortGoodsUI() const {
    cout << "\n--- [货物数据排序 (临时视图)] ---" << endl;
    cout << "  1. 按 编号 排序" << endl;
    cout << "  2. 按 单价 排序" << endl;
    cout << "  3. 按 数量 排序" << endl;
    cout << "请选择排序字段 (1-3): ";
    
    int type;
    cin >> type;

    if (type >= 1 && type <= 3) {
        cout << "  1. 升序 (从小到大)" << endl;
        cout << "  2. 降序 (从大到小)" << endl;
        cout << "请选择排序方向 (1-2): ";
        int orderChoice;
        cin >> orderChoice;
        
        // 如果用户输入1，isAscending 为 true，否则为 false
        bool isAscending = (orderChoice == 1); 

        cout << ">>> 正在生成高速排序视图..." << endl;

        int size = 0;
        Node* current = inventory.getHead();
        while (current != nullptr) {
            size++;
            current = current->next;
        }

        if (size == 0) {
            cout << "❌ 仓库为空，无法排序！" << endl;
            return;
        }

        const Goods** viewArray = new const Goods*[size];

        current = inventory.getHead();
        for (int i = 0; i < size; i++) {
            viewArray[i] = &(current->data);
            current = current->next;
        }

        quickSort(viewArray, 0, size - 1, type, isAscending);

        cout << "\n✅ 排序完成" << endl;
        cout << string(80, '-') << endl;
        for (int i = 0; i < size; i++) {
            viewArray[i]->display();
        }
        cout << string(80, '-') << endl;

        delete[] viewArray; 

    } else {
        cout << "❌ 选择无效，取消排序操作。" << endl;
    }
}

void WarehouseManager::checkLowStockUI() {
    cout << "\n--- [缺货报警系统] ---" << endl;
    cout << "请输入库存安全阈值 (低于该值的货物将被列出): ";
    
    int threshold;
    cin >> threshold;

    cout << ">>> 正在筛查库存低于 " << threshold << " 的货物..." << endl;

    Node* current = inventory.getHead();
    bool found = false; // 用于记录是否找到了缺货商品

    cout << string(80, '-') << endl;
    cout << left << setw(10) << "编号" 
         << setw(15) << "名称" 
         << setw(15) << "厂家" 
         << setw(15) << "生产日期" 
         << setw(10) << "单价" 
         << setw(10) << "数量" 
         << setw(15) << "入库时间" << endl;
    cout << string(80, '-') << endl;

    while (current != nullptr) {
        // 如果当前货物的数量小于用户输入的阈值
        if (current->data.getQuantity() < threshold) {
            current->data.display();
            found = true;          
        }
        current = current->next; 
    }

    if (!found) {
        cout << "✅ 恭喜！当前没有库存低于 " << threshold << " 的货物，库存非常充足！" << endl;
    }
    cout << string(80, '-') << endl;

    if (found) {
        char choice;
        cout << "是否需要登记缺库记录？(y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            shortageRegisterUI();
        }
    }
}

void WarehouseManager::modifyGoodsUI() {
    string targetId;
    cout << "\n--- [修改货物信息] ---" << endl;
    cout << "请输入要修改的货物编号: ";
    cin >> targetId;

    Goods* goods = inventory.findById(targetId);

    if (goods == nullptr) {
        cout << "未找到编号为 [" << targetId << "] 的货物，修改失败。" << endl;
        return;
    }

    cout << "当前货物信息:" << endl;
    goods->display();

    string name, mfg;
    double price;
    int qty;
    int py, pm, pd;
    int sy, sm, sd;

    cout << "请输入新的货物名称: ";
    cin >> name;
    cout << "请输入新的生产厂家: ";
    cin >> mfg;
    cout << "请输入新的生产日期(年 月 日): ";
    cin >> py >> pm >> pd;
    cout << "请输入新的单价: ";
    cin >> price;
    cout << "请输入新的数量: ";
    cin >> qty;
    cout << "请输入新的入库时间(年 月 日): ";
    cin >> sy >> sm >> sd;

    Date productionDate(py, pm, pd);
    Date storageDate(sy, sm, sd);

    if (!productionDate.isValid()) {
        cout << "生产日期不合法，修改失败。" << endl;
        return;
    }

    if (!storageDate.isValid()) {
        cout << "入库日期不合法，修改失败。" << endl;
        return;
    }

    if (price < 0) {
        cout << "货物单价不能为负，修改失败。" << endl;
        return;
    }

    if (qty < 0) {
        cout << "货物数量不能为负，修改失败。" << endl;
        return;
    }
    goods->setName(name);
    goods->setManufacturer(mfg);
    goods->setProductionDate(productionDate);
    goods->setPrice(price);
    goods->setQuantity(qty);
    goods->setStorageDate(storageDate);

    cout << "修改成功。" << endl;
}

void WarehouseManager::queryGoodsUI() {
    int choice;

    cout << "\n--- [货物查询] ---" << endl;
    cout << "  1. 按编号精确查询" << endl;
    cout << "  2. 按名称精确查询" << endl;
    cout << "  3. 按名称模糊查询" << endl;
    cout << "  4. 按厂家模糊查询" << endl;
    cout << "  5. 按生产日期范围查询" << endl;
    cout << "  6. 按入库日期范围查询" << endl;
    cout << "请选择查询方式 (1-6): ";
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "输入无效，查询取消。" << endl;
        return;
    }

    string keyword;
    int startY, startM, startD;
    int endY, endM, endD;
    Date startDate;
    Date endDate;
    bool found = false;

    switch (choice) {
    case 1:
        cout << "请输入货物编号: ";
        cin >> keyword;
        break;
    case 2:
        cout << "请输入货物名称: ";
        cin >> keyword;
        break;
    case 3:
        cout << "请输入货物名称关键字: ";
        cin >> keyword;
        break;
    case 4:
        cout << "请输入生产厂家关键字: ";
        cin >> keyword;
        break;
    case 5:
        cout << "请输入起始生产日期 (年 月 日): ";
        cin >> startY >> startM >> startD;
        cout << "请输入结束生产日期 (年 月 日): ";
        cin >> endY >> endM >> endD;
        startDate = Date(startY, startM, startD);
        endDate = Date(endY, endM, endD);
        break;
    case 6:
        cout << "请输入起始入库日期 (年 月 日): ";
        cin >> startY >> startM >> startD;
        cout << "请输入结束入库日期 (年 月 日): ";
        cin >> endY >> endM >> endD;
        startDate = Date(startY, startM, startD);
        endDate = Date(endY, endM, endD);
        break;
    default:
        cout << "查询方式无效，查询取消。" << endl;
        return;
    }

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "输入无效，查询取消。" << endl;
        return;
    }

    int startNumber = startDate.toNumber();
    int endNumber = endDate.toNumber();

    cout << string(80, '-') << endl;
    cout << left << setw(10) << "编号"
         << setw(15) << "名称"
         << setw(15) << "厂家"
         << setw(15) << "生产日期"
         << setw(10) << "单价"
         << setw(10) << "数量"
         << setw(15) << "入库时间" << endl;
    cout << string(80, '-') << endl;

    Node* current = inventory.getHead();
    while (current != nullptr) {
        const Goods& goods = current->data;
        bool matched = false;

        switch (choice) {
        case 1:
            matched = (goods.getId() == keyword);
            break;
        case 2:
            matched = (goods.getName() == keyword);
            break;
        case 3:
            matched = (goods.getName().find(keyword) != string::npos);
            break;
        case 4:
            matched = (goods.getManufacturer().find(keyword) != string::npos);
            break;
        case 5:
            matched = (goods.getProductionDate().toNumber() >= startNumber &&
                       goods.getProductionDate().toNumber() <= endNumber);
            break;
        case 6:
            matched = (goods.getStorageDate().toNumber() >= startNumber &&
                       goods.getStorageDate().toNumber() <= endNumber);
            break;
        }

        if (matched) {
            goods.display();
            found = true;
        }

        current = current->next;
    }

    if (!found) {
        cout << "未找到符合条件的货物信息。" << endl;
    }

    cout << string(80, '-') << endl;
}

void WarehouseManager::displayAllUI() const {
    cout << "\n--- [当前库存清单] ---" << endl;
    inventory.displayAll(); // 调用链表的遍历打印
}

void WarehouseManager::inventoryStatisticsUI() const {
    int choice = -1;

    while (choice != 0) {
        cout << "\n--- [库存盘点统计] ---" << endl;
        cout << "  1. 显示所有库存清单" << endl;
        cout << "  2. 库存总体统计" << endl;
        cout << "  3. 按厂家统计" << endl;
        cout << "  4. 按入库日期范围统计" << endl;
        cout << "  5. 按生产日期范围统计" << endl;
        cout << "  0. 返回主菜单" << endl;
        cout << "请选择盘点方式 (0-5): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "输入无效，请重新选择。" << endl;
            continue;
        }

        if (choice != 0 && inventory.getHead() == nullptr) {
            cout << "当前仓库为空，无法盘点。" << endl;
            continue;
        }

        switch (choice) {
        case 1:
            displayAllUI();
            break;
        case 2: {
            int kinds = 0;
            int totalQuantity = 0;
            double totalValue = 0;
            const Goods* maxQuantityGoods = nullptr;
            const Goods* minQuantityGoods = nullptr;
            const Goods* maxValueGoods = nullptr;

            Node* current = inventory.getHead();
            while (current != nullptr) {
                const Goods& goods = current->data;
                double value = goods.getPrice() * goods.getQuantity();

                kinds++;
                totalQuantity += goods.getQuantity();
                totalValue += value;

                if (maxQuantityGoods == nullptr || goods.getQuantity() > maxQuantityGoods->getQuantity()) {
                    maxQuantityGoods = &goods;
                }
                if (minQuantityGoods == nullptr || goods.getQuantity() < minQuantityGoods->getQuantity()) {
                    minQuantityGoods = &goods;
                }
                if (maxValueGoods == nullptr || value > maxValueGoods->getPrice() * maxValueGoods->getQuantity()) {
                    maxValueGoods = &goods;
                }

                current = current->next;
            }

            cout << "\n--- [库存总体统计] ---" << endl;
            cout << fixed << setprecision(2);
            cout << "货物种类数: " << kinds << endl;
            cout << "库存总数量: " << totalQuantity << endl;
            cout << "库存总金额: " << totalValue << endl;
            cout << "平均单价: " << (totalQuantity == 0 ? 0 : totalValue / totalQuantity) << endl;

            if (maxQuantityGoods != nullptr) {
                cout << "库存数量最多: " << maxQuantityGoods->getName()
                     << " (" << maxQuantityGoods->getQuantity() << ")" << endl;
            }
            if (minQuantityGoods != nullptr) {
                cout << "库存数量最少: " << minQuantityGoods->getName()
                     << " (" << minQuantityGoods->getQuantity() << ")" << endl;
            }
            if (maxValueGoods != nullptr) {
                cout << "库存金额最高: " << maxValueGoods->getName()
                     << " (" << maxValueGoods->getPrice() * maxValueGoods->getQuantity() << ")" << endl;
            }
            break;
        }
        case 3: {
            struct Statistics {
                int kinds;
                int quantity;
                double value;
                Statistics() : kinds(0), quantity(0), value(0) {}
            };

            map<string, Statistics> statistics;
            Node* current = inventory.getHead();
            while (current != nullptr) {
                const Goods& goods = current->data;
                string manufacturer = goods.getManufacturer().empty() ? "未填写" : goods.getManufacturer();
                Statistics& item = statistics[manufacturer];
                item.kinds++;
                item.quantity += goods.getQuantity();
                item.value += goods.getPrice() * goods.getQuantity();
                current = current->next;
            }

            cout << "\n--- [按厂家统计] ---" << endl;
            cout << fixed << setprecision(2);
            cout << string(70, '-') << endl;
            cout << left << setw(20) << "厂家"
                 << setw(12) << "种类数"
                 << setw(14) << "库存数量"
                 << setw(16) << "库存金额" << endl;
            cout << string(70, '-') << endl;

            map<string, Statistics>::const_iterator it;
            for (it = statistics.begin(); it != statistics.end(); ++it) {
                cout << left << setw(20) << it->first
                     << setw(12) << it->second.kinds
                     << setw(14) << it->second.quantity
                     << setw(16) << it->second.value << endl;
            }
            cout << string(70, '-') << endl;
            break;
        }
        case 4:
        case 5: {
            int startY, startM, startD;
            int endY, endM, endD;
            int kinds = 0;
            int totalQuantity = 0;
            double totalValue = 0;
            bool found = false;
            bool byStorageDate = (choice == 4);

            cout << "请输入起始日期 (年 月 日): ";
            cin >> startY >> startM >> startD;
            cout << "请输入结束日期 (年 月 日): ";
            cin >> endY >> endM >> endD;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "日期输入无效，统计取消。" << endl;
                break;
            }

            Date startDate(startY, startM, startD);
            Date endDate(endY, endM, endD);

            if (!startDate.isValid() || !endDate.isValid()) {
                cout << "日期不合法，统计取消。" << endl;
                break;
            }

            if (startDate.toNumber() > endDate.toNumber()) {
                cout << "起始日期不能晚于结束日期，统计取消。" << endl;
                break;
            }

            cout << (byStorageDate ? "\n--- [按入库日期范围统计] ---" : "\n--- [按生产日期范围统计] ---") << endl;
            cout << string(80, '-') << endl;
            cout << left << setw(10) << "编号"
                 << setw(15) << "名称"
                 << setw(15) << "厂家"
                 << setw(15) << "生产日期"
                 << setw(10) << "单价"
                 << setw(10) << "数量"
                 << setw(15) << "入库时间" << endl;
            cout << string(80, '-') << endl;

            Node* current = inventory.getHead();
            while (current != nullptr) {
                const Goods& goods = current->data;
                Date targetDate = byStorageDate ? goods.getStorageDate() : goods.getProductionDate();

                if (targetDate.toNumber() >= startDate.toNumber() &&
                    targetDate.toNumber() <= endDate.toNumber()) {
                    goods.display();
                    kinds++;
                    totalQuantity += goods.getQuantity();
                    totalValue += goods.getPrice() * goods.getQuantity();
                    found = true;
                }

                current = current->next;
            }

            if (!found) {
                cout << "没有找到符合日期范围的货物。" << endl;
            }

            cout << string(80, '-') << endl;
            cout << fixed << setprecision(2);
            cout << "统计种类数: " << kinds << endl;
            cout << "统计库存数量: " << totalQuantity << endl;
            cout << "统计库存金额: " << totalValue << endl;
            break;
        }
        case 0:
            break;
        default:
            cout << "无效的盘点方式，请重新选择。" << endl;
        }
    }
}

void WarehouseManager::shortageRegisterUI() {
    string targetId, status, remark;
    int requiredQty;
    int y, m, d;

    cout << "\n--- [缺库登记] ---" << endl;
    cout << "请输入缺库货物编号: ";
    cin >> targetId;

    Goods* goods = inventory.findById(targetId);
    if (goods == nullptr) {
        cout << "未找到编号为 [" << targetId << "] 的货物，缺库登记失败。" << endl;
        return;
    }

    cout << "当前货物信息:" << endl;
    goods->display();

    cout << "请输入需求数量或安全库存数量: ";
    cin >> requiredQty;
    if (requiredQty <= 0) {
        cout << "需求数量必须大于 0，缺库登记失败。" << endl;
        return;
    }

    if (requiredQty <= goods->getQuantity()) {
        cout << "当前库存未低于需求数量，无需登记缺库。" << endl;
        return;
    }

    cout << "请输入登记日期(年 月 日): ";
    cin >> y >> m >> d;
    Date registerDate(y, m, d);
    if (!registerDate.isValid()) {
        cout << "登记日期不合法，缺库登记失败。" << endl;
        return;
    }
    cout << "请输入状态(如 未处理/已采购/已完成): ";
    cin >> status;
    cout << "请输入备注(无备注请输入 none): ";
    cin >> remark;
    

    ShortageRecord record(generateRecordId("SHORT"),
                          goods->getId(),
                          goods->getName(),
                          goods->getQuantity(),
                          requiredQty,
                          requiredQty - goods->getQuantity(),
                          registerDate,
                          status,
                          remark);
    saveShortageRecord(record);

    cout << "缺库登记成功。" << endl;
}

void WarehouseManager::displayStockInRecordsUI() const {
    ifstream file(stockInFile);
    if (!file.is_open()) {
        cout << "暂无入库单记录。" << endl;
        return;
    }

    cout << "\n--- [入库单记录] ---" << endl;
    cout << left
         << setw(30) << "入库单号"
         << setw(20) << "货物编号"
         << setw(20) << "货物名称"
         << setw(14) << "数量"
         << setw(10) << "单价"
         << setw(16) << "入库日期"
         << setw(18) << "经办人"
         << setw(20) << "备注" << endl;
    cout << string(126, '-') << endl;

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            try {
                StockInRecord::fromCSV(line).display();
            } catch (const exception&) {
                cout << "跳过无法解析的入库单记录: " << line << endl;
            }
        }
    }
}

void WarehouseManager::displayStockOutRecordsUI() const {
    ifstream file(stockOutFile);
    if (!file.is_open()) {
        cout << "暂无出库单记录。" << endl;
        return;
    }

    cout << "\n--- [出库单记录] ---" << endl;
    cout << left
         << setw(30) << "出库单号"
         << setw(20) << "货物编号"
         << setw(20) << "货物名称"
         << setw(14) << "数量"
         << setw(10) << "单价"
         << setw(16) << "出库日期"
         << setw(18) << "领用人"
         << setw(18) << "经办人"
         << setw(20) << "备注" << endl;
    cout << string(140, '-') << endl;

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            try {
                StockOutRecord::fromCSV(line).display();
            } catch (const exception&) {
                cout << "跳过无法解析的出库单记录: " << line << endl;
            }
        }
    }
}

void WarehouseManager::displayShortageRecordsUI() const {
    ifstream file(shortageFile);
    if (!file.is_open()) {
        cout << "暂无缺库登记记录。" << endl;
        return;
    }

    cout << "\n--- [缺库登记记录] ---" << endl;
    cout << left
         << setw(30) << "登记编号"
         << setw(20) << "货物编号"
         << setw(20) << "货物名称"
         << setw(14) << "当前库存"
         << setw(14) << "需求数量"
         << setw(14) << "缺少数量"
         << setw(16) << "登记日期"
         << setw(14) << "状态"
         << setw(20) << "备注" << endl;
    cout << string(134, '-') << endl;

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            try {
                ShortageRecord::fromCSV(line).display();
            } catch (const exception&) {
                cout << "跳过无法解析的缺库登记记录: " << line << endl;
            }
        }
    }
}

void WarehouseManager::saveStockInRecord(const StockInRecord& record) const {
    appendLineToFile(stockInFile, record.toCSV());
}

void WarehouseManager::saveStockOutRecord(const StockOutRecord& record) const {
    appendLineToFile(stockOutFile, record.toCSV());
}

void WarehouseManager::saveShortageRecord(const ShortageRecord& record) const {
    appendLineToFile(shortageFile, record.toCSV());
}

void WarehouseManager::appendLineToFile(const std::string& fileName, const std::string& line) const {
    ofstream file(fileName, ios::app);

    if (!file.is_open()) {
        cout << "记录保存失败：无法打开 " << fileName << endl;
        return;
    }

    file << line << "\n";
}

std::string WarehouseManager::generateRecordId(const std::string& prefix) const {
    static int sequence = 0;
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    string dateText = "unknown-date";

    if (localTime != nullptr) {
        Date today(localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday);
        dateText = today.toString();
    }

    sequence++;
    return prefix + "-" + dateText + "-" + std::to_string(now) + "-" + std::to_string(sequence);
}
