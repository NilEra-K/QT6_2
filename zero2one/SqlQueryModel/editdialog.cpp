#include "editdialog.h"
#include "ui_editdialog.h"

EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);
}

EditDialog::~EditDialog()
{
    delete ui;
}

// 将部门信息加载到 cmbDept 上
void EditDialog::setDept(const QMap<int, QString> &dept) {
    m_dept = dept;  // 将部门信息保存到当前类中的变量中
    ui->cmbDept->clear();
    foreach (int id, dept.keys()) {
        qDebug() << dept.value(id) << ' ' << id;
        ui->cmbDept->addItem(dept.value(id), id);
    }
}

// 设置插入的记录
void EditDialog::setInsertRecord(QSqlRecord &recData) {
    setWindowTitle("插入数据");
    m_record = recData;                  // 保存到类中
    qDebug() << m_record;
    ui->editEmpNo->setReadOnly(false);   // empNo 编辑框可用
}

// 返回要插入的记录, 将录入的数据保存到 m_record 中
QSqlRecord EditDialog::recordData() {
    m_record.setValue("empNo", ui->editEmpNo->text());
    m_record.setValue("empName", ui->editEmpName->text());
    m_record.setValue("gender", ui->cmbGender->currentText());
    m_record.setValue("deptId", ui->cmbDept->currentText());
    m_record.setValue("salary", ui->dSpinSalary->value());
    return m_record;
}
