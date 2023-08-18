#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnListInit_clicked();

    void on_btnCityZone_clicked();

    void on_cmbSimple_currentTextChanged(const QString &arg1);

    void on_cmbCityZone_currentTextChanged(const QString &arg1);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
