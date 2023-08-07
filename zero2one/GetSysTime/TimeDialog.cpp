#include "TimeDialog.h"

TimeDialog::TimeDialog(void) {
    // 实现窗口的初始化
    setWindowTitle("获取系统时间");

    // 定义时间标签
    m_timeLabel = new QLabel(this);

    // 设置标签边框效果
    // 1. QFrame::Panel 设置一个边框效果
    // 2. QFrame::Sunken 设置一个下沉效果
    m_timeLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    // 设置标签水平垂直居中
    m_timeLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    // 设置标签字体大小
    QFont font;
    font.setPointSize(20);
    m_timeLabel->setFont(font);

    // 定义获取时间按钮
    m_getTime = new QPushButton("获取系统时间", this);
    m_getTime->setFont(font);

    // 布局
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_timeLabel);
    layout->addWidget(m_getTime);
    this->setLayout(layout);


    // 信号与槽的连接
    // 当按钮对象(m_getTime)被点击时, clicked信号会被触发
    // 该信号会被传递给当前对象(this), 并且会调用 getTime 槽函数
    // 槽函数是一个普通的成员函数, 用于接收和处理信号
    connect(m_getTime, &QPushButton::clicked, this, &TimeDialog::getTime);  // 当按钮被点击时, 将会调用 this 对象的 getTime 函数
                                                                            // 按钮点击 => this->getTime => this对象发送 mySignal(QString) 信号

    // 发送自定义信号
    // 当前对象(this)发出 mySignal 信号时
    // 该信号会被传递给标签对象(m_timeLabel), 并且会调用setText槽函数
    // setText槽函数是 QLabel 类中的一个成员函数, 用于设置标签的文本内容
    connect(this, &TimeDialog::mySignal, m_timeLabel, &QLabel::setText);    // 当前对象发出 mySignal 信号时, 将会将信号传递给标签对象, 并且标签对象会根据信号的内容来设置自己的文本内容
    // 当点击按钮时触发了 getTime 函数, 而 getTime 函数中发送了 mySignal信号, 而信号的发送者是 this, 使得触发 setText 槽函数
}

TimeDialog::~TimeDialog() { }

void TimeDialog::getTime(void) {
    // 获取当前时间
    QTime time = QTime::currentTime();

    // 将当前时间转换为字符串
    QString str = time.toString("hh:mm:ss");

    // 显示时间
    // m_timeLabel->setText(str);
    emit mySignal(str); // 使用信号方式传递参数
}