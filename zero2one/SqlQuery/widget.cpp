#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    loadDept();
}

Widget::~Widget()
{
    delete ui;
}

// 查询
void Widget::on_btnSelect_clicked() {
    QSqlQuery query;
    if(!query.exec("SELECT * FROM emp")) {
        QMessageBox::critical(this, "查询", "查询失败\n" + query.lastError().text());
        return;
    }
    while(query.next()){
        qDebug() << query.value(0).toInt() << '\t'
                 << query.value(1).toString() << '\t'
                 << query.value(2).toString() << '\t'
                 << query.value(3).toInt() << '\t'
                 << query.value(4).toDouble();
    }
//    qDebug() << "执行 first(), 定位到第一行 : ";
//    if(query.first()) {
//        // 获取 query 指向的记录在结果集中的行号
//        int rowNo = query.at();

//        // 获取记录中的列数
//        int colNum = query.record().count();

//        // 定义一个变量 fieldNo 用于存取字段的列号, 此处获取 "empNo" 字段所在的列号
//        int fieldNo = query.record().indexOf("empNo");
//        int empNo = query.value(fieldNo).toInt();

//        // 同样的方法获取其他字段的值
//        fieldNo = query.record().indexOf("empName");
//        QString empName = query.value(fieldNo).toString();

//        fieldNo = query.record().indexOf("gender");
//        QString gender = query.value(fieldNo).toString();

//        fieldNo = query.record().indexOf("deptId");
//        int deptId = query.value(fieldNo).toInt();

//        fieldNo = query.record().indexOf("salary");
//        double salary = query.value(fieldNo).toDouble();

//        // 输出
//        qDebug() << "行号为 : " << rowNo;
//        qDebug() << "列数为 : " << colNum;
//        qDebug() << "empNo : " << empNo;
//        qDebug() << "empName : " << empName;
//        qDebug() << "gender : " << gender;
//        qDebug() << "deptId : " << deptId;
//        qDebug() << "salary : " << salary;
//    }
//    qDebug() << "======== 执行 seek(2) 定位到第三行 ========";
//    if(query.seek(2)) {
//        // 输出
//        qDebug() << "行号为 : " << query.at();
//        qDebug() << "列数为 : " << query.record().count();
//        qDebug() << "empNo : " << query.value("empNo").toInt();
//        qDebug() << "empName : " << query.value("empName").toString();
//        qDebug() << "gender : " << query.value("gender").toString();
//        qDebug() << "deptId : " << query.value("deptId").toInt();
//        qDebug() << "salary : " << query.value("salary").toDouble();
//    }

//    qDebug() << "======== 执行 last() 定位到最后一行 ========";
//    if(query.seek(2)) {
//        // 输出
//        qDebug() << "行号为 : " << query.at();
//        qDebug() << "列数为 : " << query.record().count();
//        qDebug() << "empNo : " << query.value(0).toInt();
//        qDebug() << "empName : " << query.value(1).toString();
//        qDebug() << "gender : " << query.value(2).toString();
//        qDebug() << "deptId : " << query.value(3).toInt();
//        qDebug() << "salary : " << query.value(4).toDouble();
//    }
}

// 查询部门表, 将数据加载到部门组合框 cmbDept 中
void Widget::loadDept() {
    QSqlQuery query;
    query.exec("SELECT * FROM dept");
    while(query.next()) {
        int deptId = query.value("deptId").toInt();             // 获取部门编号
        QString deptName = query.value("deptName").toString();  // 获取部门名称
        ui->cmbDept->addItem(deptName, deptId);
    }
}

// 插入操作
void Widget::on_btnInsert_clicked() {
    int empNo = ui->editEmpNo->text().toInt();            // 工号
    QString empName = ui->editEmpName->text().trimmed();  // 姓名, trimmed() 用于消除空格
    QString gender = ui->cmbGender->currentText();        // 性别
    int deptId = ui->cmbDept->currentData().toInt();      // 部门编号
    double salary = ui->dSpinSalary->value();             // 工资

    QSqlQuery query;
    // 执行如下 SQL 语句
    // INSERT INTO emp(empNo, empName, gender, deptId, salary) VALUES (1010, '张三', '男', 2, 12000);
    QString sqlStr = QString::asprintf(
                "INSERT INTO emp(empNo, empName, gender, deptId, salary) "
                "VALUES (%1, '%2', '%3', %4, %5)"
            ).arg(empNo).arg(empName).arg(gender).arg(deptId).arg(salary);
    qDebug() << sqlStr;
    if(!query.exec(sqlStr)) { // 执行 sqlStr 语句
        QMessageBox::critical(this, "插入", "插入数据失败\n" + query.lastError().text());
        return;
    }
    QMessageBox::information(this, "插入", "插入数据成功");
}

// 修改操作: 根据工号修改其他字段的值
void Widget::on_btnUpdate_clicked() {
    int empNo = ui->editEmpNo->text().toInt();            // 工号
    QString empName = ui->editEmpName->text().trimmed();  // 姓名, trimmed() 用于消除空格
    QString gender = ui->cmbGender->currentText();        // 性别
    int deptId = ui->cmbDept->currentData().toInt();      // 部门编号
    double salary = ui->dSpinSalary->value();             // 工资

    QSqlQuery query;
    // 执行如下 SQL 语句
    // UPDATE emp SET empName='张三', gender='男', deptId=2, salary=12345.67 WHERE empNo=1010;
    query.prepare("UPDATE emp SET empName=:name, gender=:gender,deptId=:id,salary=:sal WHERE empNo=:no");
    query.bindValue(":name", empName);
    query.bindValue(":gender", gender);
    query.bindValue(":id", deptId);
    query.bindValue(":sal", salary);
    query.bindValue(":no", empNo);
    if(!query.exec()) {
        QMessageBox::critical(this, "修改", "修改数据失败\n" + query.lastError().text());
        return;
    }
    QMessageBox::information(this, "修改", "修改数据成功");
}

// 删除操作: 根据工号删除
void Widget::on_btnDelete_clicked() {
    int empNo = ui->editEmpNo->text().toInt();
    QSqlQuery query;
    query.prepare("DELETE FROM emp WHERE empNo=?");
    query.bindValue(0, empNo);
    if(!query.exec()) {
        QMessageBox::critical(this, "删除", "删除数据失败\n" + query.lastError().text());
        return;
    }
    if(query.numRowsAffected() == 0) {
        QMessageBox::critical(this, "删除", "没有匹配的数据");
    } else {
        QMessageBox::information(this, "删除", "删除数据成功");
    }
}

