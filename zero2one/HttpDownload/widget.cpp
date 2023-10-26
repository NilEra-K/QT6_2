#include "widget.h"
#include "ui_widget.h"
#include <QDir>
#include <QMessageBox>
#include <QDesktopServices>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

// 缺省路径
void Widget::on_btnDefaultPath_clicked() {
    QString curPath = QDir::currentPath();
    QDir dir(curPath);
    QString sub = "temp";
    dir.mkdir(sub);
    ui->editSavePath->setText(curPath + '/' + sub + '/');   // 拼接缺省路径字符串
}

// 下载
void Widget::on_btnDownload_clicked() {
    // trimmed() 函数用于去除空格
    QString urlSpec = ui->editURL->text().trimmed();
    if(urlSpec.isEmpty()) { // 如果指定的 URL 为空
        QMessageBox::critical(this, "下载", "请指定要下载的 URL");
        return;
    }

    QUrl newUrl = QUrl::fromUserInput(urlSpec); // 从用户的输入获取 URL
    if(!newUrl.isValid()) { // 验证 URL 是否合法
        QMessageBox::critical(this, "下载", QString("无效的URL: %1 \n 错误: %2").arg(urlSpec, newUrl.errorString()));
        return;
    }

    QString tempDir = ui->editSavePath->text().trimmed();
    if(tempDir.isEmpty()) { // 保证保存路径不为空
        QMessageBox::critical(this, "下载", "请指定保存下载文件的路径");
        return;
    }

    QString fullFileName = tempDir + newUrl.fileName();
    if(QFile::exists(fullFileName)) { // 如果原本存在该文件直接删除将其删除(一种覆盖的写方式)
        QFile::remove(fullFileName);
    }
    downloadFile = new QFile(fullFileName);
    if(!downloadFile->open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "下载", "临时文件打开失败");
        return;
    }
    ui->btnDownload->setEnabled(false);
    reply = networkManager.get(QNetworkRequest(newUrl)); // 发送 Get 请求

    // 绑定信号与槽
    connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));
    connect(reply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(reply, SIGNAL(finished()), this, SLOT(onFinished()));
}

// 读取下载数据
void Widget::onReadyRead() {
    downloadFile->write(reply->readAll()); // 将响应中能读到的数据写入文件中
}

// 下载进度
void Widget::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal) {
    ui->progressBar->setMaximum(bytesTotal);
    ui->progressBar->setValue(bytesReceived);
}

// 网络响应结束
void Widget::onFinished() {
    QFileInfo fileInfo;
    fileInfo.setFile(downloadFile->fileName());
    downloadFile->close();
    delete downloadFile;    downloadFile = nullptr;
    reply->deleteLater();   reply = nullptr;
    if(ui->chkIsOpen->isChecked()) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
    }
    ui->btnDownload->setEnabled(true);
}
