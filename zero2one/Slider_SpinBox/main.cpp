#include <QApplication>
#include <QSpinBox>
#include <QWidget>
#include <QSlider>

int main(int argc, char** argv){
    QApplication app(argc, argv);

    QWidget parent;
    parent.move(600, 400);
    parent.resize(200, 100);

    QSlider slider(&parent);                // 定义滑块
    slider.setOrientation(Qt::Horizontal);  // 设置滑块为水平
    slider.move(25, 30);
    slider.resize(100, 30);
    slider.setRange(0, 100);                // 设置滑动范围

    QSpinBox spinBox(&parent);
    spinBox.move(130, 30);
    spinBox.resize(45, 30);
    spinBox.setRange(0, 100);               // 设置滑动范围

    QObject::connect(&spinBox, SIGNAL(valueChanged(int)), &slider, SLOT(setValue(int)));
    // QObject::connect(&spinBox, &QSpinBox::valueChanged, &slider, &QSlider::setValue);
    QObject::connect(&slider, &QSlider::valueChanged, &spinBox, &QSpinBox::setValue);
    parent.show();
    return app.exec();
}
