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

    // 调用 QFileDialog::getOpenFileName() 函数, 弹出文件选择窗口, 进行文件选择
    // 使用两个分号隔开, 可以设置所需多个不同的文件类型
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", curPath, "学生信息文件(*.txt);;所有文件(*.*)");
    if(fileName.isEmpty()) {
        return;
    }
    QStringList fileContent;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) { // 打开文件
        QTextStream stream(&file);                  // 用文本流读取文件
        stream.setEncoding(QStringConverter::Utf8); // 在 QT6 中, setCodec() 方法已经被弃用
                                                    // 使用 setEncoding(QStringConverter::Encoding), 设置打开文件字符集格式
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
    QString header = fileContent.at(0); // 学号 姓名 出生日期 性别 联系方式
    // QT 5 中的方法, 在 QT 6中已经无法使用 QRegExp 类, 且用 QRegularExpression 类无法替代
    // QStringList headerList = header.split(QRegularExpression("\\s+"), QString::SectionSkipEmpty);
    // 这里设置以空格分割会报错, 因此修改为以 '\t' 分割
    QStringList headerList = header.split(QLatin1Char('\t'), Qt::SkipEmptyParts);
    model->setHorizontalHeaderLabels(headerList);

    // 设置内容
    QStandardItem* item;
    QStringList tmpList;
    for(int i = 1; i < rowCnt; i++) {
        QString lineText = fileContent.at(i);
        tmpList = lineText.split(QLatin1Char('\t'), Qt::SkipEmptyParts);
        for(int j = 0; j < COLUMNCOUNT; j++){
            item = new QStandardItem(tmpList.at(j));
            model->setItem(i-1, j, item);   // 为模型的某个行列位置设置 item
        }
    }
}

// 添加行
void MainWindow::on_actAppend_triggered() {
    QList<QStandardItem*> itemList;     // 创建一个项的列表
    QStandardItem* item;
    for(int i = 0; i < COLUMNCOUNT; i++) {
        item = new QStandardItem("");   // 创建 item
        itemList << item;
    }
    model->insertRow(model->rowCount(), itemList);  // 再尾端插入一行
    QModelIndex index = model->index(model->rowCount()-1, 0);
    selection->clearSelection();
    selection->setCurrentIndex(index, QItemSelectionModel::Select);
}

// 插入行
void MainWindow::on_actInsert_triggered() {
    QList<QStandardItem*> itemList;
    QStandardItem* item;
    for(int i = 0; i < COLUMNCOUNT; i++) {
        item = new QStandardItem("");
        itemList << item;
    }
    QModelIndex index = selection->currentIndex();
    model->insertRow(index.row(), itemList);
    selection->clearSelection();
    selection->setCurrentIndex(index, QItemSelectionModel::Select);
}

// 删除一行
void MainWindow::on_actDelete_triggered() {
    QModelIndex index = selection->currentIndex();
    if(index.row() == model->rowCount() - 1) { // 如果是最后一行
        model->removeRow(index.row());         // 删除一行
    } else {
        model->removeRow(index.row());
        selection->setCurrentIndex(index, QItemSelectionModel::Select);
    }
}

// 居左
void MainWindow::on_actAlignLeft_triggered() {
    if (!selection->hasSelection()){ // 如果未选中
        return;
    }

    // 获取选择的单元的模型索引, 可以是多选
    QModelIndexList selectedIndexes = selection->selectedIndexes();
    for(int i = 0; i < selectedIndexes.count(); i++) {
        QModelIndex index = selectedIndexes.at(i);
        QStandardItem* item = model->itemFromIndex(index);
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);   // 水平居左对齐, 垂直居中对齐
    }
}

// 居中
void MainWindow::on_actAlignCenter_triggered() {
    if (!selection->hasSelection()){
        return;
    }
    QModelIndexList selectedIndexes = selection->selectedIndexes();
    for(int i = 0; i < selectedIndexes.count(); i++) {
        QModelIndex index = selectedIndexes.at(i);
        QStandardItem* item = model->itemFromIndex(index);
        item->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    }
}

// 居右
void MainWindow::on_actAlignRight_triggered() {
    if (!selection->hasSelection()){
        return;
    }
    QModelIndexList selectedIndexes = selection->selectedIndexes();
    for(int i = 0; i < selectedIndexes.count(); i++) {
        QModelIndex index = selectedIndexes.at(i);
        QStandardItem* item = model->itemFromIndex(index);
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }
}

// 斜体
void MainWindow::on_actItatic_triggered(bool checked) {
    if (!selection->hasSelection()) {
        return;
    }
    QModelIndexList selectedIndexes = selection->selectedIndexes();
    for(int i = 0; i < selectedIndexes.count(); i++) {
        QModelIndex index = selectedIndexes.at(i);
        QStandardItem* item = model->itemFromIndex(index);
        QFont font = item->font();
        font.setItalic(checked);
        item->setFont(font);
    }
}

// 粗体
void MainWindow::on_actBold_triggered(bool checked) {
    if (!selection->hasSelection()) {
        return;
    }
    QModelIndexList selectedIndexes = selection->selectedIndexes();
    for(int i = 0; i < selectedIndexes.count(); i++) {
        QModelIndex index = selectedIndexes.at(i);
        QStandardItem* item = model->itemFromIndex(index);
        QFont font = item->font();
        font.setBold(checked);  // 设置字体是否是粗体
        item->setFont(font);
    }
}

// 另存文件
void MainWindow::on_actSave_triggered() {
    QString curPath = QCoreApplication::applicationDirPath();
    QString fileName = QFileDialog::getSaveFileName(this, "另存文件", curPath, "学生文件(*.txt);;所有文件(*.*)");
    if(fileName.isEmpty()) {
        return;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
        return; // 以读写, 文本, 覆盖的方式打开文件
    }
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    QStandardItem* item;
    QString str;
    ui->plainTextEdit->clear();

    // 获取表头文本
    for(int i = 0; i < COLUMNCOUNT; i++) {
        item = model->horizontalHeaderItem(i);
        str = str + item->text() + "\t";
    }
    stream << str << "\n";

    // 获取数据区文本
    for(int i = 0; i < model->rowCount(); i++) {
        str = "";
        for(int j = 0; j < COLUMNCOUNT; j++) {
            item = model->item(i, j);
            str = str + item->text() + "\t";
        }
        stream << str << "\n";
        ui->plainTextEdit->appendPlainText(str);
    }
    file.close();
}

// 模型数据预览
void MainWindow::on_actModelData_triggered() {
    QStandardItem* item;
    QString str;
    ui->plainTextEdit->clear();

    // 获取表头文本
    for(int i = 0; i < COLUMNCOUNT; i++) {
        item = model->horizontalHeaderItem(i);
        if(item == nullptr) {
            continue;
        }
        str = str + item->text() + "\t";
    }

    // 获取数据区文本
    for(int i = 0; i < model->rowCount(); i++) {
        str = "";
        for(int j = 0; j < COLUMNCOUNT; j++) {
            item = model->item(i, j);
            if(item == nullptr) {
                continue;
            }
            str = str + item->text() + "\t";
        }
        ui->plainTextEdit->appendPlainText(str);
    }
}

