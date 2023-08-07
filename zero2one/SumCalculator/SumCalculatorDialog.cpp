#include "SumCalculatorDialog.h"

// 构造函数
SumCalculatorDialog::SumCalculatorDialog(void) {
    // 窗口初始化
    setWindowTitle("加法计算器");   // 设置当前窗口标题, this->setWindowTitle(...)
    // 操作数 -> this 为当前父窗口指针
    m_editX = new QLineEdit(this);
    m_editY = new QLineEdit(this);

    // 设置文本对齐方式 -> 水平右对齐
    m_editX->setAlignment(Qt::AlignRight);
    m_editY->setAlignment(Qt::AlignRight);

    // 设置数字验证器 -> 只能输入数字
    // setValidator(const QValidator*); -> QValidator 是 QDoubleValidator的基类
    m_editX->setValidator(new QDoubleValidator(this));
    m_editY->setValidator(new QDoubleValidator(this));

    // 结果
    m_editANS = new QLineEdit(this);
    m_editANS->setAlignment(Qt::AlignRight);
    m_editANS->setReadOnly(true);   // 设置为只读

    // "+"
    m_plus = new QLabel("+", this);

    // "="
    m_equal = new QPushButton("=", this);
    m_equal->setEnabled(false);     // 设置等于号按钮不可用

    // 创建布局器, 并按水平方向依次添加控件
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(m_editX);
    layout->addWidget(m_plus);
    layout->addWidget(m_editY);
    layout->addWidget(m_equal);
    layout->addWidget(m_editANS);

    // 设置为当前窗口的布局器, this可以省略
    this->setLayout(layout);

    // 信号和槽函数的连接
    connect(m_editX, SIGNAL(textChanged(QString)), this, SLOT(enabledButton()));
    connect(m_editY, SIGNAL(textChanged(QString)), this, SLOT(enabledButton()));
    connect(m_equal, &QPushButton::clicked, this, &SumCalculatorDialog::calc);
}

SumCalculatorDialog::~SumCalculatorDialog() { }

void SumCalculatorDialog::calc(void) {
    // QString::toDouble(bool*) 将 QString 转换为 double, 
    double res = m_editX->text().toDouble() + m_editY->text().toDouble();

    // QString::number() 将指定的数字按照格式转化为字符串
    QString str = QString::number(res);

    // 讲结果显示在文本框中
    m_editANS->setText(str);
}

void SumCalculatorDialog::enabledButton(void) {
    bool X_OK, Y_OK;
    // QLineEdit::text() 获取单行编辑框文本 
    // QString::toDouble(bool*) 将 QString 转换为 double, 如果成功 bool* 输出型参数设置为 true, 否则设置为 false
    m_editX->text().toDouble(&X_OK);
    m_editY->text().toDouble(&Y_OK);

    // 当左右操作数都正确的输入了数字时, 按钮可用, 否则禁用
    m_equal->setEnabled(X_OK && Y_OK);
}
