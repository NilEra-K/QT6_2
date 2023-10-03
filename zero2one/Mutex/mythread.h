#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
public:
    MyThread();
    void stop();
protected:
    void run();
private:
    bool isStopped;
};

#endif // MYTHREAD_H
