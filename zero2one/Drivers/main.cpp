#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList driverList = QSqlDatabase::drivers();
    foreach (QString str, driverList) {
        qDebug() << str;  // qDebug(str)
    }
    return a.exec();
}
