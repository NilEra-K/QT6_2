/********************************************************************************
** Form generated from reading UI file 'timerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMERDIALOG_H
#define UI_TIMERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TimerDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnTimer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *TimerDialog)
    {
        if (TimerDialog->objectName().isEmpty())
            TimerDialog->setObjectName(QString::fromUtf8("TimerDialog"));
        TimerDialog->resize(406, 600);
        verticalLayout = new QVBoxLayout(TimerDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(TimerDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnTimer = new QPushButton(TimerDialog);
        btnTimer->setObjectName(QString::fromUtf8("btnTimer"));

        horizontalLayout_2->addWidget(btnTimer);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(TimerDialog);

        QMetaObject::connectSlotsByName(TimerDialog);
    } // setupUi

    void retranslateUi(QDialog *TimerDialog)
    {
        TimerDialog->setWindowTitle(QCoreApplication::translate("TimerDialog", "\345\233\276\345\203\217\351\232\217\346\234\272\346\265\217\350\247\210\345\231\250", nullptr));
        btnTimer->setText(QCoreApplication::translate("TimerDialog", "\345\274\200\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimerDialog: public Ui_TimerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMERDIALOG_H
