#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>

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

    // 设置画刷
    QBrush brush;
    // brush.setColor(Qt::yellow);         // 设置画刷的颜色
    // brush.setStyle(Qt::SolidPattern);   // 设置填充样式

    QPixmap texturePixmap(":/edit.bmp");   // 设置填充图片
    brush.setStyle(Qt::TexturePattern);    // 设置填充样式为纹理图案
    brush.setTexture(texturePixmap);       // 如果是 QPixmap 对象就调用 setTexture
                                           // 如果是 QImage 对象就调用 setTextureImage
    painter.setBrush(brush);

    // 绘制图像
    // painter.drawRect(rect); // 绘制矩形
    // painter.drawEllipse(QPoint(w/2, h/2), w/4, h/4); // 绘制椭圆形
    // painter.drawArc(rect, 30 * 16, 120 * 16);        // 绘制弧线, 参数传入一个矩形、开始角和跨度角
                                                        // 有一个重载
    // painter.drawChord(rect, 30 * 16, 120 * 16);      // 绘制弦, 与绘制弧线相似
    // painter.drawPie(rect,  30 * 16, 120 * 16);       // 绘制扇形
    // 绘制封闭多边形、不封闭的多边形
    QPoint points[6] = {
        QPoint(w/4, h/2),
        QPoint(3*w/8, h/4),
        QPoint(5*w/8, h/4),
        QPoint(3*w/4, h/2),
        QPoint(5*w/8, 3*h/4),
        QPoint(3*w/8, 3*h/4)
    };
    // painter.drawPolygon(points, 6);  // 封闭多边形
    painter.drawPolyline(points, 6);    // 不封闭多边形(折线)

}

