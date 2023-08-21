#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void timerEvent(QTimerEvent* event);

private:
    Ui::Widget *ui;
    int m_timerID;
};
#endif // WIDGET_H
