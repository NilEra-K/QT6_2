## Hello

编译过程(以 `Hello` 为例):
1. `qmake -project` 生成 `Hello.pro` 文件
2. `vi Hello.pro` 修改 `Hello.pro` 文件, 添加相应的模块
3. `qmake` 生成 `Makefile` 文件
4. `make` 生成可执行程序 -> Windows下可以使用 `mingw32-make`

需要注意添加 `qmake` 的环境变量, `MinGW` 的环境变量

## Close
初识信号与槽

## Slider_SpinBox
初识 滑块(QSlider) 和 选值框(QSpinBox), 使用信号与槽机制保持同步
- `QSlider`
  - `void setRange(int min, int max);` 设置滑动范围
  - `void valueChanged(int)` 滑块滑动时发送信号(信号函数)
  - `void setValue(int)` 设置当前位置(槽函数)
- `QSpinBox`
  - `void setRange(int min, int max)` 设置数值改变范围
  - `void valueChanged(int)` 选值框数值改变时发送信号(信号函数)
  - `void setValue(int)` 设置当前数值(槽函数)

## SumCalculator
实现加法器, 了解面向对象的 QT 编程
- 输入两个数字, 按 "=" 按钮显示计算结果
- 两个操作数必须都是合法的数字, 拒绝接受任何非法字符
- 两个操作数必须全部合法, "=" 按钮才被激活, 否则禁用(不可以点击)
- 显示结果的控件只可查看不可修改, 但支持复制到剪贴板
- 所有子窗口的大小和位置随主窗口的缩放自动调整至最佳

## GetSysTime
获取系统时间, 使用面向对象的 Qt 编程技术创建获取时间窗口
- 点击按钮, 通过自定义的槽函数获取时间并显示到标签
- 发送自定义信号

## SumCalculator_useDesigner
使用 Designer 实现加法器布局, 了解使用 `uic` 的编译过程: <p>
`uic SumCalculator.ui -o ui_SumCalculator.h`

## Login
使用 Designer 设计登录对话框, 了解 `lineEdit` 控件的 `echoMode` 属性, 可以防止密码明文显示
- 点击 "OK" 按钮判断输入用户名或密码是否正确
- 如错误弹出信息提示框, 可以重新登录
- 点击 "Cancel" 按钮, 则退出登录 


