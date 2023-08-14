#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::keyPressEvent(QKeyEvent *event) {
    // 获取 label 的当前坐标
    int x = ui->label->pos().x();
    int y = ui->label->pos().y();
    switch (event->key()) {
    case Qt::Key_Left:
        x -= 5; // 每次移动 5 个像素
        break;
    case Qt::Key_Right:
        x += 5;
        break;
    case Qt::Key_Up:
        y -= 5;
        break;
    case Qt::Key_Down:
        y += 5;
        break;
    default:
        break;
    }

    QSize s1 = this->size();
    QSize s2 = ui->label->size();
    if(x < 0){
        x = 0;
    } else if (x > s1.width() - s2.width()) {
        x = s1.width() - s2.width();
    }

    if(y < 0){
        y = 0;
    } else if (y > s1.height() - s2.height()) {
        y = s1.height() - s2.height();
    }

    ui->label->move(x, y);
}

void Dialog::keyReleaseEvent(QKeyEvent *event) {

}
