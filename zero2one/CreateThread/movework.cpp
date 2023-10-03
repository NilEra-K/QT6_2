#include "movework.h"
#include <QThread>
#include <QDebug>

MoveWork::MoveWork(QObject *parent)
    : QObject{parent}
{

}

void MoveWork::doWork() {
    while(true) {
        for(int i = 0; i < 10; i++) {
            qDebug() << QThread::currentThreadId() << " : " << i << i << i;
        }
    }
}
