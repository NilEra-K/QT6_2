#include "timerdialog.h"
#include "ui_timerdialog.h"
#include <QtGlobal>

TimerDialog::TimerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TimerDialog)
{
    ui->setupUi(this);
    m_index = 0;        // 初始图片设置为第一张图片
    isStarted = false;  // 计时器设置为关闭状态

    // 设计随机种子
    // qsrand(QTime::currentTime().msec());    // 获取毫秒值, qsrand 在 QT 5.15 中已经被弃用
    loadImages("../ShowImagesRandom/Images");
    qDebug() << "加载图片数量 : " << m_images.size();
}

TimerDialog::~TimerDialog()
{
    delete ui;
}

// 从指定路径加载图片, 保存到向量容器中
void TimerDialog::loadImages(const QString& path) {
    // 创建目录
    QDir dir(path);
    // 遍历目录下的所有图片
    QStringList list1 = dir.entryList(QDir::Files);
    for(int i = 0; i < list1.size(); i++){
        QImage image(path + "/" + list1.at(i));
        m_images << image;  // 这里不需要用 push_back(), QT 重写了 `<<` 操作符, 可用于直接将对象插入容器
    }
}

// 绘图事件处理函数
void TimerDialog::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    QPainter painter(this);
    QRect rect = ui->frame->frameRect();
    rect.translate(ui->frame->pos());
    painter.drawImage(rect, m_images[m_index]);
    update();
}

// 定时器事件处理函数
void TimerDialog::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event)
}


