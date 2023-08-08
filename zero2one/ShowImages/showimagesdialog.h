#ifndef SHOWIMAGESDIALOG_H
#define SHOWIMAGESDIALOG_H

#include <QDialog>
#include <QPainter> // 画家类
#include <QImage>   // 图片类

QT_BEGIN_NAMESPACE
namespace Ui { class ShowImagesDialog; }
QT_END_NAMESPACE

class ShowImagesDialog : public QDialog
{
    Q_OBJECT

public:
    ShowImagesDialog(QWidget *parent = nullptr);
    ~ShowImagesDialog();
protected:
    // 绘图事件处理函数
    void paintEvent(QPaintEvent* event);

private:
    Ui::ShowImagesDialog *ui;
    int m_index;    // 图片索引
};
#endif // SHOWIMAGESDIALOG_H
