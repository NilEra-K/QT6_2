/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QCheckBox *ckBox_underline;
    QCheckBox *checkBox_italic;
    QCheckBox *checkBox_bold;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton_black;
    QRadioButton *radioButton_red;
    QRadioButton *radioButton_blue;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pBtn_clean;
    QSpacerItem *horizontalSpacer;
    QPushButton *pBtn_ok;
    QPushButton *pBtn_close;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(478, 490);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/images/editor.png"), QSize(), QIcon::Normal, QIcon::Off);
        Widget->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        ckBox_underline = new QCheckBox(groupBox);
        ckBox_underline->setObjectName(QString::fromUtf8("ckBox_underline"));

        horizontalLayout->addWidget(ckBox_underline);

        checkBox_italic = new QCheckBox(groupBox);
        checkBox_italic->setObjectName(QString::fromUtf8("checkBox_italic"));

        horizontalLayout->addWidget(checkBox_italic);

        checkBox_bold = new QCheckBox(groupBox);
        checkBox_bold->setObjectName(QString::fromUtf8("checkBox_bold"));

        horizontalLayout->addWidget(checkBox_bold);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        radioButton_black = new QRadioButton(groupBox_2);
        radioButton_black->setObjectName(QString::fromUtf8("radioButton_black"));

        horizontalLayout_2->addWidget(radioButton_black);

        radioButton_red = new QRadioButton(groupBox_2);
        radioButton_red->setObjectName(QString::fromUtf8("radioButton_red"));

        horizontalLayout_2->addWidget(radioButton_red);

        radioButton_blue = new QRadioButton(groupBox_2);
        radioButton_blue->setObjectName(QString::fromUtf8("radioButton_blue"));

        horizontalLayout_2->addWidget(radioButton_blue);


        verticalLayout->addWidget(groupBox_2);

        plainTextEdit = new QPlainTextEdit(Widget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        QFont font;
        font.setPointSize(16);
        font.setBold(false);
        plainTextEdit->setFont(font);

        verticalLayout->addWidget(plainTextEdit);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        pBtn_clean = new QPushButton(Widget);
        pBtn_clean->setObjectName(QString::fromUtf8("pBtn_clean"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/images/eraser.png"), QSize(), QIcon::Normal, QIcon::Off);
        pBtn_clean->setIcon(icon1);
        pBtn_clean->setIconSize(QSize(13, 13));

        horizontalLayout_3->addWidget(pBtn_clean);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pBtn_ok = new QPushButton(Widget);
        pBtn_ok->setObjectName(QString::fromUtf8("pBtn_ok"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/images/ensure.png"), QSize(), QIcon::Normal, QIcon::Off);
        pBtn_ok->setIcon(icon2);

        horizontalLayout_3->addWidget(pBtn_ok);

        pBtn_close = new QPushButton(Widget);
        pBtn_close->setObjectName(QString::fromUtf8("pBtn_close"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/images/cancle.png"), QSize(), QIcon::Normal, QIcon::Off);
        pBtn_close->setIcon(icon3);
        pBtn_close->setIconSize(QSize(13, 13));

        horizontalLayout_3->addWidget(pBtn_close);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Widget);
        QObject::connect(pBtn_clean, &QPushButton::clicked, plainTextEdit, qOverload<>(&QPlainTextEdit::clear));
        QObject::connect(pBtn_close, &QPushButton::clicked, Widget, qOverload<>(&QWidget::close));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\345\255\227\344\275\223", nullptr));
        ckBox_underline->setText(QCoreApplication::translate("Widget", "\344\270\213\345\210\222\347\272\277", nullptr));
        checkBox_italic->setText(QCoreApplication::translate("Widget", "\346\226\234\344\275\223", nullptr));
        checkBox_bold->setText(QCoreApplication::translate("Widget", "\345\212\240\347\262\227", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "\351\242\234\350\211\262", nullptr));
        radioButton_black->setText(QCoreApplication::translate("Widget", "\351\273\221\350\211\262", nullptr));
        radioButton_red->setText(QCoreApplication::translate("Widget", "\347\272\242\350\211\262", nullptr));
        radioButton_blue->setText(QCoreApplication::translate("Widget", "\350\223\235\350\211\262", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("Widget", "Hello World!", nullptr));
        pBtn_clean->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272", nullptr));
        pBtn_ok->setText(QCoreApplication::translate("Widget", "\347\241\256\345\256\232", nullptr));
        pBtn_close->setText(QCoreApplication::translate("Widget", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
