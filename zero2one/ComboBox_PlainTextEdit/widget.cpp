#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

// 初始化列表
void Widget::on_btnListInit_clicked() {
    QIcon icon(":/icons/unit.ico"); // 图标路径
    ui->cmbSimple->clear();
    for(int i = 0; i < 15; i++) {   // 一般不会这样添加, 多数情况下还是手动一个一个添加
        ui->cmbSimple->addItem(icon, QString::asprintf("Item %d", i));  // 有图标的方式
        // ui->cmbSimple->addItem(QString::asprintf("Item %d", i));     // 无图标的方式
    }
    QStringList cityList;
    cityList << "北京市" << "上海市" << "天津市" << "重庆市" << "河北省" << "江苏省";
    ui->cmbSimple->addItems(cityList);
}

// 初始化城市 + 区号
void Widget::on_btnCityZone_clicked() {
    QMap<QString, int> cityZone;   // 创建一个键值对, 存储城市和区号的关系
    cityZone.insert("北京", 10);
    cityZone.insert("广州", 20);
    cityZone.insert("上海", 21);
    cityZone.insert("天津", 22);
    cityZone.insert("重庆", 23);
    cityZone.insert("沈阳", 24);
    cityZone.insert("南京", 25);
    cityZone.insert("武汉", 27);
    cityZone.insert("成都", 28);
    cityZone.insert("西安", 29);

    ui->cmbCityZone->clear();
    foreach (const QString& str, cityZone.keys()) {
        ui->cmbCityZone->addItem(str, cityZone.value(str));
    }
}

