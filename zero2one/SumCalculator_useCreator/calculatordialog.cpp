#include "calculatordialog.h"
#include "ui_calculatordialog.h"

#include <QDoubleValidator>

CalculatorDialog::CalculatorDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CalculatorDialog)
{
    ui->setupUi(this);
    ui->m_editX->setValidator(new QDoubleValidator(this));
    ui->m_editY->setValidator(new QDoubleValidator(this));
    connect(ui->m_editX, SIGNAL(textChanged(QString)), this, SLOT(enabledButton()));
    connect(ui->m_editY, SIGNAL(textChanged(QString)), this, SLOT(enabledButton()));
}

CalculatorDialog::~CalculatorDialog()
{
    delete ui;
}

void CalculatorDialog::enabledButton(void) {
    bool bOkX, bOkY;
    ui->m_editX->text().toDouble(&bOkX);
    ui->m_editY->text().toDouble(&bOkY);
    ui->m_button->setEnabled(bOkX && bOkY);
}

void CalculatorDialog::on_m_button_clicked() {
    // 从Designer右键控件, 进行 Go To Slot操作
    // 按照这种方式命名的槽函数不需要手动连接
    double res = ui->m_editX->text().toDouble() + ui->m_editY->text().toDouble();
    QString str = QString::number(res);
    ui->m_editANS->setText(str);
}

