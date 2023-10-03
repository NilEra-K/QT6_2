#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mythread.h"

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
    MyThread thread1;
    MyThread thread2;
};
#endif // WIDGET_H
