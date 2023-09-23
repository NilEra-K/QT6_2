#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("QPainter 基本绘图");
    setPalette(QPalette(Qt::white));    // 设置窗口为白色背景
    setAutoFillBackground(true);        // 设置自动填充背景色
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event) {
    // 创建 QPainter 对象
    QPainter painter(this);

    // 获取绘图区域
    int w = this->width();              // 窗口宽
    int h = this->height();             // 窗口高
    QRect rect(w/4, h/4, w/2, w/4);     // 窗口中间区域

    // 设置画笔
    QPen pen;
    pen.setWidth(3);                // 设置画笔线宽
    pen.setColor(Qt::cyan);         // 设置画笔颜色
    pen.setStyle(Qt::SolidLine);    // 设置画笔线型
    pen.setCapStyle(Qt::RoundCap);  // 设置线的端点样式
    pen.setJoinStyle(Qt::BevelJoin);// 设置线的连接点样式
    painter.setPen(pen);


    // 绘制图像

}

