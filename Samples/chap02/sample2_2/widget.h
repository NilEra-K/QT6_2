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
    void on_ckBox_underline_clicked(bool checked);

    void on_checkBox_italic_clicked(bool checked);

    void on_checkBox_bold_clicked(bool checked);

    void do_FontColor();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
