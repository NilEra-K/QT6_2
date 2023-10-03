#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include "workthread.h"
#include "movework.h"

#define MAX_THREAD_NUM 2

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnStart_clicked();

    void on_btnStop_clicked();

private:
    Ui::Widget *ui;
    WorkThread* workThreads[MAX_THREAD_NUM];

    QThread thread; // 用于 moveToThread() 的 thread 对象
    MoveWork work;
};
#endif // WIDGET_H
