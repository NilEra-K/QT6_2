#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMetaEnum>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    labelSocketState = new QLabel("Socket 状态 :");
    labelSocketState->setMaximumWidth(200);
    ui->statusbar->addWidget(labelSocketState);

    // 本机 IP
    initHost();
    QString localIP = getLocalIP();
    setWindowTitle(windowTitle() + "--本机 IP: " + localIP);
    // ui->cmbTargetIP->addItem(localIP);

    // 创建 QUdpSocket 对象
    udpSocket = new QUdpSocket(this);

    ui->actBind->setEnabled(true);
    ui->actDisbind->setEnabled(false);

    // 信号与槽函数连接
    connect(udpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(onReadRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initHost() {
    QString hostName = QHostInfo::localHostName();          // 本地主机名
    QHostInfo hostInfo = QHostInfo::fromName(hostName);     // 本地主机信息
    QString localIP = "";
    QList<QHostAddress> addrList = hostInfo.addresses();    // IP 地址列表
    if(!addrList.isEmpty()) {
        for(int i = 0; i < addrList.count(); i++) {
            QHostAddress addr = addrList.at(i);
            if(addr.protocol() == QAbstractSocket::IPv4Protocol) { // 只要得到本机的一个 IPv4 地址就直接退出循环
                localIP = addr.toString();
                ui->cmbTargetIP->addItem(addr.toString(), QVariant(addr.toString()));
                // break;
            }
        }
    }
}

// 获取本机 IP
QString MainWindow::getLocalIP() {
//    QString hostName = QHostInfo::localHostName();          // 本地主机名
//    QHostInfo hostInfo = QHostInfo::fromName(hostName);     // 本地主机信息
//    QString localIP = "";
//    QList<QHostAddress> addrList = hostInfo.addresses();    // IP 地址列表
//    if(!addrList.isEmpty()) {
//        for(int i = 0; i < addrList.count(); i++) {
//            QHostAddress addr = addrList.at(i);
//            if(addr.protocol() == QAbstractSocket::IPv4Protocol) { // 只要得到本机的一个 IPv4 地址就直接退出循环
//                localIP = addr.toString();
//                // break;
//            }
//        }
//    }
    QString localIP = ui->cmbTargetIP->currentText();
    setWindowTitle(windowTitle() + "--本机 IP: " + localIP);
    return localIP;
}

void MainWindow::onStateChanged(QAbstractSocket::SocketState socketState) {
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    labelSocketState->setText("Socket 状态: " + QString(metaEnum.valueToKey(socketState)));
}

// 绑定端口
void MainWindow::on_actBind_triggered() {
    quint16 port = ui->spinBindPort->value();   // 绑定 UDP 端口
    if(udpSocket->bind(port)) { // 绑定端口成功
        ui->plainTextEdit->appendPlainText(">>> 已成功绑定");
        ui->plainTextEdit->appendPlainText(">>> 绑定端口 : " + QString::number(udpSocket->localPort()));
        ui->actBind->setEnabled(false);
        ui->actDisbind->setEnabled(true);
    } else {
        ui->plainTextEdit->appendPlainText(">>> 绑定失败");
    }
}

// 解除绑定
void MainWindow::on_actDisbind_triggered() {
    udpSocket->abort();     // 直接断开绑定(立即关闭套接字), 未写入数据全部丢弃
    ui->actBind->setEnabled(true);
    ui->actDisbind->setEnabled(false);
    ui->plainTextEdit->setPlainText(">>> 已解除绑定");
}

// 发送消息
void MainWindow::on_btnSend_clicked() {
    QString targetIP = ui->cmbTargetIP->currentText();  // 目标 IP
    QHostAddress targetAddr(targetIP);
    qint16 targetPort = ui->spinTargetPort->value();
    QString msg = ui->editMessage->text();
    QByteArray str = msg.toUtf8();
}

