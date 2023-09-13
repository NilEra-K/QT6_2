#include "sizedialog.h"
#include "ui_sizedialog.h"

sizeDialog::sizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sizeDialog)
{
    ui->setupUi(this);
}

sizeDialog::~sizeDialog()
{
    delete ui;
}
