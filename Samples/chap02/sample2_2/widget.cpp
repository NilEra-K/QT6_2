#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QObject::connect(ui->radioButton_black, &QPushButton::clicked, this, qOverload<>(&Widget::do_FontColor));
    QObject::connect(ui->radioButton_blue, &QPushButton::clicked, this, qOverload<>(&Widget::do_FontColor));
    QObject::connect(ui->radioButton_red, &QPushButton::clicked, this, qOverload<>(&Widget::do_FontColor));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_ckBox_underline_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font(); // 获取当前字体
    font.setUnderline(checked);             // 如果被选中, 为字体设置下划线
    ui->plainTextEdit->setFont(font);       // 将设置好的字体为 plainTextEdit 设置
}


void Widget::on_checkBox_italic_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setItalic(checked);
    ui->plainTextEdit->setFont(font);
}

void Widget::on_checkBox_bold_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setBold(checked);
    ui->plainTextEdit->setFont(font);
}

void Widget::do_FontColor()
{
    QPalette plet = ui->plainTextEdit->palette();
    if(ui->radioButton_black->isChecked()){
        plet.setColor(QPalette::Text, Qt::black);
    } else if (ui->radioButton_blue->isChecked()) {
        plet.setColor(QPalette::Text, Qt::blue);
    } else if (ui->radioButton_red->isChecked()) {
        plet.setColor(QPalette::Text, Qt::red);
    }
    ui->plainTextEdit->setPalette(plet);
}

