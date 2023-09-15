#include "headerdialog.h"
#include "ui_headerdialog.h"
#include <QMessageBox>

HeaderDialog::HeaderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HeaderDialog)
{
    ui->setupUi(this);
    headerModel = new QStringListModel(this);
    ui->listView->setModel(headerModel);
}

HeaderDialog::~HeaderDialog() {
    QMessageBox::information(this, "设置表头", "设置表头标题窗口被销毁");
    delete ui;
}

// 初始化对话框窗口的 listView
void HeaderDialog::setHeaderList(QStringList &headers) {
    headerModel->setStringList(headers);
}

// 返回字符串列表
QStringList HeaderDialog::headerList() {
    return headerModel->stringList();
}
