#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 初始化列表
void MainWindow::on_actListInit_triggered() {
    QListWidgetItem* item;                      // 每一行是一个 QListWidgetItem
    QIcon icon(":/icons/check.ico");
    bool chk = ui->chkEditable->isChecked();    // 查看是否可编辑
    ui->listWidget->clear();
    for(int i = 0; i < 10; i++) {
        QString str = QString::asprintf("Item %d", i);
        item = new QListWidgetItem;
        item->setText(str);
        item->setIcon(icon);
        item->setCheckState(Qt::Checked);
        if(chk) {
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
        } else {
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
        }
        ui->listWidget->addItem(item);
    }
}

// 插入项
void MainWindow::on_actItemInsert_triggered() {
    QIcon icon(":/icons/check.ico");
    bool chk = ui->chkEditable->isChecked();
    QListWidgetItem* item = new QListWidgetItem(icon, "New Insert Item");
    item->setCheckState(Qt::Checked);       // 设置为选中状态
    if(chk) {
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
    } else {
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    }
    ui->listWidget->insertItem(ui->listWidget->currentRow(), item);
}

// 添加项
void MainWindow::on_actItemAppend_triggered() {
    QIcon icon(":/icons/check.ico");
    bool chk = ui->chkEditable->isChecked();
    QListWidgetItem* item = new QListWidgetItem(icon, "New Append Item");
    item->setCheckState(Qt::Checked);       // 设置为选中状态
    if(chk) {
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
    } else {
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    }
    ui->listWidget->addItem(item);
}

// 删除当前项
void MainWindow::on_action_triggered() {
    int rowNo = ui->listWidget->currentRow();
    QListWidgetItem* item = ui->listWidget->takeItem(rowNo);
    delete item;
}

// 清除列表
void MainWindow::on_actListClear_triggered() {
    ui->listWidget->clear();
}

// 全选
void MainWindow::on_actSelAll_triggered() {
    int cnt = ui->listWidget->count();      // 获取 listWidget 中的项的数量
    for(int i = 0; i < cnt; i++) {
        QListWidgetItem* item = ui->listWidget->item(i);    // 选中一项
        item->setCheckState(Qt::Checked);                   // 设为选中状态
    }
}

// 全不选
void MainWindow::on_actSelNone_triggered() {
    int cnt = ui->listWidget->count();      // 获取 listWidget 中的项的数量
    for(int i = 0; i < cnt; i++) {
        QListWidgetItem* item = ui->listWidget->item(i);    // 选中一项
        item->setCheckState(Qt::Unchecked);                 // 设为未选中状态
    }
}

// 反选
void MainWindow::on_actSelInvs_triggered() {
    int cnt = ui->listWidget->count();      // 获取 listWidget 中的项的数量
    for(int i = 0; i < cnt; i++) {
        QListWidgetItem* item = ui->listWidget->item(i);    // 选中一项
        if(item->checkState() == Qt::Checked){              // 如果被选中了
            item->setCheckState(Qt::Unchecked);             // 设为未选中状态
        } else if(item->checkState() == Qt::Unchecked) {    // 如果未被选中
            item->setCheckState(Qt::Checked);               // 设为选中状态
        }
    }

}

