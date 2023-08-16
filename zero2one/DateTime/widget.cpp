#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>

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

// 读取当前日期时间
void Widget::on_btnGetDateTime_clicked() {
    QDateTime curDateTime = QDateTime::currentDateTime();   // 获取当前日期时间
    ui->timeEdit->setTime(curDateTime.time());              // 设置时间控件的值
    ui->dateEdit->setDate(curDateTime.date());              // 设置日期控件的值
    ui->dateTimeEdit->setDateTime(curDateTime);             // 设置日期时间控件的值

    ui->lineEditTime->setText(curDateTime.time().toString("HH:mm:ss"));
    ui->lineEditDate->setText(curDateTime.date().toString("yyyy年MM月dd日"));
    ui->lineEditDateTime->setText(curDateTime.toString("yyyy-MM-dd HH:mm:ss"));
}

// 通过 lineEditTime 设置 时间
void Widget::on_btnSetTime_clicked() {
    QString str = ui->lineEditTime->text(); // 假设输入 10:20:12
    str = str.trimmed();    // 去除字符串前后的空格, 防止用户错误输入, 例如 " 2022:12:20 " -> "2022:12:20"
    if(!str.isEmpty()) {
        QTime time = QTime::fromString(str, "hh:mm:ss");    // 这里的格式需要和输入的格式相同, "10-20-12" 则无法转换
        if(time.isValid()) {// 验证时间是否合法
            ui->timeEdit->setTime(time);
        } else {
            QMessageBox::warning(this, "设置时间", "合法格式为: hh:mm:ss");
        }
    }
}

// 设置日期
void Widget::on_btnSetDate_clicked() {
    QString str = ui->lineEditDate->text().trimmed();
    if(!str.isEmpty()) {
        QDate date = QDate::fromString(str, "yyyy-MM-dd");
        if(date.isValid()) {
            ui->dateEdit->setDate(date);
        } else {
            QMessageBox::warning(this, "设置日期", "合法格式为: yyyy-MM-dd");
        }
    }
}

// 设置日期时间
void Widget::on_btnSetDateTime_clicked() {
    QString str = ui->lineEditDateTime->text().trimmed();
    if(!str.isEmpty()) {
        QDateTime datetime = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");
        if(datetime.isValid()) {
            ui->dateTimeEdit->setDateTime(datetime);
        } else {
            QMessageBox::warning(this, "设置日期时间", "合法格式为: yyyy-MM-dd hh:mm:ss");
        }
    }

}

// 日历控件选择日期
void Widget::on_calendarWidget_selectionChanged() {
    QDate curDate = ui->calendarWidget->selectedDate();
    QString str = curDate.toString("yyyy 年 MM 月 dd 日");
    ui->lineEditSelectedDate->setText(str);
}

