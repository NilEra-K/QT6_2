#include "workthread.h"

WorkThread::WorkThread() {
    isStopped = false;
}

void WorkThread::stop() {
    isStopped = true;
}

void WorkThread::run() {
    while(!isStopped) {
        for(int i = 0; i < 10; i++) {
            qDebug() << QThread::currentThreadId() << " : " << i << i  << i;
        }
    }
    isStopped = false;
}
