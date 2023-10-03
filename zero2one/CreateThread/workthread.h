#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include <QDebug>

class WorkThread : public QThread
{
public:
    WorkThread();
    void stop();    // 定义线程终止函数, 需要注意的是 terminate() 函数并不是推荐的终止线程的方式
protected:
    void run();
private:
    bool isStopped;
};

#endif // WORKTHREAD_H
