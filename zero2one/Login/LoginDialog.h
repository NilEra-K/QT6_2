#ifndef __LOGINDIALOG_H
#define __LOGINDIALOG_H

#include "ui_LoginDialog.h"
#include <QMessageBox>  // 消息提示框
#include <QDebug>

class LoginDialog : public QDialog {
    Q_OBJECT
private:
    Ui::LoginDialog* ui;
public:
    LoginDialog(void);
    ~LoginDialog(void);
};

#endif // __LOGINDIALOG_H