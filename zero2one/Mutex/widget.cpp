#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

// 开始
void Widget::on_btnStart_clicked() {
    thread1.start();
    qDebug() << "thread1 Has Been Openned...";
    thread2.start();
    qDebug() << "thread2 Has Been Openned...";
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
}

// 停止
void Widget::on_btnStop_clicked() {
    thread1.stop();
    thread2.stop();
    thread1.wait();
    thread2.wait();
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
}

