#include "LoginDialog.h"

// 构造函数
LoginDialog::LoginDialog(void) : ui(new Ui::LoginDialog){
    // 界面初始化
    ui->setupUi(this);
}

// 析构函数
LoginDialog::~LoginDialog(void) {
    delete ui;
}

