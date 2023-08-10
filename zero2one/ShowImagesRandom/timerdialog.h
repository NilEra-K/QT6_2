#ifndef TIMERDIALOG_H
#define TIMERDIALOG_H

#include <QDialog>
#include <QImage>
#include <QDir>
#include <QTime>
#include <QPainter>
#include <QVector>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class TimerDialog; }
QT_END_NAMESPACE

class TimerDialog : public QDialog
{
    Q_OBJECT

public:
    TimerDialog(QWidget *parent = nullptr);
    ~TimerDialog();
private:
    // 将指定路径的图片加载到容器中
    void loadImages(const QString& path);
    // 绘图事件处理函数
    void paintEvent(QPaintEvent* event);
    // 定时器事件处理函数
    void timerEvent(QTimerEvent* event);

private:
    Ui::TimerDialog *ui;
    QVector<QImage> m_images;   // 保存图片的容器
    int m_index;                // 图片在向量中的索引
    int m_timerID;              // 定时器 ID
    bool isStarted;             // 是否启动 true - 切换图片/ false - 停止切换
};
#endif // TIMERDIALOG_H
