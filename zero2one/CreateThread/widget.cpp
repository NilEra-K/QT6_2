#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
    qDebug() << "主线程 : " << QThread::currentThreadId() << " 开始运行...";

    // MoveToThread 部分
    work.moveToThread(&thread);
    thread.start();
    connect(ui->btnStart_M, SIGNAL(clicked()), &work, SLOT(doWork()));  // 连接按钮的点击信号和 MoveWork 对象的槽函数 doWork()
                                                                        // 信号发射时, 槽函数被触发执行, 就会交由 thread 的 exec() 处理
}

Widget::~Widget()
{
    delete ui;
}

// 开始
void Widget::on_btnStart_clicked() {
    for(int i = 0; i < MAX_THREAD_NUM; i++) {
        workThreads[i] = new WorkThread;
    }
    for(int i = 0; i < MAX_THREAD_NUM; i++) {
        workThreads[i]->start();
    }

    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
}

// 结束
void Widget::on_btnStop_clicked() {
    for(int i = 0; i < MAX_THREAD_NUM; i++) {
        workThreads[i]->stop();
        workThreads[i]->wait();
        workThreads[i] = nullptr;
    }
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
}

