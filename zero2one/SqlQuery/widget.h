#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QMessageBox>

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
    void on_btnSelect_clicked();

    void on_btnInsert_clicked();

    void on_btnUpdate_clicked();

    void on_btnDelete_clicked();

private:
    void loadDept();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
