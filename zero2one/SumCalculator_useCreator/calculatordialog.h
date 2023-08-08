#ifndef CALCULATORDIALOG_H
#define CALCULATORDIALOG_H

#include <QDialog>

// #include "ui_CalculatorDialog.h"
// 短式声明, 或称前置声明, CalculatorDialog 类在 ui_CalculatorDialog.h
// 使用 Ui::CalculatorDialog 需要包含该头文件, 但是没有编译之前我们无法获取该头文件
// 因此此处采用短式声明的方式, 告诉编译器拥有该类
QT_BEGIN_NAMESPACE
namespace Ui { class CalculatorDialog; }
QT_END_NAMESPACE

class CalculatorDialog : public QDialog
{
    Q_OBJECT

public:
    CalculatorDialog(QWidget *parent = nullptr);
    ~CalculatorDialog();    
public slots:
    // 使能等号按钮
    void enabledButton(void);
private slots:
    void on_m_button_clicked();

private:
    Ui::CalculatorDialog *ui;
};
#endif // CALCULATORDIALOG_H
