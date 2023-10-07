#include <QCoreApplication>
#include <QWaitCondition>
#include <QMutex>
#include <QThread>
#include <QDebug>
#include <QTime>
#include <QRandomGenerator> // 用于生成随机数

#define DATASIZE 100
#define BUFFERSIZE 8

int buffer[BUFFERSIZE];
QWaitCondition bufferNotEmpty;      // 非空
QWaitCondition bufferNotFull;       // 非满
QMutex mutex;

int numUsable = 0;                  // 可用数据数量
int index = 0;                      // 下标: 记录下一次消费哪个数据

// 生产者线程
class ProducerThread : public QThread {
protected:
    void run() {
        for(int i = 0; i < DATASIZE; i++) {
            mutex.lock();
            if(numUsable == BUFFERSIZE) { // 缓冲区已满
                qDebug() << "缓冲区已满, 等待...";
                bufferNotFull.wait(&mutex); // 等待缓冲区有空位 (bufferNotFull) 条件成立
                                            // *非满条件等待, 说明缓冲区已经满了 -> 等待非满条件
            }
            buffer[i % BUFFERSIZE] = i + 1; // 缓冲区未满, 向缓冲区存储数据
            ++numUsable;
            qDebug() << currentThreadId() << " > 生产者生产了数据 : " << i + 1;
            msleep(QRandomGenerator::global()->bounded(0, 500) % 5 * 100);  // 100, 200, 300, 400, 500
            mutex.unlock();
            bufferNotEmpty.wakeAll();   // 唤醒等待缓冲有数据 (bufferNotEmpty)条件成立的线程
                                        // *非空条件唤醒, 说明当前正处于非空环境
        }
    }
};

// 消费者线程
class ConsumerThread : public QThread {
protected:
    void run() {
        while (1) {
            mutex.lock();
            if(numUsable == 0) { // 缓冲区已空
                qDebug() << "缓冲区已空, 等待...";
                bufferNotEmpty.wait(&mutex);    // 等待缓冲区有数据(bufferNotEmpty)条件成立
                                                // *非空条件等待, 说明缓冲区已经空了 -> 等待非空条件
            }
            qDebug() << currentThreadId() << " > 消费者消费了数据 : " << buffer[index];
            index = (++index) % BUFFERSIZE;
            --numUsable;
            msleep(QRandomGenerator::global()->bounded(0, 500) % 5 * 100);
            mutex.unlock();
            bufferNotFull.wakeAll();    // 唤醒等待缓冲区由空位(bufferNotFull)条件成立的线程
                                        // *非满条件唤醒, 说明当前正处于非满环境
        }
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    ProducerThread produce;
    ConsumerThread consumer1;
//    ConsumerThread consumer2;

    produce.start();
    consumer1.start();
//    consumer2.start();

    produce.wait();
    consumer1.wait();
//    consumer2.wait();

    return a.exec();
}
