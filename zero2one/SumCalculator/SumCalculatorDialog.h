#ifndef __SUMCALCULATORDIALOG_H
#define __SUMCALCULATORDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>        // 单行编辑器控件
#include <QHBoxLayOut>      // 水平布局器空间
#include <QDoubleValidator> // 数字验证器

class SumCalculatorDialog : public QDialog {
    Q_OBJECT    // MOC, 只要用到信号与槽机制必须加入 Q_OBJECT 宏
private:
    QLineEdit* m_editX;     // 左操作数
    QLineEdit* m_editY;     // 右操作数
    QLineEdit* m_editANS;   // 结果
    QLabel* m_plus;         // "+"
    QPushButton* m_equal;   // "="
public:
    SumCalculatorDialog(void);
    ~SumCalculatorDialog();
public slots:
    // 计算并显示结果
    void calc(void);

    // 使能 "=" 按钮
    void enabledButton(void);
};

#endif // __SUMCALCULATORDIALOG_H
