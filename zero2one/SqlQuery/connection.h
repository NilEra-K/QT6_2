#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>

static bool createConn(void) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");   // 创建 QSqlDatabase 对象
    db.setHostName("localhost");    // 设置主机名或 IP 地址, 本机为 localhost 或 127.0.0.1
    db.setUserName("root");
    db.setPassword("00098498");
    db.setDatabaseName("emp");
    db.setPort(3306);
    if(!db.open()) {
        QMessageBox::critical(NULL, "连接数据库", "连接数据库失败\n" + db.lastError().text());
        return false;
    }
    return true;
}

#endif // CONNECTION_H
