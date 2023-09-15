#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sizedialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tableView);

    model = new QStandardItemModel(5, 4, this);
    selection = new QItemSelectionModel(model);
    ui->tableView->setModel(model);                 // 设置数据模型
    ui->tableView->setSelectionModel(selection);    // 设置选择模型
}

MainWindow::~MainWindow()
{
    delete ui;
}

// "设置行数列数"
void MainWindow::on_actSetSize_triggered() {
    // 动态创建
    SizeDialog* dlgSize = new SizeDialog(this);
    dlgSize->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    // dlgSize->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);  // 对话框窗口大小固定
    dlgSize->setRowColumn(model->rowCount(), model->columnCount());

    // 模态显示
    int ret = dlgSize->exec();
    if (ret == QDialog::Accepted) { // 确定按钮被点击
        int row = dlgSize->rowCnt();
        int col = dlgSize->columnCnt();
        model->setRowCount(row);
        model->setColumnCount(col);
    }
    delete dlgSize;
    dlgSize = nullptr;
}

// 设置表头标题, 该对话框在父窗口存续期间只创建一次
void MainWindow::on_actSetHeader_triggered() {
    // 只创建一次
    if(dlgHeader == NULL) {
        dlgHeader = new HeaderDialog(this);
    }
    if(dlgHeader->headerList().count() != model->columnCount()) { // 表头列数有变化
        QStringList strList;
        for(int i = 0; i < model->columnCount(); i++) { // 将已有 columnCount 的表头进行插入 QStringList
            strList.append(model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        }
        dlgHeader->setHeaderList(strList);  // 初始化对话框中的 listView
    }
    // 模态方式显示
    int ret = dlgHeader->exec();
    if(ret == QDialog::Accepted) { // 当按下接收按钮
        QStringList tmpList = dlgHeader->headerList();
        model->setHorizontalHeaderLabels(tmpList);
    }
}

