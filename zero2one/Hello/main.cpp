#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

int main(int argc, char** argv){
    // 创建应用程序对象
    QApplication app(argc, argv);

    QWidget parent;             // 定义 QWidget 窗口
    parent.move(500, 400);      // 相对于 Desktop 的位置
    parent.resize(300, 200);    // 设置 Widget 大小

    // 创建标签控件
    QLabel label("Hello QT", &parent);  // 设置父窗口为 parent
    label.move(50, 40);                 // 相对于 parent 的位置
    label.resize(200, 40);              // 设置 Label 大小

    // 创建按钮控件
    QPushButton button("退出", &parent);
    button.move(90, 120);
    button.resize(120, 40);

    // 标签和按钮设置了父窗口, 可以直接显示父窗口
    // label.show();
    // button.show();
    parent.show();

    // 进入主事件循环并等待 exit() 被调用
    return app.exec();
}


