#ifndef __SUMCALCULATORDIALOG_H
#define __SUMCALCULATORDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>        // 单行编辑器控件
#include <QHBoxLayOut>      // 水平布局器空间
#include <QDoubleValidator> // 数字验证器

class SumCalculatorDialog : public QDialog {
    Q_OBJECT    // MOC
private:
    QLineEdit* m_editX;
    QLineEdit* m_editY;
    QLineEdit* m_editX;
public:
    SumCalculatorDialog(void);
    ~SumCalculatorDialog();
};

SumCalculatorDialog::SumCalculatorDialog(void) {

}

SumCalculatorDialog::~SumCalculatorDialog()
{
}




#endif // __SUMCALCULATORDIALOG_H