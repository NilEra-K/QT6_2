#include <QCoreApplication>
#include <QWaitCondition>
#include <QMutex>
#include <QThread>
#include <QDebug>
#include <QTime>

#define DATASIZE 100
#define BUFFERSIZE 8

int buffer[BUFFERSIZE];
QWaitCondition bufferNotEmpty;      // 非空
QWaitCondition bufferNotFull;       // 非满
QMutex mutex;

int numUsable = 0;                  // 可用数据数量
int index = 0;                      // 下标: 记录下一次消费哪个数据

class ProducerThread : public QThread {
protected:
    void run() {
        for(int i = 0; i < DATASIZE; i++) {
            mutex.lock();
            if(numUsable == BUFFERSIZE) { // 缓冲区已满
                qDebug() << "缓冲区已满, 等待...";
                bufferNotFull.wait(&mutex); // 等待缓冲区有空位(bufferNotFull) 条件成立
            }
        }
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    return a.exec();
}
