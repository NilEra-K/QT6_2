#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPainterPath>
#include <cmath>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("QPainter 坐标变换");    // 设置窗口标题
    setPalette(QPalette(Qt::white));       // 设置窗口背景颜色
    setAutoFillBackground(true);           // 设置自动填充背景颜色
    resize(600, 300);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);    // 设置窗口大小固定
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    // 创建画家类对象
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing); // 抗锯齿效果

    // 生成五角星的五个顶点坐标(假设原点在五角星中心)
    qreal r = 100;  // 圆的半径
    const qreal Pi = 3.1415926535;
    qreal deg = Pi * 72 / 180;  // 72° 对应的弧度
    QPointF points[5] = {
        QPointF(r, 0),
        QPointF(r * cos(deg), -r * sin(deg)),
        QPointF(r * cos(2*deg), -r * sin(2*deg)),
        QPointF(r * cos(3*deg), -r * sin(3*deg)),
        QPointF(r * cos(4*deg), -r * sin(4*deg))
    };

    // 设置画笔
    QPen pen;
    pen.setColor(QColor(170, 20, 20));
    pen.setStyle(Qt::DashDotDotLine); // 绘制实线
    pen.setJoinStyle((Qt::BevelJoin));
    painter.setPen(pen);

    // 设置字体
    QFont font;
    font.setPointSize(12);
    font.setBold(false);
    font.setFamily("隶书");

    // 设计绘制五角星的 QPainterPath, 以便重复使用
    QPainterPath starPath;
    starPath.moveTo(points[0]); // 调用 moveTo 函数表示开启一个新的点进行绘图
    starPath.lineTo(points[2]); // 从当前点到参数指定的点绘制一条直线, 同时将参数设置为新的当前点
    starPath.lineTo(points[4]);
    starPath.lineTo(points[1]);
    starPath.lineTo(points[3]);
    starPath.closeSubpath();    // 闭合路径, 将最后一次绘制路径的点与第一个点进行连接

    // 显示顶点编号
    for(int i = 0; i < 5; i++) {
        starPath.addText(points[i], font, QString::number(i));
    }

    // 绘图
    painter.save();                 // 保存坐标状态
    painter.translate(100, 150);    // 平移
    painter.drawPath(starPath);     // 绘制五角星
    painter.drawText(0, 0, "S1");   // 绘制文本 S1
    painter.restore();              // 恢复坐标状态

    painter.translate(300, 150);    // 平移
    painter.scale(0.8, 0.8);        // 缩放(缩小)
    painter.rotate(90);             // 旋转(顺时针旋转 90°)
    painter.drawPath(starPath);
    painter.drawText(0, 0, "S2");   // 绘制文本 S1
    // painter.restore();
    painter.resetTransform();       // 重置所有坐标变换

    painter.translate(500, 150);
    painter.rotate(-135);
    painter.drawPath(starPath);
    painter.drawText(0, 0, "S3");
}

