#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QMap>
#include <QSqlRecord>

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QWidget *parent = nullptr);
    ~EditDialog();

    // 将部门信息加载到 cmbDept 上
    void setDept(const QMap<int, QString>& dept);

    // 设置插入的记录
    void setInsertRecord(QSqlRecord& recData);

    // 设置插入的记录
    void setUpdateRecord(QSqlRecord& recData);

    // 返回要插入的记录
    QSqlRecord recordData();

private:
    Ui::EditDialog *ui;
    QMap<int, QString> m_dept;  // 保存部门信息的映射
    QSqlRecord m_record;        // 保持一条记录的数据
};

#endif // EDITDIALOG_H
