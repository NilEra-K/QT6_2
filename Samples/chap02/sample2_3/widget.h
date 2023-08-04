#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QCheckBox;
class QRadioButton;
class QPlainTextEdit;
class QCheck;
class QPushButton;

class Widget : public QWidget
{
    Q_OBJECT
private:
    QCheckBox* chkBox_underline;
    QCheckBox* chkBox_italic;
    QCheckBox* chkBox_bold;

    QRadioButton* radioButton_red;
    QRadioButton* radioButton_blue;
    QRadioButton* radioButton_black;

    QPlainTextEdit* txtEdit;

    QPushButton* pBtn_ensure;
    QPushButton* pBtn_clear;
    QPushButton* pBtn_close;
private slots:
    void do_chkBox_underline(bool checked);
    void do_chkBox_bold(bool checked);
    void do_chkBox_italic(bool checked);
    void do_setFontColor();
    void do_clearTxtEdit();
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
