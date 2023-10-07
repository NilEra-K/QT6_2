#include <QCoreApplication>
#include <QSemaphore>
#include <QThread>
#include <QDebug>
#include <QRandomGenerator>

#define DATASIZE 100
#define BUFFERSIZE 8
int buffer[BUFFERSIZE];

QSemaphore freeSpace(BUFFERSIZE);   // 生产者信号量: 对于生产者来说资源是空位
QSemaphore dataNum(0);              // 消费者信号量: 对于消费者来说资源是数据

// 生产者线程
class Producer : public QThread {
protected:
    void run() {
        for(int i = 0; i < DATASIZE; i++) {
            freeSpace.acquire(1);   // 获取一个生产者信号量
            buffer[i % BUFFERSIZE] = i + 1; // 将生产的数据放入缓冲区
            qDebug() << QThread::currentThreadId() << " >>> 生产者生产了数据 : " << i + 1;
            // 生产者产生了一个数据, 对于消费者而言就是多了一个可供消费的数字
            dataNum.release(1);     // 释放一个消费者信号量
            msleep((QRandomGenerator::global()->bounded(0, 500) % 5 + 1) * 100);
        }
    }
};

// 消费者线程
class Consumer : public QThread {
protected:
    void run() {
        for(int i = 0; i < DATASIZE; i++) {
            dataNum.acquire(1);     // 获取一个消费者信号量
            qDebug() << QThread::currentThreadId() << "消费者消费了数据 : " << buffer[i % BUFFERSIZE];
            // 消费者消费了一个数据, 对于生产者而言就是多了一个可供生产的空位
            freeSpace.release(1);
            msleep((QRandomGenerator::global()->bounded(0, 500) % 5 + 1) * 100);
        }
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    Producer producer;
    Consumer consumer;

    producer.start();
    consumer.start();

    producer.wait();
    consumer.wait();
    return a.exec();
}
