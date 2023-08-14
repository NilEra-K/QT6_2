#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    m_drag = false;
}

Dialog::~Dialog()
{
    delete ui;
}

// 鼠标移动事件处理函数
void Dialog::mouseMoveEvent(QMouseEvent* event) {
    if(m_drag){
        // 计算 label 要移动到的位置
        QPoint newPos = event->pos() + m_pos;

        QSize s1 = this->size();        // 获取窗口的大小
        QSize s2 = ui->label->size();   // 获取 label 的大小
        if(newPos.x() < 0)
            newPos.setX(0);
        else if(newPos.x() > s1.width() - s2.width())
            newPos.setX(s1.width() - s2.width());

        if(newPos.y() < 0)
            newPos.setY(0);
        else if(newPos.y() > s1.height() - s2.height())
            newPos.setY(s1.height() - s2.height());

        // 移动
        ui->label->move(newPos);
    }
}

// 鼠标按键按下事件处理函数
void Dialog::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) { // 如果按下的是鼠标左键
        // 获取 label 控件所在的矩形区域
        QRect rect = ui->label->frameRect();

        // 坐标平移
        rect.translate(ui->label->pos());

        // 判断鼠标光标是否在 rect 内
        // rect 是否包含 鼠标坐标
        if(rect.contains(event->pos())) {
            m_drag = true;
            m_pos = ui->label->pos() -  event->pos();
        }
    }
}

void Dialog::mouseReleaseEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        m_drag = false;
    }
}

