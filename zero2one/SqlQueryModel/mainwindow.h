#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QItemSelectionModel>

#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actOpenDB_triggered();

    void on_actInsert_triggered();

private:
    void loadDataBase(const QString& dbName);   // 根据数据库名加载数据库
    void loadDept();    // 读取 dept 表中的数据, 并保存到映射中
private:
    Ui::MainWindow *ui;
    QSqlDatabase db;                    // 数据库
    QSqlQueryModel* model;              // 数据模型
    QItemSelectionModel* selection;     // 选择模型
    QMap<int, QString> m_map;
};
#endif // MAINWINDOW_H
