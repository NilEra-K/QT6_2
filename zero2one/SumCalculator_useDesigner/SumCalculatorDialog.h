#ifndef __SUMCALCULATORDIALOG_H
#define __SUMCALCULATORDIALOG_H

#include <QDoubleValidator> // 数字验证器
#include "ui_SumCalculator.h"

// 方法 1: 通过继承方式, 将界面相关代码继承过来直接使用
// class SumCalculatorDialog : public QDialog, public Ui::SumCalculator { ... } 

// 方法 2: 通过组合方式, 添加一个界面类的成员变量(ui), 通过该成员访问界面相关的代码, 实际开发中, 推荐这种方法
class SumCalculatorDialog : public QDialog {
    Q_OBJECT    // MOC, 只要用到信号与槽机制必须加入 Q_OBJECT 宏
public:
    SumCalculatorDialog(void);
    ~SumCalculatorDialog();
private:
    Ui::SumCalculator* ui;  // 方法 2
                            // 将来通过 `ui->成员` 的方式访问界面类的成员
public slots:
    // 计算并显示结果
    void calc(void);

    // 使能 "=" 按钮
    void enabledButton(void);
};

#endif // __SUMCALCULATORDIALOG_H
