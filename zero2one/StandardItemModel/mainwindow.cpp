#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);

    model = new QStandardItemModel(2, COLUMNCOUNT, this);   // 创建一个 2 行 COLUMNCOUNT 列的标准项模型
    selection = new QItemSelectionModel(model);             // 创建选择模型, 选择模型不能单独使用, 需要作为一个模型的 "选择模型"
    ui->tableView->setModel(model);                         // 设置数据模型
    ui->tableView->setSelectionModel(selection);            // 设置选择模型
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);  // 设置选择模式, 参数为一个枚举值
                                                                            // ExtendedSelection 是符合人们日常使用的操作方式
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);    // 设置选择行为, 参数为一个枚举值
                                                                            // SelectionItems - 选择单个项目
                                                                            // SelectionRows - 选择一整行
                                                                            // SelectionColumns - 选择一整列
    initUi();   // 初始化状态栏

    // 连接信号与槽
    connect(selection, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(on_CurrentChanged(QModelIndex, QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 初始化状态栏
void MainWindow::initUi(void) {
    labelCurFile = new QLabel("当前文件 : ");
    labelCurFile->setMinimumWidth(400);
    ui->statusbar->addWidget(labelCurFile);

    labelCellPos = new QLabel("当前单元格 : ");
    labelCellPos->setMinimumWidth(200);
    ui->statusbar->addWidget(labelCellPos);

    labelCellText = new QLabel("单元格文本");
    labelCellText->setMinimumWidth(200);
    ui->statusbar->addWidget(labelCellText);
}

// 当选中的单元格发生变化时
void MainWindow::on_CurrentChanged(const QModelIndex& current, const QModelIndex& previous) {
    Q_UNUSED(previous);
    if(current.isValid()) {
        labelCellPos->setText(QString::asprintf("当前单元格 : %d 行, %d 列", current.row(), current.column()));
        QStandardItem* item = model->itemFromIndex(current);
        labelCellText->setText("单元格文本 : " + item->text());
        QFont font = item->font();
        ui->actBold->setCheckable(font.bold());
    }
}

// 打开
void MainWindow::on_actOpen_triggered() {
    QString curPath = QCoreApplication::applicationDirPath();
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", curPath, "学生信息文件(*.txt);;所有文件(*.*)"); // 使用两个分号隔开, 可以设置所需多个不同的文件类型
    if(fileName.isEmpty()) {
        return;
    }
    QStringList fileContent;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) { // 打开文件
        QTextStream stream(&file);                  // 用文本流读取文件
        stream.setEncoding(QStringConverter::Utf8); // 在 QT6 中, setCodec() 方法已经被弃用
                                                    // 使用 setEncoding(QStringConverter::Encoding)
        ui->plainTextEdit->clear();
        while(!stream.atEnd()) { // 当读取位置未到达文件尾时
            QString str = stream.readLine();
            ui->plainTextEdit->appendPlainText(str);
            fileContent.append(str);
        }
        file.close();
        labelCurFile->setText("当前文件 : " + fileName);    // 状态栏显示
        initModelFromStringList(fileContent);   // 调用 initModelFromStringList() 函数
    }
}

// 使用 StringList 数据, 初始化模型
void MainWindow::initModelFromStringList(QStringList& fileContent) {
    int rowCnt = fileContent.count();   // 文本行数, 第一行是表头
    model->setRowCount(rowCnt - 1);
    // 设置表头
}
