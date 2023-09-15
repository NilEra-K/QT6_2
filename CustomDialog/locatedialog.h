#ifndef LOCATEDIALOG_H
#define LOCATEDIALOG_H

#include <QDialog>

namespace Ui {
class LocateDialog;
}

class LocateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LocateDialog(QWidget *parent = nullptr);
    ~LocateDialog();

private slots:

private:
    Ui::LocateDialog *ui;
};

#endif // LOCATEDIALOG_H
