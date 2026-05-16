#include "WarehouseManager.h"
#include <cstdlib>

int main() {
    // 强行将 Windows 控制台的编码切换为 UTF-8 (代号 65001)
    system("chcp 65001");
    
    // 实例化系统管理者
    WarehouseManager app;

    // 启动系统！
    app.run();

    return 0;
}