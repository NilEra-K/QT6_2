#include "timerdialog.h"
#include "ui_timerdialog.h"
#include <QtGlobal>             // qsrand/qrand 等在 QtGlobal 头文件中, 截至 5.15 版本, 这两个方法已经被彻底弃用
#include <QRandomGenerator>     // 改用 QRandomGenertor 中的 QRandomGenerator::global()->generate() 进行随机数的生成
#include <QFileInfoList>

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
    QStringList list1;
    // list1 = dir.entryList(QDir::Files);

    // 改用 QFileInfoList 获取文件信息
    QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files);
    for(int i = 0; i < fileInfoList.size(); i++){
        // QFileInfoList::suffix 获取文件后缀信息, 防止获取到的并非都是 *图片格式* 文件
        if (fileInfoList[i].suffix() == ".jpg" ||
            fileInfoList[i].suffix() == ".png" ||
            fileInfoList[i].suffix() == ".jpeg" ){ // 如果后缀是 ".jpg"/"png"/"jpeg"
            list1.append(fileInfoList[i].fileName());
        }
    }

    for(int i = 0; i < list1.size(); i++){
        QImage image(path + "/" + list1.at(i));
        m_images << image;  // 这里不需要用 push_back(), QT 重写了 `<<` 操作符, 可用于直接将对象插入容器
    }

    // 递归遍历子目录的图片
    QStringList list2 = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    qDebug() << "加载文件夹的数量 : " << list2.size();
    for(int i = 0; i < list2.size(); i++) {
        loadImages(path + "/" + list2.at(i));
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
    // m_index = qrand() % m_images.size();
    m_index = QRandomGenerator::global()->generate() % m_images.size();
}

void TimerDialog::on_btnTimer_clicked()
{
    if(!isStarted) { // 定时器处于停止状态
        isStarted = true;
        m_timerID = startTimer(500);    // 启动定时器, 参数事件间隔为毫秒, 返回定时器 ID
        ui->btnTimer->setText("停止");  // 启动定时器后, 按钮上的文字变为停止
    } else {
        isStarted = false;
        killTimer(m_timerID);
        ui->btnTimer->setText("开始");
    }
}

