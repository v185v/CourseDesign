#include "WarehouseManager.h"
#include <iostream>
#include <string>
#include <fstream>  // 👇 必须引入：用于文件读写
#include <sstream>  // 👇 必须引入：用于解析字符串
#include <vector>

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
        // 调用我们早在 Goods 类里写好的 toCSV() 方法
        file << current->data.toCSV() << "\n"; 
        current = current->next;
    }
    
    file.close(); // 养成好习惯，写完文件随手关门
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
    cout << "  2. 出库/删除 (移除货物)" << endl;
    cout << "  3. 精确查询 (按编号查找)" << endl;
    cout << "  4. 盘点库存 (显示所有货物)" << endl;
    cout << "  0. 退出系统并保存" << endl;
    cout << "=========================================" << endl;
    cout << "请输入您的指令 (0-4): ";
}

void WarehouseManager::run() {
    int choice = -1;

    // 核心引擎：只要不输入 0，就一直循环
    while (choice != 0) {
        showMenu();
        cin >> choice;

        // ⚠️ 经典 C++ 避坑：清理输入缓冲区
        // 当我们输入数字并按回车时，回车符 '\n' 会留在缓冲区里。
        // 如果下面要用 getline 读取字符串，会直接把这个回车当成空字符串读入，导致跳过输入。
        // cin.clear(); 
        // cin.ignore(10000, '\n'); // 清除掉那个讨厌的回车符

        switch (choice) {
        case 1: addGoodsUI(); break;
        case 2: removeGoodsUI(); break;
        case 3: queryGoodsUI(); break;
        case 4: displayAllUI(); break;
        case 0: break; // 退出循环
        default: cout << "❌ 无效的指令，请重新输入！" << endl;
        }
    }
}

// --- 下面是将用户输入转化为链表操作的具体实现 ---

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

void WarehouseManager::removeGoodsUI() {
    string targetId;
    cout << "\n--- [出库/删除] ---" << endl;
    cout << "请输入要删除的货物编号: ";
    cin >> targetId;

    // 调用我们刚才写的删除逻辑
    inventory.removeById(targetId);
}

void WarehouseManager::queryGoodsUI() {
    string targetId;
    cout << "\n--- [精确查询] ---" << endl;
    cout << "请输入要查询的货物编号: ";
    cin >> targetId;

    // 调用我们刚才写的查询逻辑
    inventory.searchById(targetId);
}

void WarehouseManager::displayAllUI() const {
    cout << "\n--- [当前库存清单] ---" << endl;
    inventory.displayAll(); // 调用链表的遍历打印
}