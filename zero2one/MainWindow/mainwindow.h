#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// 需要手动添加的控件
#include <QLabel>
#include <QSpinBox>
#include <QFontComboBox>    // 字体组合框

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
    void on_actFontBold_triggered(bool checked);

    void on_actFontItalic_triggered(bool checked);

    void on_actFontUnderLine_triggered(bool checked);

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_selectionChanged();

    // 自定义槽函数
    void spinBox_valueChanged(int fontSize);                // 用于改变字体大小
    void cmbFont_currentIndexChanged(int font);             // 用于选择字体

private:
    void initUi();  // 代码方式初始化 UI

private:
    Ui::MainWindow *ui;

    // 需要手动添加到窗口的控件
    QLabel* labelCurFile;   // [状态栏] 显示当前文件名
    QSpinBox* spinBox;      // [工具栏] 设置字体大小
    QFontComboBox* cmbFont;  // [工具栏] 选择字体
};
#endif // MAINWINDOW_H
