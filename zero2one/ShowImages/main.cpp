#include "showimagesdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShowImagesDialog w;
    w.show();
    return a.exec();
}
