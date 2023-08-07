#include "SumCalculatorDialog.h"

// 构造函数
// 使用方法 2 需要将私有成员 ui 进行初始化
SumCalculatorDialog::SumCalculatorDialog(void) : ui(new Ui::SumCalculator) {
    // 窗口初始化
    ui->setupUi(this);

    // 设置数字验证器
    ui->m_editX->setValidator(new QDoubleValidator(this));
    ui->m_editY->setValidator(new QDoubleValidator(this));

    // 结果
    ui->m_editANS->setReadOnly(true);   // 设置为只读

    // 信号和槽函数的连接
    connect(ui->m_editX, SIGNAL(textChanged(QString)), this, SLOT(enabledButton()));
    connect(ui->m_editY, SIGNAL(textChanged(QString)), this, SLOT(enabledButton()));
    connect(ui->m_equal, &QPushButton::clicked, this, &SumCalculatorDialog::calc);
}

// 析构中 delete ui;
SumCalculatorDialog::~SumCalculatorDialog() {
    delete ui;
}

void SumCalculatorDialog::calc(void) {
    // QString::toDouble(bool*) 将 QString 转换为 double, 
    double res = ui->m_editX->text().toDouble() + ui->m_editY->text().toDouble();

    // QString::number() 将指定的数字按照格式转化为字符串
    QString str = QString::number(res);

    // 讲结果显示在文本框中
    ui->m_editANS->setText(str);
}

void SumCalculatorDialog::enabledButton(void) {
    bool X_OK, Y_OK;
    // QLineEdit::text() 获取单行编辑框文本 
    // QString::toDouble(bool*) 将 QString 转换为 double, 如果成功 bool* 输出型参数设置为 true, 否则设置为 false
    ui->m_editX->text().toDouble(&X_OK);
    ui->m_editY->text().toDouble(&Y_OK);

    // 当左右操作数都正确的输入了数字时, 按钮可用, 否则禁用
    ui->m_equal->setEnabled(X_OK && Y_OK);
}
