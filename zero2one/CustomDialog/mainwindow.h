#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// 构成 MV 模型
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "headerdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    // 响应对话框窗口的信号, 设置指定单元格的文本
    void setCellText(int row, int column, QString& text);
    // 响应对话框窗口的信号, 设置 actLocate 的使能状态
    void setActLocateEnable(bool enable);

signals:
    // 当前单元格发生变化时, 发出信号
    void cellIndexChanged(int row, int colNo);

private slots:
    void on_actSetSize_triggered();

    void on_actSetHeader_triggered();

    void on_tableView_clicked(const QModelIndex &index);

    void on_actLocate_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel* model;      // 数据模型
    QItemSelectionModel* selection; // 选择模型
    HeaderDialog* dlgHeader = NULL; // 表头对话框
};
#endif // MAINWINDOW_H
