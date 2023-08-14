#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    // 鼠标事件处理函数
    void mouseMoveEvent(QMouseEvent* event);    // 鼠标移动事件处理函数
    void mousePressEvent(QMouseEvent* event);   // 鼠标按下事件处理函数
    void mouseReleaseEvent(QMouseEvent* event); // 鼠标案件松开事件处理函数

private:
    Ui::Dialog *ui;

    bool m_drag;    // 用于记录当前是否可以移动标签控件
    QPoint m_pos;   // 用于记录当前控件坐标
};
#endif // DIALOG_H
