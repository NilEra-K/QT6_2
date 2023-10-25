#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostInfo>
#include <QUdpSocket>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initHost();
    // 获取本机 IP 地址
    QString getLocalIP();

private slots:
    void onStateChanged(QAbstractSocket::SocketState socketState);
    void onReadyRead();

    void on_actBind_triggered();

    void on_actDisbind_triggered();

    void on_btnSend_clicked();

    void on_btnBoardcast_clicked();

    void on_actTextClear_triggered();

private:
    Ui::MainWindow *ui;
    QUdpSocket* udpSocket;
    QLabel* labelSocketState;
};
#endif // MAINWINDOW_H
