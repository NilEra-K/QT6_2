#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnCalc_clicked() {
    int num = ui->spinNum->value();         // 数量
    double price = ui->spinPrice->value();  // 单价
    double total = num * 1.0 * price * 1.0;
    ui->editTotal->setText(QString::number(total, 'f', 2));
}

// 十进制 转换为 其他进制
void Widget::on_btnDecToOther_clicked() {
    int val = ui->spinDec->value();
    ui->spinBin->setValue(val); // 会自动转换
    ui->spinHex->setValue(val);
}

// 二进制 转换为 其他进制
void Widget::on_btnBinToOther_clicked() {
    int val = ui->spinBin->value();
    ui->spinDec->setValue(val);
    ui->spinHex->setValue(val);
}

// 十六进制 转换为 其他进制
void Widget::on_btnHexToOther_clicked() {
    int val = ui->spinHex->value();
    ui->spinBin->setValue(val);
    ui->spinDec->setValue(val);
}

