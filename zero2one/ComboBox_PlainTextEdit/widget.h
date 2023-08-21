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

    void on_chkEditable_clicked(bool checked);

    void on_btnListClear_clicked();

    void on_btnAddText2Cmb_clicked();

    void on_btnTextClear_clicked();

    void on_chkReadOnly_clicked(bool checked);

    void on_plainTextEdit_customContextMenuRequested(const QPoint &pos);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
