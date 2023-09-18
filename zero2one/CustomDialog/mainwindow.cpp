#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sizedialog.h"
#include "locatedialog.h"

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

// 设置单元格文字
void MainWindow::setCellText(int row, int column, QString &text) {
    QModelIndex index = model->index(row, column);
    selection->clearSelection();
    selection->setCurrentIndex(index, QItemSelectionModel::Select);
    model->setData(index, text, Qt::DisplayRole);   // 设置单元格的值
}

// 响应对话框窗口的信号, 设置 actLocate 的使能状态
void MainWindow::setActLocateEnable(bool enable) {
    ui->actLocate->setEnabled(enable);
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

// 当点击 tableView 时, 发射信号, 传递当前单元格的行号和列号
void MainWindow::on_tableView_clicked(const QModelIndex &index) {
    emit cellIndexChanged(index.row(), index.column());
}

// 定位单元格
void MainWindow::on_actLocate_triggered() {
    LocateDialog* dlgLocate = new LocateDialog(this);   // 动态创建
    dlgLocate->setAttribute(Qt::WA_DeleteOnClose);      // 设置属性: 关闭时自动删除, 在关闭时自动删除窗口
    dlgLocate->setWindowFlag(Qt::WindowStaysOnTopHint); // 设置窗口保持顶部显示

    // 设置对话框窗口 spinBox 的最大值
    dlgLocate->setSpinMax(model->rowCount(), model->columnCount());
    QModelIndex index = selection->currentIndex();
    if(index.isValid()) {
        dlgLocate->setSpinValue(index.row(), index.column());
    }
    // 连接信号和槽函数
    // 对话框窗口发射信号, 设置单元格文本
    connect(dlgLocate, SIGNAL(changeCellText(int,int,QString&)), this, SLOT(setCellText(int,int,QString&)));
    // 对话框窗口发射信号, 设置 actLocate 的属性
    connect(dlgLocate, SIGNAL(changeActionEnable(bool)), this, SLOT(setActLocateEnable(bool)));
    // 主窗口发射信号, 更新对话框窗口 spinBox 的值
    connect(this, SIGNAL(cellIndexChanged(int,int)), dlgLocate, SLOT(setSpinValue(int,int)));

    dlgLocate->show();  // 非模态方式显示
}

