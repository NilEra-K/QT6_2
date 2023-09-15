#include "locatedialog.h"
#include "ui_locatedialog.h"

LocateDialog::LocateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LocateDialog)
{
    ui->setupUi(this);
}

LocateDialog::~LocateDialog()
{
    delete ui;
}
