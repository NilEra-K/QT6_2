#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHostInfo>
#include <QNetworkInterface>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QString protocolName(QAbstractSocket::NetworkLayerProtocol protocol);

private slots:
    void on_btnGetLocalHostInfo_clicked();

    void on_btnGetDomainHostInfo_clicked();

    // 使用 lookUpHost(const QString& name, QObject* receiver, const char* member)
    // @param name: 一个主机名(host name)
    // @param receiver: 接收者
    // @param member: 槽函数, 此处是 member 的示例定义
    void lookedUp(const QHostInfo& host);

    void on_btnTextClear_clicked();

    void on_btnAllAddresses_clicked();

    void on_btnAllInterfaces_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
