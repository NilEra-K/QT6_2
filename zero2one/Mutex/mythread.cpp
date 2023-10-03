#include "mythread.h"
#include <QDebug>
#include <QMutex>

static int cnt = 0;
static QMutex mutex;

MyThread::MyThread() {
    isStopped = false;
}

// 停止
void MyThread::stop() {
    isStopped = true;
}

// 重写 run() 函数
void MyThread::run() {
    while(!isStopped) {
        // mutex.lock();    // 加锁方式 1
        // 加锁方式 2
        /*
        while(!mutex.tryLock(100)){
            qDebug() << QThread::currentThreadId() << " : 尝试加锁失败";
        }
        */
        // 加锁方式 3
        QMutexLocker locker(&mutex);    // 创建 QMutexLocker 对象并锁定 mutex
        cnt += 1;
        qDebug() << ">>>" << QThread::currentThreadId() << "cnt = " << cnt;
        msleep(500);
        // 当使用 QMutexLocker 时可以不主动进行解锁操作, 当离开 while 作用域时, 该变量会自动销毁
        // mutex.unlock();     // 解锁
    }   // 此处销毁类的实例
    isStopped = false;
}



