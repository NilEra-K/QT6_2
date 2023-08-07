#include <QApplication>
#include "SumCalculatorDialog.h"

int main(int argc, char** argv) {
    // 创建应用程序对象
    QApplication app(argc, argv);

    // 创建自定义窗口对象
    SumCalculatorDialog sumcalc;

    // 显示窗口
    sumcalc.show();

    // 进入主事件循环
    return app.exec();
}

