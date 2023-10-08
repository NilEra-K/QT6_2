#include "widget.h"
#include "ui_widget.h"
#include <QMetaEnum>

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

// 根据协议类型获取字符串形式的协议名称
QString Widget::protocolName(QAbstractSocket::NetworkLayerProtocol protocol) {
    // 通过 QMetaEnum 类获取对象的枚举信息
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::NetworkLayerProtocol>();
    qDebug() << "metaEnum.keyCount() = " <<metaEnum.keyCount();
    qDebug() << "protocol = " << protocol;
    return metaEnum.valueToKey(protocol);
}

// QHostInfo - 获取本地主机名 和 IP地址
void Widget::on_btnGetLocalHostInfo_clicked() {
    QString localName = QHostInfo::localHostName();         // 获取本机主机名
    ui->plainTextEdit->appendPlainText("本机主机名 : " + localName + "\n");
    QHostInfo hostInfo = QHostInfo::fromName(localName);    // 通过获取的主机名获取主机信息
    QList<QHostAddress> addrList = hostInfo.addresses();    // 获取主机信息中的地址信息列表
    if(!addrList.isEmpty()) {
        for(int i = 0; i < addrList.count(); i++) {
            QHostAddress addr = addrList.at(i);                 // 每一项就是一个 QHostAddress 对象
            bool ipv4ShowOnly = ui->ckbIPv4Only->isChecked();   // 是否勾选 "只显示 IPv4" 复选框
            bool isIPv4 = (addr.protocol() == QAbstractSocket::IPv4Protocol); // 使用 protocol() 函数确定当前地址的协议
                                                                              // 使用枚举值来确定 IPv4/IPv6/IPv4&IPv6/Others几种协议
            if((ipv4ShowOnly && isIPv4) || !ipv4ShowOnly) {
                ui->plainTextEdit->appendPlainText("协议 : " + protocolName(addr.protocol()));
                ui->plainTextEdit->appendPlainText("IP地址 : " + addr.toString());
                ui->plainTextEdit->appendPlainText("\n");
            }
        }
    }
}

// QHostInfo - 查找域名的 IP 地址
void Widget::on_btnGetDomainHostInfo_clicked() {
    QString hostName = ui->editDomainName->text();
    ui->plainTextEdit->appendPlainText("正在查找主机信息: " + hostName);
    QHostInfo::lookupHost(hostName, this, SLOT(lookedUp(QHostInfo)));
}

// 查找主机信息的槽函数
void Widget::lookedUp(const QHostInfo& hostInfo) {
    QList<QHostAddress> addrList = hostInfo.addresses();    // 获取主机信息中的地址信息列表
    if(!addrList.isEmpty()) {
            for(int i = 0; i < addrList.count(); i++) {
            QHostAddress addr = addrList.at(i);                 // 每一项就是一个 QHostAddress 对象
            bool ipv4ShowOnly = ui->ckbIPv4Only->isChecked();   // 是否勾选 "只显示 IPv4" 复选框
            bool isIPv4 = (addr.protocol() == QAbstractSocket::IPv4Protocol); // 使用 protocol() 函数确定当前地址的协议
                                                                              // 使用枚举值来确定 IPv4/IPv6/IPv4&IPv6/Others几种协议
            if((ipv4ShowOnly && isIPv4) || !ipv4ShowOnly) {
                ui->plainTextEdit->appendPlainText("协议 : " + protocolName(addr.protocol()));
                ui->plainTextEdit->appendPlainText("IP地址 : " + addr.toString());
                ui->plainTextEdit->appendPlainText("\n");
            }
        }
    }
}

// 清空文本框
void Widget::on_btnTextClear_clicked() {
    ui->plainTextEdit->clear();
}

// QNetworkInterface::allAddresses
void Widget::on_btnAllAddresses_clicked() {
    QList<QHostAddress> addrList = QNetworkInterface::allAddresses();
    if(!addrList.isEmpty()) {
        for(int i = 0; i < addrList.count(); i++) {
            QHostAddress addr = addrList.at(i);                 // 每一项就是一个 QHostAddress 对象
            bool ipv4ShowOnly = ui->ckbIPv4Only->isChecked();   // 是否勾选 "只显示 IPv4" 复选框
            bool isIPv4 = (addr.protocol() == QAbstractSocket::IPv4Protocol); // 使用 protocol() 函数确定当前地址的协议
                                                                              // 使用枚举值来确定 IPv4/IPv6/IPv4&IPv6/Others几种协议
            if((ipv4ShowOnly && isIPv4) || !ipv4ShowOnly) {
                ui->plainTextEdit->appendPlainText("协议 : " + protocolName(addr.protocol()));
                ui->plainTextEdit->appendPlainText("IP地址 : " + addr.toString());
                ui->plainTextEdit->appendPlainText("\n");
            }
        }
    }
}

// QNetworkInterface::allInterfaces
void Widget::on_btnAllInterfaces_clicked() {
    QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();    // 获取网络接口列表
    if(interfaceList.isEmpty()) { return; }
    for(int i = 0; i < interfaceList.count(); i++) {
        QNetworkInterface interface = interfaceList.at(i);
        if(!interface.isValid()) { continue; }
        ui->plainTextEdit->appendPlainText("设备名称 : " + interface.humanReadableName());
        ui->plainTextEdit->appendPlainText("硬件地址 : " + interface.hardwareAddress());
        QList<QNetworkAddressEntry> entryList = interface.addressEntries();
        for(int j = 0; j < entryList.count(); j++) {
            QNetworkAddressEntry entry = entryList.at(j);
            ui->plainTextEdit->appendPlainText("    IP 地址 : " + entry.ip().toString());
            ui->plainTextEdit->appendPlainText("    广播地址 : " + entry.broadcast().toString());
            ui->plainTextEdit->appendPlainText("    子网掩码 : " + entry.netmask().toString() + "\n");
        }
        ui->plainTextEdit->appendPlainText("\n");
    }
}

