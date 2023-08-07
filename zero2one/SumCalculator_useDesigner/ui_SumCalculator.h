/********************************************************************************
** Form generated from reading UI file 'SumCalculator.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUMCALCULATOR_H
#define UI_SUMCALCULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SumCalculator
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *m_editX;
    QLabel *m_plus;
    QLineEdit *m_editY;
    QPushButton *m_equal;
    QLineEdit *m_editANS;

    void setupUi(QDialog *SumCalculator)
    {
        if (SumCalculator->objectName().isEmpty())
            SumCalculator->setObjectName(QString::fromUtf8("SumCalculator"));
        SumCalculator->resize(523, 114);
        verticalLayout = new QVBoxLayout(SumCalculator);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_editX = new QLineEdit(SumCalculator);
        m_editX->setObjectName(QString::fromUtf8("m_editX"));
        m_editX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(m_editX);

        m_plus = new QLabel(SumCalculator);
        m_plus->setObjectName(QString::fromUtf8("m_plus"));
        m_plus->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(m_plus);

        m_editY = new QLineEdit(SumCalculator);
        m_editY->setObjectName(QString::fromUtf8("m_editY"));
        m_editY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(m_editY);

        m_equal = new QPushButton(SumCalculator);
        m_equal->setObjectName(QString::fromUtf8("m_equal"));
        m_equal->setEnabled(false);

        horizontalLayout->addWidget(m_equal);

        m_editANS = new QLineEdit(SumCalculator);
        m_editANS->setObjectName(QString::fromUtf8("m_editANS"));
        m_editANS->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_editANS->setReadOnly(true);

        horizontalLayout->addWidget(m_editANS);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SumCalculator);

        QMetaObject::connectSlotsByName(SumCalculator);
    } // setupUi

    void retranslateUi(QDialog *SumCalculator)
    {
        SumCalculator->setWindowTitle(QCoreApplication::translate("SumCalculator", "\345\212\240\346\263\225\345\231\250", nullptr));
        m_plus->setText(QCoreApplication::translate("SumCalculator", "+", nullptr));
        m_equal->setText(QCoreApplication::translate("SumCalculator", "=", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SumCalculator: public Ui_SumCalculator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUMCALCULATOR_H
