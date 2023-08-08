#include "calculatordialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalculatorDialog w;
    w.show();
    return a.exec();
}
