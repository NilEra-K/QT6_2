#ifndef __TIMEDIALOG_H
#define __TIMEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>  // 垂直布局器
#include <QTime>        // 时间
#include <QDebug>       // 打印调试信息

class TimeDialog : public QDialog {
    Q_OBJECT
private:
    QLabel* m_timeLabel;        // 显示时间的标签
    QPushButton* m_getTime;     // 获取时间的按钮
public:
    TimeDialog(void);
    ~TimeDialog();
signals:
    void mySignal(const QString&);  // 自定义信号
public slots:
    void getTime(void);
};

#endif // __TIMEDIALOG_H