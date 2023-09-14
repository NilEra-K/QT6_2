#include "sizedialog.h"
#include "ui_sizedialog.h"
#include <QMessageBox>

SizeDialog::SizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SizeDialog)
{
    ui->setupUi(this);
}

SizeDialog::~SizeDialog()
{
    QMessageBox::information(this, "设置行数列数", "设置行数列数对话框被销毁");
    delete ui;
}

void SizeDialog::setRowColumn(int row, int col) {
    ui->spinRow->setValue(row);
    ui->spinColumn->setValue(col);
}

int SizeDialog::rowCnt() {
    return ui->spinRow->value();
}

int SizeDialog::columnCnt() {
    return ui->spinColumn->value();
}
