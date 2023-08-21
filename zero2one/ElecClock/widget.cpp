#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);  // 固定窗口大小

    // 启动定时器
    this->m_timerID = startTimer(1000);
}

Widget::~Widget()
{
    // 停止定时器
    killTimer(m_timerID);
    delete ui;
}

void Widget::timerEvent(QTimerEvent *event) {
    QTime curTime = QTime::currentTime();
    ui->lcdHour->display(QString::number(curTime.hour()));
    ui->lcdMinute->display(QString::number(curTime.minute()));
    ui->lcdSecond->display(QString::number(curTime.second()));
}

