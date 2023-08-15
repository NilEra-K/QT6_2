#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit); // 为中心控件布局, 将文本编辑框设置为中心控件

    // 初始化代码设计部分 UI
    initUi();
    connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(spinBox_valueChanged(int)));
    connect(cmbFont, SIGNAL(currentIndexChanged(int)), this, SLOT(cmbFont_currentIndexChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUi() {
    // 状态栏
    labelCurFile = new QLabel("当前文件: ");
    labelCurFile->setMinimumWidth(350);
    ui->statusbar->addWidget(labelCurFile); // 将 labelCurFile 标签加入 statusbar

    // 工具栏
    spinBox = new QSpinBox;
    spinBox->setRange(8, 48);   // 设置字体大小的范围
    spinBox->setValue(ui->textEdit->font().pointSize());  // 将 textEdit 的默认字体大小设置为当前 SpinBox 的初始值
    spinBox->setMinimumWidth(50);

    cmbFont = new QFontComboBox;
    cmbFont->setMinimumWidth(150);

    ui->toolBar->addWidget(new QLabel(" 字体大小 "));
    ui->toolBar->addWidget(spinBox);
    ui->toolBar->addWidget(new QLabel(" 字体 "));
    ui->toolBar->addWidget(cmbFont);
}

// 粗体
void MainWindow::on_actFontBold_triggered(bool checked) {
    // 多行编辑框没有直接修改粗体的属性, 使用 QTextCharFormat 来进行设置
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();    // 获取当前格式
    if(checked){
        fmt.setFontWeight(QFont::Bold);
    } else {
        fmt.setFontWeight(QFont::Normal);
    }
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

// 斜体
void MainWindow::on_actFontItalic_triggered(bool checked) {
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    fmt.setFontItalic(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

// 下划线
void MainWindow::on_actFontUnderLine_triggered(bool checked) {
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    fmt.setFontUnderline(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

// 是否允许剪切/复制/粘贴: 更新 cut/copy/paste 的 enabled 属性
void MainWindow::on_textEdit_copyAvailable(bool b) {
    ui->actCut->setEnabled(b);
    ui->actCopy->setEnabled(b);
    ui->actPaste->setEnabled(ui->textEdit->canPaste()); // 获取是否可用粘贴的状态: 剪切板缓冲区有数据
}

// 更新粗体/斜体/下划线 的 checked 属性, 检查其是否被选中
void MainWindow::on_textEdit_selectionChanged() {
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    ui->actFontBold->setChecked(fmt.font().bold()); // bold() 函数, 返回是否为粗体
                                                    // 如果返回值是 true, 则设置为选中
                                                    // 否则设置为未选中
    ui->actFontItalic->setChecked(fmt.font().italic());
    ui->actFontItalic->setChecked(fmt.fontItalic());
    ui->actFontUnderLine->setChecked(fmt.fontUnderline());
}

void MainWindow::spinBox_valueChanged(int fontSize) {
    QTextCharFormat fmt;
    fmt.setFontPointSize(fontSize);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::cmbFont_currentIndexChanged(int font) {
    QTextCharFormat fmt;
    QString fontName = QFontComboBox::itemText(font);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

