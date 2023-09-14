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

private slots:
    void on_actSetSize_triggered();

    void on_actSetHeader_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel* model;      // 数据模型
    QItemSelectionModel* selection; // 选择模型
    HeaderDialog* dlgHeader = NULL; // 表头对话框
};
#endif // MAINWINDOW_H
