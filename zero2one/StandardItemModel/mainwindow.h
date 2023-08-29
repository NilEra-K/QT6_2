#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QLabel>
#include <QFile>
#include <QFileDialog>  // 文件对话框
#include <QTextStream>  // 文本流

#define COLUMNCOUNT 5   // 文件固定为 5 列

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
    // 处理 QItemSelectionModel::currentChanged(...) 信号
    void on_CurrentChanged(const QModelIndex& current, const QModelIndex& previous);

    void on_actOpen_triggered();

private:
    void initUi(void);  // 初始化状态栏
    void initModelFromStringList(QStringList&); // 通过 QStringList 初始化模型

private:
    Ui::MainWindow *ui;

    QStandardItemModel* model;      // 数据模型
    QItemSelectionModel* selection; // 选择模型
    QLabel* labelCurFile;           // 当前文件
    QLabel* labelCellPos;           // 当前单元格
    QLabel* labelCellText;          // 当前单元格文本
};
#endif // MAINWINDOW_H
