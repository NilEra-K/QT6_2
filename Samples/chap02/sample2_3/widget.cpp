#include "widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QPlainTextEdit>

void Widget::do_chkBox_underline(bool checked)
{
    QFont font = txtEdit->font();
    font.setUnderline(checked);
    txtEdit->setFont(font);
}

void Widget::do_chkBox_bold(bool checked)
{
    QFont font = txtEdit->font();
    font.setBold(checked);
    txtEdit->setFont(font);
}

void Widget::do_chkBox_italic(bool checked)
{
    QFont font = txtEdit->font();
    font.setItalic(checked);
    txtEdit->setFont(font);
}

void Widget::do_setFontColor(){
    QPalette palt = txtEdit->palette();
    if(radioButton_black->isChecked()){
        palt.setColor(QPalette::Text, Qt::black);
    } else if(radioButton_blue->isChecked()) {
        palt.setColor(QPalette::Text, Qt::blue);
    } else if(radioButton_red->isChecked()) {
        palt.setColor(QPalette::Text, Qt::red);
    }
    txtEdit->setPalette(palt);
}

void Widget::do_clearTxtEdit()
{
    txtEdit->clear();
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    chkBox_underline = new QCheckBox("下划线");
    chkBox_bold = new QCheckBox("加粗");
    chkBox_italic = new QCheckBox("斜体");
    QHBoxLayout* HLay1 = new QHBoxLayout();
    HLay1->addWidget(chkBox_underline);
    HLay1->addWidget(chkBox_bold);
    HLay1->addWidget(chkBox_italic);

    radioButton_black = new QRadioButton("黑色");
    radioButton_red = new QRadioButton("红色");
    radioButton_blue = new QRadioButton("蓝色");
    QHBoxLayout* HLay2 = new QHBoxLayout();
    HLay2->addWidget(radioButton_black);
    HLay2->addWidget(radioButton_red);
    HLay2->addWidget(radioButton_blue);

    txtEdit = new QPlainTextEdit("Hello World!");
    QFont font = txtEdit->font();
    font.setPointSize(20);
    txtEdit->setFont(font);

    pBtn_ensure = new QPushButton("确认");
    pBtn_close = new QPushButton("关闭");
    pBtn_clear = new QPushButton("清除");
    QHBoxLayout* HLay3 = new QHBoxLayout();
    HLay3->addWidget(pBtn_clear);
    HLay3->addStretch();
    HLay3->addWidget(pBtn_ensure);
    HLay3->addWidget(pBtn_close);

    QVBoxLayout* VLay1 = new QVBoxLayout();
    VLay1->addLayout(HLay1);
    VLay1->addLayout(HLay2);
    VLay1->addWidget(txtEdit);
    VLay1->addLayout(HLay3);
    setLayout(VLay1);

    connect(chkBox_underline, SIGNAL(clicked(bool)), this, SLOT(do_chkBox_underline(bool)));
    connect(chkBox_bold, SIGNAL(clicked(bool)), this, SLOT(do_chkBox_bold(bool)));
    connect(chkBox_italic, SIGNAL(clicked(bool)), this, SLOT(do_chkBox_italic(bool)));
    connect(radioButton_black, SIGNAL(clicked(bool)), this, SLOT(do_setFontColor()));
    connect(radioButton_blue, SIGNAL(clicked(bool)), this, SLOT(do_setFontColor()));
    connect(radioButton_red, SIGNAL(clicked(bool)), this, SLOT(do_setFontColor()));
    connect(pBtn_clear, SIGNAL(clicked(bool)), this, SLOT(do_clearTxtEdit()));
    connect(pBtn_close, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(pBtn_ensure, SIGNAL(clicked(bool)), this, SLOT(accept()));
}

Widget::~Widget()
{
}

