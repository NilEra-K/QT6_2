#include <QApplication>
#include "TimeDialog.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    TimeDialog tDialog;
    tDialog.show();    
    return app.exec();
}