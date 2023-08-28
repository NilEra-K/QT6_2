#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);         // 创建数据模型
    model->setRootPath(QDir::currentPath());    // 设置根目录为当前目录
    ui->treeView->setModel(model);              // 为视图控件设置数据模型
    ui->tableView->setModel(model);
    ui->listView->setModel(model);
}

Widget::~Widget()
{
    delete ui;
}

// 点击从 treeView 时, 更新 label 的信息
void Widget::on_treeView_clicked(const QModelIndex &index) {
    ui->chkIsDir->setChecked(model->isDir(index));          // 检测是否为目录
    ui->labelFileName->setText(model->fileName(index));     // 文件名
    ui->labelFilePath->setText(model->filePath(index));     // 文件路径
    ui->labelType->setText(model->type(index));             // 文件类型
    int sz = model->size(index);                            // 文件大小
    if (sz < 1024) {
        ui->labelSize->setText(QString("%1 Byte").arg(sz));   // QString 的一种传参方式, 表示将 sz 传递给编号为 1 的位置 "%1"
    } else if (sz < (1024 * 1024)) {
        ui->labelSize->setText(QString::asprintf("%.1f KB", sz / 1024.0));
    } else {
        ui->labelSize->setText(QString::asprintf("%.1f MB", sz / 1024.0 / 1024.0));
    }
}

