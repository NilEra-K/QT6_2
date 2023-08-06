#include <QApplication>
#include <QPushButton>
#include <QLabel>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    QLabel label("Push Button To Kill Me");
    label.resize(200, 50);
    label.show();

    QPushButton button("End Label");
    button.resize(200, 50);
    button.show();

    // 信号和槽函数的连接
    QObject::connect(&button, SIGNAL(clicked()), &label, SLOT(close()));

    // 函数指针形式调用 connect 函数
    // QObject::connect(&button, &QPushButton::clicked, &label, &QWidget::close);

    return app.exec();
}


