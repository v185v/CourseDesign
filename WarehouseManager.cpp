#include "WarehouseManager.h"
#include <iostream>
#include <string>
#include <fstream>  
#include <sstream> 
#include <vector>
#include <iomanip>

using namespace std;

// --- 1. 构造函数与析构函数的修改 ---

WarehouseManager::WarehouseManager() : dataFile("warehouse.csv") {
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

        // 🌟 核心技巧：用 getline 配合逗号 ',' 来切分字符串
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
    cout << "  3. 精确查询 (按编号查找)" << endl;
    cout << "  4. 盘点库存 (显示所有货物)" << endl;
    cout << "  5. 货物排序 (按编号/单价/数量)" << endl;
    cout << "  6. 缺货报警 (筛查库存不足货物)" << endl;
    cout << "  7. 修改货物信息" << endl;
    cout << "  8. 出库登记" << endl;
    cout << "  0. 退出系统并保存" << endl;
    cout << "=========================================" << endl;
    cout << "请输入您的指令 (0-8): ";
}

void WarehouseManager::run() {
    int choice = -1;

    // 核心引擎：只要不输入 0，就一直循环
    while (choice != 0) {
        showMenu();
        cin >> choice;

        // 新增防御机制：检查输入流是否崩溃
        if (cin.fail()) {
            // 清除 cin 的罢工错误状态
            cin.clear(); 
            
            // 忽略（丢弃）缓冲区里的多余字符，直到遇到换行符 '\n'
            // 10000 是一个足够大的数字，代表最多丢弃 10000 个字符
            cin.ignore(10000, '\n'); 
            
            cout << "❌ 检测到非法输入（数字过大或包含字母），请重新输入有效选项！" << endl;
            continue;
        }

        switch (choice) {
        case 1: addGoodsUI(); break;
        case 2: removeGoodsUI(); break;
        case 3: queryGoodsUI(); break;
        case 4: displayAllUI(); break;
        case 5: sortGoodsUI(); break;
        case 6: checkLowStockUI(); break;
        case 7: modifyGoodsUI(); break;
        case 8: stockOutUI(); break;
        case 0: break;
        default: cout << "❌ 无效的指令，请重新输入！" << endl;
        }
    }
}


void WarehouseManager::addGoodsUI() {
    string id, name, mfg;
    double price;
    int qty;
    int y, m, d;

    cout << "\n--- [入库登记] ---" << endl;
    cout << "请输入货物编号: "; cin >> id;
    cout << "请输入货物名称: "; cin >> name;
    cout << "请输入生产厂家: "; cin >> mfg;
    cout << "请输入单价: "; cin >> price;
    cout << "请输入入库数量: "; cin >> qty;

    cout << "请输入生产日期 (年 月 日，用空格隔开): ";
    cin >> y >> m >> d;
    Date pDate(y, m, d);

    // 假设入库时间就是今天 (为了简化，这里先固定一个时间，后续可改)
    Date sDate(2024, 5, 20);

    // 组装成 Goods 对象，并交给链表
    Goods newGoods(id, name, mfg, pDate, price, qty, sDate);
    inventory.add(newGoods);

    cout << "✅ 入库成功！" << endl;
}

void WarehouseManager::stockOutUI() {
    string targetId;
    int outQty;
    int y, m, d;

    cout << "\n--- [出库登记] ---" << endl;
    cout << "请输入出库货物编号: ";
    cin >> targetId;

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

    goods->setQuantity(goods->getQuantity() - outQty);
    saveStockOutRecord(targetId, outQty, outDate);

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
        // 👇 这里把 isAscending 传给 compareGoods
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

void WarehouseManager::checkLowStockUI() const {
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
            current->data.display(); // 打印这件货物
            found = true;            // 标记为已找到
        }
        current = current->next;     // 巡视员走向下一节车厢
    }

    // 如果整个仓库都没有缺货商品，给出积极提示
    if (!found) {
        // 使用回车符覆盖刚才的表头内部，保持界面整洁
        cout << "✅ 恭喜！当前没有库存低于 " << threshold << " 的货物，库存非常充足！" << endl;
    }
    cout << string(80, '-') << endl;
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

    goods->setName(name);
    goods->setManufacturer(mfg);
    goods->setProductionDate(Date(py, pm, pd));
    goods->setPrice(price);
    goods->setQuantity(qty);
    goods->setStorageDate(Date(sy, sm, sd));

    cout << "修改成功。" << endl;
}

void WarehouseManager::queryGoodsUI() {
    string targetId;
    cout << "\n--- [精确查询] ---" << endl;
    cout << "请输入要查询的货物编号: ";
    cin >> targetId;

    inventory.searchById(targetId);
}

void WarehouseManager::displayAllUI() const {
    cout << "\n--- [当前库存清单] ---" << endl;
    inventory.displayAll(); // 调用链表的遍历打印
}

void WarehouseManager::saveStockOutRecord(
    const std::string& goodsId,
    int quantity,
    const Date& outDate
) const {
    ofstream file("stock_out.csv", ios::app);

    if (!file.is_open()) {
        cout << "出库记录保存失败：无法打开 stock_out.csv" << endl;
        return;
    }

    file << goodsId << ","
         << quantity << ","
         << outDate.toString() << "\n";

    file.close();
}