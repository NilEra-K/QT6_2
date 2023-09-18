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

// 根据主窗口选中的单元格设置 spinBox 的最大值
void LocateDialog::setSpinMax(int rowCnt, int columnCnt) {
    ui->spinRow->setMaximum(rowCnt - 1);
    ui->spinColumn->setMaximum(columnCnt - 1);
    // 或者可以使用
    // ui->spinRow->setRange(0, rowCnt - 1);
    // ui->spinColumn->setRange(0, columnCnt - 1);
}

// 根据主窗口选中的单元格设置 spinBox 的当前值
void LocateDialog::setSpinValue(int rowNo, int colNo) {
    ui->spinRow->setValue(rowNo);
    ui->spinColumn->setValue(colNo);
}

// 窗口关闭事件处理函数: 当对话框关闭时, 发送信号, 使能 actLocate 事件
void LocateDialog::closeEvent(QCloseEvent *event) {
    Q_UNUSED(event)
    emit changeActionEnable(true);
}

// 窗口显示事件处理函数: 当对话框显示时, 发送信号, 禁用 actLocate 事件
void LocateDialog::showEvent(QShowEvent *event) {
    Q_UNUSED(event)
    emit changeActionEnable(false);
}

// "设定文字" 按钮点击
void LocateDialog::on_btnSetText_clicked() {
    int rowNo = ui->spinRow->value();
    int colNo = ui->spinColumn->value();
    QString text = ui->lineEdit->text();
    emit changeCellText(rowNo, colNo, text);
}
