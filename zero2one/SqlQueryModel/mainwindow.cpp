#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tableView);
    // 程序开始时, 未打开数据库, 初始化对于数据操作按钮的使能状态
    ui->actInsert->setEnabled(false);
    ui->actUpdate->setEnabled(false);
    ui->actDelete->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadDataBase(const QString &) {
    model = new QSqlQueryModel(this);               // 创建数据模型
    selection = new QItemSelectionModel(model);     // 创建选择模型

    // 执行查询操作
    // model->setQuery("SELECT * FROM emp ORDER BY empNo");
    // 也可以使用多表查询的方式进行展示
    model->setQuery("SELECT empNo, empName, gender, deptName, salary From emp, dept WHERE emp.deptId=dept.deptId ORDER BY empNo");
    if(model->lastError().isValid()) {
        QMessageBox::critical(this, "打开数据库", "加载数据表失败\n" + model->lastError().text());
        return;
    }
    model->setHeaderData(0, Qt::Horizontal, "工号");
    model->setHeaderData(1, Qt::Horizontal, "姓名");
    model->setHeaderData(2, Qt::Horizontal, "性别");
    model->setHeaderData(3, Qt::Horizontal, "部门");
    model->setHeaderData(4, Qt::Horizontal, "工资");

    ui->tableView->setModel(model);
    ui->tableView->setSelectionModel(selection);

    // 设置 "打开数据库" 按钮使能状态
    ui->actOpenDB->setEnabled(false);
    ui->actInsert->setEnabled(true);
    ui->actUpdate->setEnabled(true);
    ui->actDelete->setEnabled(true);
}

// 读取 dept 表中数据, 并保存到映射中
void MainWindow::loadDept() {
    QSqlQuery query;
    query.exec("SELECT * FROM dept");
    while(query.next()) {
        m_map.insert(query.value(0).toInt(), query.value(1).toString());
    }
}

// 更新记录
void MainWindow::updateRecord(int recNo) {
    QSqlRecord curRec = model->record(recNo);   // 获取当前行记录
    int empNo = curRec.value("empNo").toInt();
    QSqlQuery query;
    query.prepare("SELECT * FROM emp WHERE empNo=?");
    query.addBindValue(empNo);  // 或者写 query.bindValue(0, emoNo);
    if(!query.exec()) { return; }
    query.first();
    if(!query.isValid()) { return; }
    curRec = query.record();
    EditDialog* dlgEdit = new EditDialog(this);
    dlgEdit->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    dlgEdit->setDept(m_map);            // 加载部门信息
    dlgEdit->setUpdateRecord(curRec);   // 加载要修改的记录
    int ret = dlgEdit->exec();          // 模态方式打开
    if(ret == QDialog::Accepted) {
        QSqlRecord recData = dlgEdit->recordData();
        query.prepare("UPDATE emp SET empName=:name, gender=:gender, deptId=:id, salary=:sal WHERE empNo=:no");
        query.bindValue(":no", recData.value("empNo"));
        query.bindValue(":name", recData.value("empName"));
        query.bindValue(":gender", recData.value("gender"));
        query.bindValue(":id", recData.value("deptId"));
        query.bindValue(":sal", recData.value("salary"));
        if(!query.exec()) {
            QMessageBox::critical(this, "更新", "更新记录失败\n" + query.lastError().text());
        } else {
            // model->setQuery("SELECT * FROM emp ORDER BY empNo");
            model->setQuery("SELECT empNo, empName, gender, deptName, salary From emp, dept WHERE emp.deptId=dept.deptId ORDER BY empNo");
        }
    }

    delete dlgEdit;
    dlgEdit = nullptr;
}

// 打开数据库
void MainWindow::on_actOpenDB_triggered() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("00098498");
    db.setDatabaseName("emp");
    if(!db.open()) {
        QMessageBox::critical(this, "打开数据库", "数据库打开失败\n" + db.lastError().text());
        return;
    }
    loadDataBase("emp");    // 读取 emp 表格数据并显示在 tableView 上
    loadDept();             // 读取 dept 表中数据, 并保存到映射中
}

// 插入记录
void MainWindow::on_actInsert_triggered() {
    QSqlQuery query;
    query.exec("SELECT * FROM emp WHERE 1=0");  // 1 不可能等于 0, 这一行是在查询字段信息
                                                // 只用于获取字段信息或称字段结构, 而不获取数字信息
    QSqlRecord record = query.record();         // 获取当前行记录 (空行)
                                                // 对于本项目, 会返回 QSqlRecord(5), 包含五个 QSqlField
                                                // 以第五个字段为例:
                                                // 4: QSqlField("salary", double, tableName: "emp", length: 9, precision: 2, required: no, generated: yes, typeID: 246, autoValue: false, readOnly: false) "5000"
    // qDebug() << "record" << record;          // 可以访问该类实例化对象后的成员函数

    EditDialog* dlgEdit = new EditDialog(this);                 // 动态创建窗口
    dlgEdit->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);   // 固定窗口大小
    dlgEdit->setDept(m_map);                                    // 初始化对话框窗口的部门组合框
    dlgEdit->setInsertRecord(record);                           // 设置插入记录
    int ret = dlgEdit->exec();                                  // 以模态方式显示
    if(ret == QDialog::Accepted) { // "确定"按钮被按下
        QSqlRecord recData = dlgEdit->recordData();
        qDebug() << "recDate" << recData;
        query.prepare("INSERT INTO emp VALUES(:empNo, :empName, :gender, :deptId, :salary)");
        query.bindValue(0, recData.value("empNo"));
        query.bindValue(1, recData.value("empName"));
        query.bindValue(2, recData.value("gender"));
        query.bindValue(3, recData.value("deptId"));
        query.bindValue(4, recData.value("salary"));
        if(!query.exec()) { // 执行失败弹出错误
            QMessageBox::critical(this, "插入", "输入记录失败\n" + query.lastError().text());
        } else { // 执行成功后重新加载模型, 可以理解为刷新模型
            // model->setQuery("SELECT * FROM emp ORDER BY empNo");
            model->setQuery("SELECT empNo, empName, gender, deptName, salary From emp, dept WHERE emp.deptId=dept.deptId ORDER BY empNo");
        }
    }
    delete dlgEdit; // 使用后删除
    dlgEdit = nullptr;
}

// 更新记录
void MainWindow::on_actUpdate_triggered() {
    int rowNo = selection->currentIndex().row();
    updateRecord(rowNo);
}

// 双击更新界面
void MainWindow::on_tableView_doubleClicked(const QModelIndex &index) {
    int rowNo = index.row();
    updateRecord(rowNo);
}

// 删除
void MainWindow::on_actDelete_triggered() {
    int curNo = selection->currentIndex().row();
    QSqlRecord curRec = model->record(curNo);       // 获取记录
    if(curRec.isEmpty()) { return; }
    int empNo = curRec.value("empNo").toInt();
    QSqlQuery query;
    query.prepare("DELETE FROM emp WHERE empNo=:no");
    query.bindValue(":no", empNo);
    if(!query.exec()) {
        QMessageBox::critical(this, "删除", "删除记录失败\n" + query.lastError().text());
    } else {
        if(query.numRowsAffected() == 0) {
            QMessageBox::information(this, "删除", "没有满足条件的记录");
        } else {
            model->setQuery("SELECT * FROM emp ORDER BY empNo");
        }
    }
}

