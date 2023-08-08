#include <QDebug>
#include "showimagesdialog.h"
#include "ui_showimagesdialog.h"

ShowImagesDialog::ShowImagesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowImagesDialog)
{
    ui->setupUi(this);

    m_index = 0;    // 将图片索引置为 0
}

ShowImagesDialog::~ShowImagesDialog()
{
    delete ui;
}

void ShowImagesDialog::paintEvent(QPaintEvent* event){
    Q_UNUSED(event)
    // 1. 创建画家类对象
    QPainter painter(this);
    // 2. 获取绘图区域
    QRect rect = ui->frame->frameRect();
    // [验证] 通过 ui->frame->frameRect() 获取的坐标原点为(0, 0)
    // int ax, ay, aw, ah;
    // rect.getRect(&ax, &ay, &aw, &ah);
    // qDebug() << ax << ay;

    // [WHY] 坐标系平移:
    // void QPainter::drawImage(const QRectF& targetRect, const QImage& image, const QRectF& sourceRect = QRectF(), Qt::ImageConversionFlags flags = Qt::AutoColor);
    // const QRectF& targetRect: 该参数表示目标区域的矩形范围, 指定了在绘图设备上将图像绘制的 **位置** 和 **大小**, 通常使用 QRect 或 QRectF 类型表示
    // 在 QPainter 中, 绘图操作是相对于绘图设备(例如窗口或控件)的坐标系进行的, 绘图设备的坐标系通常以窗口的左上角为原点 (0, 0)
    // 如果 rect 是通过 ui->frame->frameRect() 获取的, 它表示了 ui->frame 控件的边框矩形, 那么绘制图像时 (0, 0) 对应的是绘图设备的原点, 而不是 rect 的左上角
    // 也就是说: 我通过传入rect得到的 **位置** 和 **大小** 分别是(0, 0) 和 矩形框的大小
    // 但是这个(0, 0), 对于 painter 来说实际是窗口的 (0, 0) 而不是矩形框的 (0, 0)
    rect.translate(ui->frame->pos());

    // 通过移动后, 得到位置为 (11, 11)
    // rect.getRect(&ax, &ay, &aw, &ah);
    // qDebug() << ax << ay;

    // 3. 构建一张要绘制的图片
    QImage image(":/images/0.jpg");
    // 4. 使用 painter 绘制图片
    painter.drawImage(rect, image); // drawImage(const QRect& r, const QImage& image);
                                    // const QRect& r: 表示在何处绘制
                                    // const QImage& image: 表示绘制什么
}

