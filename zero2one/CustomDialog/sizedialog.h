#ifndef SIZEDIALOG_H
#define SIZEDIALOG_H

#include <QDialog>

namespace Ui {
class sizeDialog;
}

class sizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit sizeDialog(QWidget *parent = nullptr);
    ~sizeDialog();

private:
    Ui::sizeDialog *ui;
};

#endif // SIZEDIALOG_H
