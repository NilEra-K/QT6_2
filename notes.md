# Notes 笔记

**[补充] 参考相关博客** <p>
- 虚函数相关
  - **https://blog.csdn.net/zhang_cherry/article/details/108647349**
  - **https://blog.csdn.net/xuebing1995/article/details/103695355**
  - **https://blog.csdn.net/yuanchunsi/article/details/78833345**
---

**QT框架功能描述** <p>
QT 框架中的模块分为两大类:
- ***QT基本模块(Qt Essentials) :*** 提供了 Qt 在所有平台上的基本功能
- ***QT附加模块(Qt Add-Ons) :*** 实现了一些特定功能的模块

| 模块 | 描述 |
| :-: | :-: |
| `Qt Core` | Qt 框架的核心, 定义了元对象系统 |
| `Qt GUI` | 设计 GUI 界面的基础类, 包括事件处理、文字处理等 |
| `Qt Widgets` | 提供用于创建 GUI 的各种界面组件类 |
| `Qt D-Bus` | D-Bus 是用于实现进程间通信(Inter Process Communication, IPC) 和 远程过程调用(Remote Procedure Call, RPC)的一种通信协议 |
| `Qt Test` | 提供一些对应用程序和库进行单元测试的类 |
| `Qt QML` | 提供用 QML 编程的框架, 定义了 QML 和基础引擎 |
| `Qt Quick` | 用于开发 QML 应用程序的标准库, 提供创建 UI 的一些基本类型 |
| `Qt Quick Controls` | 提供一套基于 Qt Quick 的控件,可用于创建复杂的UI |
| `Qt Quick Dialogs` | 提供通过 QML 使用系统对话框的功能 |
| `Qt Quick Layouts` | 提供用于管理界面布局的QML类型 |
| `Qt Quick Test` | 提供 QML 应用程序的单元测试框架 |

**Object 类**
- **元对象 (Meta Object) :** 每个 QObject及其子类的实例都有一个元对象 (静态变量 staticMetaObject)  函数 `metaObject()` 可以返回它的指针
- **类型信息 :** QObject的 `inherits()` 函数可以判断继承关系 
- **动态翻译 :** 函数 `tr()` 返回一个字符串的翻译版本
- **对象树 :** 表示对象间从属关系的树状结构 QObject 提供了 `parent()`、`children()`、`findChildren()` 等函数, 当对象树中的某个对象被删除时, 它的子对象也将被删除
- **信号和槽 :** 对象间的通信机制 
- **属性系统 :** 可以使用宏 `Q_PROPERTY` 定义属性, QObject 的`setProperty()` 会设置属性的值或定义动态属性; `property()`函数会返回属性的值

**QT 父窗口**
- 创建控件时, 可以指定停靠在某个父窗口上面, 这时控件将作为子窗口被束缚在其父窗口的内部, 并伴随父窗口一起移动、隐藏、显示和关闭; 否则该控件将作为独立窗口显示在屏幕上, 且游离于其它窗口之外
- QWidget及其子类的对象可以做为其它控件的父窗口常用的父窗口类有如下三个
  - `QWidget`
  - `QMainWindow` 主窗口, QWidget的直接子类
  - `QDialog` 对话框, QWidget的直接子类
- 父窗口的析构函数回自动销毁其所有的子窗口对象, 因此即使子窗口对象是通过 `new` 操作符动态创建的, 可以不显式的执行 `delete` 操作, 而且不用担心内存泄漏的问题, 只要保证父窗门对象被正确销毁, 其子窗口也将随之被销毁
- 设置窗口的位置和大小
  - `void move(int x, int y);`
  - `void resize(int x, int y);`

---

**QT 信号与槽**
- 什么是信号和槽
  - 信号和槽是 QT 自定义的一种通信机制, 实现对象之间的数据交互
  - 当用户或系统触发了一个动作, 导致某个控件的状态发生了改变, 该控件就会发射一个信号, 即调用其类中一个特定的成员函数(信号), 同时还可能携带有必要的参数
  - 槽和普通的成员函数几乎没有太多区别, 可以是公有的、保护的或私有的, 可以被重载也可以被覆盖, 其参数可以是任意类型, 并可以像普通成员函数一样调用
  - 槽函数与普通成员函数的差别并不在于其语法特性, 而在于其功能, 槽函数更多体现为对某种特定信号的处理, 可以将槽和其它对象信号建立连接, 这样当发射信号时, 槽函数将被触发和执行, 进而来完成具体功能 
- **信号的定义**
  ```
  class X : public QObject {    // X 类必须派生自 QObject 类, 或其子类
                                // 可以是 QObject 的子类, 也可以是其子类的子类
      Q_OBJECT                  // 使用信号与槽机制必须添加 Q_OBJECT 宏
  signals:                      // 不需添加任何访问修饰符
      void signal_func(...);    // 信号函数
  };
  ```
  ***注意 :*** 信号函数只需要声明, 不能写定义
- **槽函数的定义**
  ```
  class X : public QObject {
      Q_OBJECT
  public slots:
      void slot_func(...) { ... }   // 槽函数
  };
  ```
  ***注意 :*** 槽函数可以连接到某个信号上, 当信号被发射时, 槽函数将被触发, 另外槽函数也可以被当作普通的成员函数被直接调用
- 信号与槽的连接 <p>
  `QObject::connect(const QObject* sender, const char* signal, const QObject* receiver, const char* method);`
  - 参数
    - `sender` 信号发送的对象指针
    - `signal` 要发送的信号函数, 可以用 `SIGNAL(...)` 宏进行类型转换
    - `receiver` 信号的接收对象指针
    - `method` 接收信号后要执行的槽函数, 可以使用 `SLOT(...)` 宏进行类型转换
- 信号与槽连接的语法要求
  - 信号与槽参数要一致 <p>
    `QObject::connect(A, SIGNAL(sigfunc(int)), B, SLOT(slotfunc(int)));` **-> 正确** <p>
    `QObject::connect(A, SIGNAL(sigfunc(int)), B, SLOT(slotfunc(int, int)));` **-> 错误**
  - 可以有缺省参数 <p>
    `QObject::connect(A, SIGNAL(sigfunc(int)), B, SLOT(slotfunc(int, int = 0)));` **-> 正确**
  - 信号函数的参数可以多于槽函数, 多余的参数将被忽略
    `QObject::connect(A, SIGNAL(sigfunc(int, int)), B, SLOT(slotfunc(int)));` **-> 正确**
- 信号与槽连接的应用
  - 一个信号可以被连接到多个槽 <p>
    `QObject::connect(A, SIGNAL(sigfunc(int)), B1, SLOT(slotfunc1(int)));` <p>
    `QObject::connect(A, SIGNAL(sigfunc(int)), B2, SLOT(slotfunc2(int)));`
  - 多个信号可以被连接到一个槽  <p>
    `QObject::connect(A1, SIGNAL(sigfunc1(int)), B, SLOT(slotfunc(int)));` <p>
    `QObject::connect(A2, SIGNAL(sigfunc2(int)), B, SLOT(slotfunc(int)));`
  - 两个信号可以直接连接(信号级连) - 了解即可 <p>
    `QObject::connect(A1, SIGNAL(sigfunc1(int)), A2, SIGNAL(sigfunc2(int)));`

---

**面向对象的 QT 编程** <p>
***基于对象的 QT 编程***
- 完全不使用任何面向对象技术, 而只是利用Qt所提供的类创建对象, 并诉用对象的接口以满足用户的需求是可能的, 但这样构建的应用程序其功能必然是十分有限的
- 首先, Qt类保护成员中的诸多实现无法在类的外部被复用, Qt试图通过多态实现的很多机制, 如事件处理, 完全无法使用
- 再次, Qt提供的信号和槽不可能满足用户所有的需求, 自定义信号和槽需要面向对象技术
- 最后, Qt Designer、Qt Creator等工具链都在以面向对象的方式使用Qt, 不能反其道而行之

---

**QT Designer (QT 设计师)**
- 在指定目录下输入 `designer` 进入 QT Designer, 进入 QT Designer 后可以进行可视化的 UI 编辑, 当成功布局好 UI 后按住 `ctrl + S` 进行重命名保存
- 使用 `uic` 进行编译, 将 XML 文件转换为 C++ 头文件
- 使用头文件中自动生成的界面相关代码, 完成代码编写
  - **方法 1:** 通过继承方式, 将界面相关代码继承过来直接使用
  - **方法 2:** 通过组合方式, 添加一个界面类的成员变量(ui), 通过该成员访问界面相关的代码, 实际开发中, 推荐这种方法

---

**QT Creator (QT 创造器)**
- 在任意目录下, 执行 `qtcreator` , 进入 QT 集成开发环境界面(Windows 下需要将对应的环境变量进行添加)
- 在欢迎界面选择 "New Project" 创建新项目

---

**QT 事件**
- 事件的概念
  - 在Qt中, 是以事件驱动 UI工具集, 包括信号与槽都依赖于 Qt 的事件处理机制
  - 通常事件是由窗口系统或者 Qt 自身产生的, 用以响应所发生的各类事情, 比如用户按下并释放了键盘或者鼠标、窗口因缩放而需要重绘、定时器到期而应有所动作
  - 如下图可以看到事件比信号更原始, 一个下压式按钮首先感受到的是鼠标事件, 在进行必要的处理以产生按钮下沉继而弹起的视觉效果之后, 才会发射 `clicked()` 信号

![](./src/QT_Event.png)
- **如何处理事件**
  - 在 Qt 中, 事件被封装成对象, 所有的事件对象类型都继承自抽象类 `QEvent` , 当事件发生时, 首先被调用的是 `QObject` 类中的虚函数`event()` , 其参数 `QEvent` 标识了类型
  - 在 Qt 桌面应用(Qt Widgets Application)开发中, QWidget类覆盖了其基类中的 `event()`, 并根据具体事件调用具体事件处理函数:
    - `void QWidget::mousePressEvent(QMouseEvent* e);` 鼠标按下事件
    - `void QWidget:mouseReleaseEvent(QMouseEvent* e);` 鼠标抬起事件
    - `void QWidget::mouseMoveEvent(QMouseEvent* e);` 标移动事件
    - `void QWidget::paintEvent(QPaintEvent* e);` 绘图事件
  - **所有的事件处理函数都是虚函数**, 可以被 QWidget 的子类覆盖, 以提供针对不同窗口控件类型的事件处理, 控件的使用者所关心的往往是定义什么样的槽处理什么样的信号, 而控件的实现者则更关心覆盖哪些事件处理函数
  - 如果程序员希望在窗口中自定义的处理事件, 可以**继承 QWidget** 或者其子类, 比如**QDialog、QMainWindow** , 在自定义的窗口子类中重写事件处理函数, 当相应事件被触发时, 会利用多态的语法机制, 所执行到的事件处理函数将是子类中重写的版本, 从而实现程序员想要的事件处理效果

---

**QT 常用事件** <p>
***绘图事件***
- 通过绘图事件, 可以实现自定义的图像绘制, 当有下列情况之一发生时, 将触发窗口的绘制事件, 即 **QWidget** 类的 `paintEvent()` 虚函数会被调用:
  - 窗口被创建以后第一次显示出来
  - 窗口由隐藏状态转变为可见状态
  - 窗口由最小化状态转变为正常或最大化状态
  - 窗口因尺寸大小的变化需要呈现更多的内容
  - **QWidget** 类的 `update()/repaint()` 成员函数被调用
- 如果希望在自己的窗口中显示某个图像, 在 **QWidget** 的窗口子类中可以重写绘图事件函数 `paintEvent` , 在其中可用 **QPainter(Qt二维图形引擎)** 实现指定的**图像绘制、渲染**等操作

***定时器事件***
- Qt 通过两套机制为应用程序提供定时功能
  - 定时器事件, 由 `QObject` 提供
  - 定时器信号, 由 `QTimer` 提供
- 通过定时器事件实现定时器
  - `int QObject:startTimer(int interval);` 启动定时器, 以后每隔 `interval` 毫秒触发一次定时器事件, **返回定时器 ID**
  - `void QObject::timerEvent(QTimerEvent*);` **虚函数** , 定时器事件处理函数
  - `void QObject::killTimer(int id);` 关闭参数 `id` 所标识的定时器

***鼠标事件***
- `QWidget` 类定义了以下虚函数提供对鼠标事件的处理, 其参数 `QMouseEvent` 描述了鼠标事件的细节, 如发事件的鼠标按键、鼠标所在位置等
  - `virtual void mousePressEvent (QMouseEvent* e);` 鼠标按下
  - `virtual void mouseReleaseEvent(QMouseEvent* e);` 鼠标抬起
  - `virtual void mouseDoubleClickEvent(QMouseEvent* e);` 鼠标双击
  - `virtual void mouseMoveEvent(QMouseEvent* e);` 鼠标移动

***键盘事件***
- `QWidget` 类定义了以下虚函数提供对键盘事件的处理, 其参数 `QKeyEvent` 描述了键盘事件的细节, 如引发事件的键盘按键文本等
  - `virtual void keyPressEvent (QKeyEvent* e);` 按键按下
  - `virtual void keyReleaseEvent(QKeyEvent* e);` 按键抬起

---

**混合方式 UI 设计** 
- 可视化 UI 设计无需人工编写代码区处理大量繁琐的界面组件的创建和布局管理工作, 可以直观地进行界面设计, 大大提高工作效率, **但某些组件无法可视化地添加到界面上 ( 例如状态栏、工具栏的部分功能等 )**
- 采用纯代码方式进行 UI 设计虽然无所不能, 但是设计效率太低, 过程非常繁琐
- 混合方式创建UI, 即部分界面设计用UI设计器可视化实现, 部分无法在 UI 设计器里实现的界面设计用代码实现

***主窗口***
- `QMainWindow` 是一个为用户提供主窗口程序的类, 包含一个菜单栏多个工具栏、多个停靠控件、一个状态栏以及一个中心控件, 是许多应用程序(如文本编辑器、图片编辑器等)的基础
- Qt主窗口界面布局如下图
  ![](./src/MainWindowLayout.png)
- 主窗口具有自己的布局管理器因此不允许在主窗口上设置或创建布局管理器, 但是在中心控件上可以设置
- **菜单栏**
  - 菜单是一系列命令的列表, 为了实现菜单、工具栏按钮、键盘快捷方式等命令的一致性, **QT 使用动作(Action)来表示这些命令**
  - Qt 的菜单就是由一系列的 **QAction 动作对象** 构成的列表
  - 菜单栏是包含菜单的面板, 位于主窗口标题栏的下面一个主窗口只能有一个菜单栏
- **工具栏**
  - 工具栏是由一系列的类似于按钮的动作排列而成的面板, 它通常由一些经常使用的命令(动作)组成
  - 工具栏位于菜单栏的下面、状态栏的上面, 可以停靠在主窗口的上下左右四个方向
  - 一个主窗口可以包含多个工具栏
- **状态栏**
  - 位于应用程序底部, 用于显示应用程序状态的一些信息
- **QAction**
  - `QAction` 类提供了抽象的用户界面 *action* , 这些 *action* 可以被放置在窗口控件
  - `QAction` 可以被添加到菜单和工具栏中, 并且可以自动保持在菜单和工具栏中的同步。
  - `QAction` 是可以作为独立的对象被创建, 也可以在构建菜单时创建
  - `QAction` 可以包含一个*图标* 、*菜单文本* 、*快捷键* 、*状态文本* 等
  - 只有将 `QAction` 添加到窗口控件上, 才可以使用这些 `QAction`

---

**常用 UI 设计控件** <p>
***常用输入显示控件***
- QLabel
- QLineEdit
  - QLabel 用于显示字符串, QLineEdit 用于显示和输入字符串, 这两个类都有如下两个函数用于读取和设置显示字符串:
    - `QString text() const`
    - `void setText(const QString &)`
- QSpinBox
- QDoubleSpinBox
  | 属性名称 | 描述 |
  | :-: | :-: |
  | prefix | 数字显示的前缀, 例如 '$', 前缀不会被获取, 仅作显示的效果 |
  | suffix | 数字显示的后缀, 例如 'kg', 后缀不会被获取, 仅作显示的效果 |
  | minimum | 数值范围的最小值, 如 0 |
  | maximum | 数值范围的最大值, 如 255 |
  | singlestep | 步长, 点击右侧上下调整按钮时的单步改变值, 如 1、0.1 等 |
  | value | 当前显示的值, 不包含前缀 |
  | displayIntegerBase | QSpinBox 特有的属性, 显示整数使用的进制, 如 2 表示而进制 |
  | decimals | QDoubleSpin 特有的属性, 显示数值的小数位置, 如 2 显示两位小数 |

***日期时间和日历控件***
- 日期时间类型
  - QTime : 时间数据类型, 仅表示时间, 如: 15:23:20
  - QDate : 日期数据类型, 仅表示日期, 如: 2023-08-16
  - QDateTime : 日期时间数据类型, 表示日期和时间, 如 2023-08-16 15:23:20
- 日记时间控件
  - QTimeEdit : 编辑和显示时间的控件
  - QDateEdit : 编辑和显示日期的控件
  - QDateTimeEdit : 编辑和显示日期时间的控件
  - QCalendarWidget : 一个用日历形式选择日期的控件
- QCalendarWidget 日历控件
  - 信号
    - `void QCalendarWidget::selectionChanged()`

***QComboBox***
- 下拉列表框控件类
- 提供一个下拉列表供用户选择, 也可以直接当作一个 `QLineEdit` 用作输入
- 每个项(item, 或称列表项)可以关联一个 `QVariant` 类型的变量, 用于存储一些**不可见数据**
  - 在某些情况下, 我们可能希望将更多的数据与每个选项相关联, 例如一个整数、一个自定义对象等; 可以使用 `QVariant` 来保存和传递这些额外的数据
  - 可以使用 `QVariant` 构造函数将数据包装成 `QVariant` 对象, 然后使用 `addItem()` 函数将带有相关数据的选项添加到 `QComboBox` 中
  - 在需要访问选定的选项及其关联的数据时, 可以使用 `currentData()` 函数获取与选定选项相关联的 `QVariant` 数据
    ```
    // 演示如何在 QComboBox 中添加带有相关数据的选项, 并使用 QVariant 来检索数据
    #include <QApplication>
    #include <QComboBox>
    #include <QDebug>

    int main(int argc, char *argv[]) {
        QApplication app(argc, argv);

        QComboBox comboBox;

        // 添加带有相关数据的选项
        int intValue = 42;
        QString stringValue = "Hello, QVariant!";
        QVariant variantInt(intValue);
        QVariant variantString(stringValue);

        comboBox.addItem("Option 1", variantInt);
        comboBox.addItem("Option 2", variantString);

        // 获取当前选中项的数据
        QVariant currentData = comboBox.currentData();
        if (currentData.canConvert<int>()) {
            int selectedInt = currentData.toInt();
            qDebug() << "Selected Int:" << selectedInt;
        } else if (currentData.canConvert<QString>()) {
            QString selectedString = currentData.toString();
            qDebug() << "Selected String:" << selectedString;
        }
        comboBox.show();
        return app.exec();
    }
    ```
  - `QVariant` 是一个非常通用的类型, 几乎所有类都能转换为 `QVariant` , 类似于 `union` 联合 , 然后再通过 `toX` 函数转换为原类型
- 常用函数
  - 添加项 <p>
    `void addItem(const QString& text, const QVariant& userData = QVariant())` <p>
    `void addItem(const QIcon& icon, const QString& text, const QVariant& userData = QVariant())`
  - 访问项 <p>
    **返回当前项的序号, 从 0 开始 :** `int currentIndex()` <p>
    **返回当前项的文字 :** `QString currentText()` <p>
    **返回当前项的关联数据 :** `QVariant currentData(int role=Qt::UserRole)` <p>
    **返回指定索引号的项的文字 :** `QString itemText(int index)` <p>
    **返回指定索引号的项的关联数据 :** `QVariant itemData(int index, int role=Qt::UserRole)` <p>
    **返回项的个数 :** `int count()`
  - 常用信号 <p>
    `void currentIndexChanged(int index)` <p>
    `void currentIndexChanged(const QString& text)`

***QPlainTextEdit***
- 用于编辑多行文本的编辑器, 可以编辑普通文本
- `QPlainTextEdit` 提供 `cut()`、`copy()`、`paste()`、`undo()`、`redo()`、`clear()`、`selectAll()` 等标准功能的槽函数, `QPlainTextEdit` 还提供一个标准的右键快捷菜单
- `QPlainTextEdit` 常用函数
  - 添加项字符串 <p>
    `QPlainTextEdit::appendPlainText(const QString& text)`
  - 读取所有文字
    `QString QPlainTextEdit::toPlainTextEdit() const`
  - 逐行读取需要使用 `QTextDocument` 类<p>
    `QTextDocument* QPlainTextEdit::document() const` <p>
    `int QTextDocument::blockCount()` <p>
    `QTextBlock QTextDocument::findBlockByNumber(int blockNumber)`
- 常用信号 <p>
  **为信号生成槽函数, 在槽函数中生成 QPlainTextEdit 的标准右键菜单** `customContextMenuRequested()`
- 自定义的右键菜单需要手动设置, 在 `QPlainTextEdit` 控件的 `contextMenuPolicy` 属性中设置值为 `Qt::CustomContextMenu` 可以将指定的自定义右键菜单进行显示
- 需要注意的是, 右键菜单显示的时候需要指定位置, 我们一般不使用默认的位置, 而是希望该位置和我们期待的位置重合

***QListWidget***
- QT 中用于项 (Item) 处理的组件有两类 :
  - **Item Views (包括 QListView、QTableView、QTreeView)**
  - **Item Widgets(包括 QListWidget、QTableWidget、QTreeWidget)**
- QListWidget 提供一个基于 *项* 的列表控件
- 常用函数
  - 添加项 <p>
    `void addItem(const QString& label)` <p>
    `void addItem(QListWidgetItem* item)` <p>
    `void addItems(const QStringList& labels)`
  - 插入项 <p>
    `void insertItem(int row, QListWidgetItem* item)` <p>
    `void insertItem(int row, const QString& label)` <p>
    `void insertItems(int row, const QStringList& labels)` <p>
  - 删除项 <p>
    `QListWidgetItem* takeItem(int row)` 按照行号删除相应的项, 需要注意的是, 该函数只是再控件列表中将该项移除, 在内存中并没有移除, 我们需要手动通过 `delete` 移除
  - 获取项 <p>
    `QListWidgetItem* item(int row) const`
    `QListWidgetItem* itemAt(const QPoint& p) const`
    `QListWidgetItem* itemAt(int x, int y) const`
  - 常用信号 <p>
    `void currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)` <p>
    `void currentRow(int currentRow)`
- QListWidgetItem 是 QListWidget 中的一个项

***QToolButton***
- 使用 `void QToolButton::setDefaultAction(QAction* action)` 来实现 `QToolButton` 和 `QAction` 之间的关联

***QSplitter***
- 可以用于分割两部分控件

---

**QT Model/View 模型**
- **Model/View** 结构是 QT 中用户界面组件显示与编辑数据的一种结构
  - View(视图) 是显示和编辑数据的界面组件
  - Model(模型) 是视图与原始数据之间的接口
- GUI 应用程序的一个很重要的功能是由用户在界面上编辑和修改数据, 典型的**如数据库应用程序** , 在数据库应用程序中, 用户在界面上执行各种操作, 实际上是修改了界面组件相关的数据库内的数据
- **将界面组件与所编辑的数据分离开来 , 又通过数据源的方式连接起来** , 是处理界面与数据的一种较好的方式
- Model/View 的基本结构如图:
  ![](../QT6_2/src/ModelViewBase.png)
  - **数据(Data) :** 实际的数据, 可能在内存中, 可能在文件中, 也可能在数据库中
  - **视图(View) :** 屏幕上的**界面组件**
  - **模型(Model) :** 与实际数据通信, 并为视图组件提供数据接口
  - **代理(Delegate) :** 可以让用户定制数据的界面和编辑方式
- 模型、视图和代理之间使用信号与槽通信
  - 源数据发生变化时, 模型发射信号通知视图组件
  - 用户再界面操作数据时, 视图发射信号
  - 编辑数据时, 代理发射信号告知模型和视图编辑器目前的状态
- **模型**
  ![](../src/../QT6_2/src/ModelStruct.png)
  - 抽象类不能直接使用, 需要子类继承来实现一些纯虚函数, QT 提供了一些模型类用于项数据处理, 常见的几个类如下表所示——
    | Model 类 | 用途 |
    | :-: | :-: |
    | QStringListModel | 用于处理字符串列表数据的数据模型类 |
    | QStandardItemModel | 标准的基于项数据的数据模型类, 每个项数据可以是任何数据类型 |
    | QFileSystemModel | 计算机上文件系统的数据模型类 |
    | QSortFilterProxyModel | 用于数据库SQL查询结果的数据模型类 |
    | QSqlQueryModel | 用于数据库SQL查询结果的数据模型类 |
    | QSqlTableModel | 用于数据库的一个数据表的数据模型类 |
    | QSqlRelationalTableModel | 用于关系型数据表的数据模型类 |
- **视图**
  ![](../src/../QT6_2/src/ViewStruct.png)
  - 视图组件(View) 就是现实数据模型的数据的界面组件, QT 提供的视图组件如下——
    | View 类 | 用途 |
    | :-: | :-: |
    | QListView | 用于显示单列的列表数据, 适用于一维数据的操作 |
    | QTreeView | 用于显示树状结构数据, 适用于树状结构数据的操作 |
    | QTableView | 用于显示表格状数据, 适用于二维表格型数据的操作 |
    | QColumnView | 用多个 QListView 显示树状层次结构, 树状结构的一个层用一个 QListView 显示 |
    | QHeaderView | 提供行表头活列表头的视图组件, 如 QTableView 的行表头和列表头 |
  - QListWidget、QTableWidget、QTreeWidget 是其基类的简便类, 适用于数据量
  - 通过 `setModel()` 函数设置视图
- **代理**
  ![](../QT6_2/src/DelegateStruct.png)
  - 代理就是在视图组件上为编辑数据提供编辑器
  - 代理负责从数据模型获取相应的数据, 然后显示在编辑器里, 修改数据后, 又将其保存到数据模型中
  - **QAbstractItemDelegate** 是所有代理类的基类, 作为抽象类, 它不能直接使用, 它的一个子类 **QStyledItemDelegate**, 是 QT 的视图组件缺省使用的代理类
  - 对于一些特殊的数据编辑要求, 可以从 **QStyledItemDelegate** 继承创建自定义代理类
- **相关概念**
  - 数据模型的基本结构
    ![](../QT6_2/src/MV-BasicStruct.png)
  - 模型索引
    - **`QModelIndex`** 表示模型索引的类
    - 模型索引提供数据存取的一个临时指针, 用于通过数据模型提取或修改数据
  - 行号和列号
    - 表格数据模型中的三个数据项 A、B、C , 获取其模型索引的代码是: <p>
      `QModelIndex indexA = model->index(0, 0, QModelIndex())` <p>
      `QModelIndex indexB = model->index(1, 1, QModelIndex())` <p>
      `QModelIndex indexC = model->index(2, 1, QModelIndex())`
  - 父项
    - 树状数据模型, 节点 A 和 节点 C 的父节点是顶层节点, 获取模型索引的代码是: <p>
      `QModelIndex indexA = model->index(0, 0, QModelIndex())` <p>
      `QModelIndex indexC = model->index(2, 1, QModelIndex())` <p>
    - 节点 B 的父节点是节点 A, 节点 B的模型索引由以下代码生成: <p>
      `QModelIndex indexB = model->index(1, 0, indexA)`
  - 项的角色 (enum Qt::ItemDataRole)
    - `DisplayRole` 数据是现实的字符串
    - `DecorationRole` 是用于装饰显示的属性
    - `ToolTipRole` 定义了鼠标的提示信息

**模型类 —— QFileSystemModel**
- QFileSystemModel 提供了一个可用于访问本机文件系统的数据模型
- QFileSystemModel 和视图结合使用, 可以显示本机上的文件系统
- 常用函数
  - `QString rootPath() const`
  - `bool isDir(const QModelIndex& index) const`
  - `QString filePath(const QModelIndex& index) const`
  - `QString fileName(const QModelIndex& index) const`
  - `QString type(const QModelIndex& index) const`
  - `qint64 size(const QModelIndex& index) const`
  - ...

**模型类 —— QStringListModel**
- `QStringListModel` 用于处理字符串列表的数据类型, 他可以作为 `QListView` 的数据模型, 在界面上显示和编辑字符串列表
- 常用函数
  - `void setString(const QStringList& string)`
  - `bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex)`
  - `bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex)`
  - `bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole)`

**模型类 —— QStandardItemModel**
- **QstandardltemModel** 是标准的以项数据 (Item Data) 为基础的标准数据模型类
- 通常与 **QTableView** 组合成 **Model/View** 结构, 实现通用的二维数据的管理功能
- 每个项是一个 **QStandardltem** 类的变量, 用于存储项的数据、字体格式、对齐方式等
- ***相关类***
  - **QTabelView**
    - 二维数据表视图组件
    - 有多个行和多个列, 每个基本显示单元是一个单元格
    - 通过 `setModel()` 函数设置一个 `QStandardItemModel` 类的数据模型
    - 一个单元格显示 `QStandardItemModel` 数据模型中的一个项
  - **QItemSelectionModel**
    - 一个用于跟踪视图组件的单元格选择状态的类
    - 当在 `QTabelView` 中选择某个单元格或多个单元格时, 通过 `QItemSelectionModel` 可以获得选中的单元格的模型索引, 为单元格的选择提供方便
- ***几个类的关系***
  - `QTableView` 是界面视图组件
  - 其关联的的数据模型是 `QStandardItemModel`
  - 关联的项选择模型是 `QItemSelectionModel`
  - `QStandardItemModel` 的数据管理的基本单元是 `QStandardItem`

---

**自定义代理**
- `QTableView` 控件为每个单元格提供的是缺省的代理编辑控件, 即一个 `QLineEdit` 控件, 在编辑框里可以输入任何数据, 所以比较通用
- 但是有些情况下, 希望根据数据的类型限定使用不同的编辑控件, 比如 : 性别更适合使用 `QComboBox` 控件
- 要实现这样的功能, 就需要为某个列或单元格设置自定义控件
  ![](../QT6_2/src/DelegateStruct.png)
- 我们通常继承 `QStyledItemDelegate` 类来实现自定义代理

**自定义代理类的基本设计要求**
- 自定义代理控件, 必须实现如下4个函数:
  - **`createEditor()` 函数 :** 创建用于编辑模型数据的 Widget 控件, 如一个 `QComboBox` 控件, 或者一个 `QSpinBox` 控件
  - **`setEditorData()` 函数 :** 从数据模型获取数据, 供 Widget 控件进行编辑
  - **`setModelData()` 函数 :** 将 Widget 上的数据更新到数据模型
  - **`updateEditorGeometry()` 函数 :** 用于给 Widget 控件设置一个合适的大小

---

**标准对话框**
- 5 种预定义的标准对话框
  | 对话框 | 常用静态函数 | 函数功能 |
  | :-: | :-: | :-: |
  | **`QFileDialog`** <p> _文件对话框_ | `QString getOpenFileName()` | 选择打开一个文件 |
  | - | `QStringList getOpenFileNames()` | 选择打开多个文件 |
  | - | `QString getSaveFileName()` | 选择保存一个文件 |
  | - | `QString getExistDirectory()` | 选择一个已有目录 |
  | - | `QUrl getOpenFileUrl()` | 选择打开一个文件, 可选择远程网络文件 |
  | **`QColorDialog`** <p> _颜色对话框_ | `QColor getColor()` | 选择颜色 |
  | **`QFontDialog`** <p> _字体对话框_ | `QFont getFont` | 选择字体 |
  | **`QInputDialog`** <p> _输入对话框_ | `QString getText()` | 输入单行文字 |
  | - | `int getInt()` | 输入整数 |
  | - | `double getDouble()` | 输入浮点数 |
  | - | `QString getItem()` | 从一个下拉列表框中选择输入 |
  | - | `QString getMultiLineText()` | 输入多行字符串 |
  | **`QMessageBox`** <p> _消息框_ | `StandardButton inforMmation()` | 消息提示对话框 |
  | - | `StandardButton question()` | 询问并获取是否确认的对话框 |
  | - | `StandardButton warning()` | 警告信息提示对话框 |
  | - | `StandardButton critical()` | 错误信息提示对话框 |
  | - | `void about()` | 设置自定义信息的关于对话框 |
  | - | `void aboutQt()` | 关于 Qt 的对话框 |

  ( "`-`" 在此表中表示同上 )
 
---

**自定义对话框** <p>
***自定义的不同调用方式***
- 自定义对话框的设计一般从 **QDialog** 继承
- 对话框的调用步骤
  - 创建对话框
  - 传递数据给对话框
  - 显示对话框获取输入
  - 判断对话框单机按钮的返回类型
  - 获取对话框输入数据
- 模态方式显示
  - 会阻塞本程序中其它的窗口, 直到对话框关闭对话框显示时
  - 返回 `DialogCode` 值
  - 函数 `int exec()`
- 非模态方式显示
  - 对话框显示时, 其它的窗口依旧可以操作
  - 函数: `void show()`
- 关于 `setWindowFlag` 使用为 `setWindowFlags` 错误的问题
  - `setWindowFlags` 使用的时候会先清除当前窗口的所有标志, 然后设置新的窗口标志, `Qt::Window` 这个标志被清除掉了
  - `Qt::Window`, 当窗口基类是 `QWidget` 时, 如果为其设置父窗口, 窗口会以子窗口的形式出现在父窗口中, 这时窗口没有标题栏关闭按钮等, 如果想使子窗口与父窗口绑定, 而且子窗口以独立窗口的形式存在, 则需要设置子窗口属性为 `Qt::Window`
  - 正确用法:
    - `dlgSize->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);`
    - `dlgSize->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);`

---

**QT 绘图、坐标系统和坐标变换** <p>
***`QPainter` 和 `QPaintDevice` 类***
- `QPainter` 是用来进行绘图操作的类
  - `QPainter` 绘图的主要属性:
    - `pen` 属性 : 是一个 `QPen` 对象, 用于控制线条的颜色、宽度、线型等
    - `brush` 属性 : 是一个 `QBrush` 对象, 用于设置一个区域的填充属性, 可以设置填充颜色、方式、渐变特性等, 还可以采用图片做材质填充
    - `font` 属性 : 是一个 `QFont` 对象, 用于绘制文字时, 设置文字的字体样式、大小等属性
- `QPaintDevice` 是一个可以使用 `QPainter` 进行绘图的抽象二维界面

***坐标系统和坐标变换***
- 常用的坐标变换函数
  | 分组 | 函数原型 | 功能 |
  | :-: | :-: | :-: |
  | 坐标变换 | `void translate(qreal dx, qreal dy)` | 坐标系统平移一定的偏移量, 坐标原点平移到新的点 |
  | 坐标变换 | `void rotate(qreal angle)` | 坐标系统顺时针旋转一个角度 |
  | 坐标变换 | `void scale(qreal sx, qreal sy)` | 坐标系统缩放 |
  | 坐标变换 | `void shear(qreal sh, qreal sv)` | 坐标系统做扭转变换 |
  | 状态保存与恢复 | `void save()` | 保存 painter 当前状态, 就是将当前状态压入栈 |
  | 状态保存与恢复 | `void restore()` | 恢复上一次状态, 就是在堆栈中弹出上次的状态 |
  | 状态保存与恢复 | `void resetTransform` | 复位所有坐标变换 |

---

**QT SQL 模块**
- **QT 6.2.4 解决 MySQL 8.0 驱动问题 :** https://blog.csdn.net/oh_MY_G0D/article/details/133103148
- **QT 6.2.4 解决 MySQL 8.0 驱动编译 :** https://blog.csdn.net/laomengnevergiveup/article/details/128848214
- **驱动下载地址 :** https://github.com/thecodemonkey86/qt_mysql_driver/releases/tag/qmysql_6.2.4
- 项目中使用**Qt SQL**模块, 需在项目配置文件中增加: `Qt += sql`
  | 驱动名 | 数据库 |
  | :-: | :-: |
  | `QDB2` | IBM DB2 (7.1及以上版本) 数据库 |
  | `QIBASE` | Borland InterBase 数据库 |
  | `QMYSQL` | MysQL 数据库 |
  | `QOCI` | Oracle 调用接口驱动 (Oracle Call Interface Driver) |
  | `QODBC` | Open Database Connectivity (ODBC) , Microsoft的 SQL Server 数据库以及其他支持 ODBC 接口的数据库, 如Access |
  | `QPSQL` | PostgreSQL (7.3及以上版本) 数据库
  | `QSQLITE2` | SQLite 2数据库 |
  | `QSQLITE` | SQLite 3数据库 |
  | `QTDS` | Sybase Adaptive Server, 注意: 从 Qt 4.7 开始已过时 |
- Qt SQL模块的主要类
  | 类名称 | 功能描述 |
  | :-: | :-: |
  | `QSqlDatabase` | 用于建立与数据库的连接 |
  | `QSqlError` | SQL数据库错误信息, 可以用于访问上一次出错的信息 |
  | `QSqlQuery` | 执行各种SQL语句的类 |
  | `QSqlQueryModel` | SQL查询结果集数据的**只读数据模型(data model)** , 用于 select 查询结果数据记录的只读显示 |
  | `QSqlRecord` | 封装了数据记录操作的类 |
- SQL模块使用步骤
  - 创建数据库连接 `QSqlDatabase`
    ```
    // mysql -h localhost -u root -p[pwd] emp -P 3306
    QSqlDatabase db = QSQLDatabase::addDatabase("驱动");
    db.setHostname("主机名 或 IP地址");
    db.setUserName("账号");
    db.setPassword("密码");
    db.setDatabaseName("数据库名");
    db.setPort("端口号");
    bool ok = db.open();
    ```
  - 执行 SQL 语句 `QSqlQuery`
    - `bool exec(const QString& query)` : 执行 `query` 所对应的 SQL 语句
    - `bool exec()` : 重载版本, 执行预编译的 SQL 语句 
    - `seek(int n)` : `query` 指向结果集的**第 n 条**记录
    - `first()` : `query` 指向结果集的**第 1 条**记录
    - `last()` : `query` 指向结果集的**最后 1 条**记录
    - `next()` : `query` 指向下一条记录, 每执行一次该函数, 便指向相邻的下一条记录
    - `previous()` : `query` 指向上一条记录, 每执行一次该函数，便指向相邻的上一条记录
    - `record()` : 获得现在指向的记录
    - `value(int n)` : 获得属性的值, 其中 n 表示查询的第 n 个字段, 该函数返回 `QVariant` 类型的数据
    - `at()` : 获得现在 `query` 指向的记录在结果集中的编号
- **`QSqlQueryModel`** 类
  - 数据库的操作一般需要将数据库的内容在界面上进行显示和编辑, Qt 采用 Model/View 结构进行数据库内容的界面显示
  - QTableView是常用的数据库内容显示视图组件
  - 用于数据库操作的数据模型类:
    - `QSqlQueryModel` 只读的数据模型
    - `QSqlTableModel` 普通的数据模型类型
    - `QSqlRelationalTableModel` 关系模型数据模型类型
  - **`QSqlQueryModel`** 常用函数
    - `void clear()` 清除数据模型, 释放所有获得的数据
    - `QSqlError lastError()` 返回上次的错误, 可获取错误的类型和文本信息
    - `QSqlQuery query()` 返回当前关联的 `QSqlQuery` 对象
    - `void setQuery(QSqlQuery &query)` 设置一个 `QSqlQuery` 对象, 获取数据
    - `void setQuery(QString &query)` 设置一个 **SELETE** 语句创建查询, 获取数据
    - `QSqlRecord record()` 返回一个空记录, 包含当前查询的字段信息
    - `QSqlRecord record(int row)` 返回行号为 **row** 的记录
    - `int rowCount()` 返回查询到的记录条数
    - `int columnCount()` 返回查询的字段个数
    - `void setHeaderData(int section, Qt::Orientation orientation, QVariant &value)` 设置表头数据, 一般用于设置字段的表头标题
- **`QSqlRecord` 类**
  - `QSqlRecord` 类记录了数据表的字段信息和一条记录的数据内容
  - `QSqlRecord` 类常用函数
    - `QVariant value(QString &name)` 返回字段名称为 **name** 的字段的值
    - `void setValue(QString &name, QVariant &val)` 设置字段名称为 **name** 的字段的值为 **val**
    - `QVariant value(int index)` 返回序号为 **index** 的字段的值
    - `void setValue(int index, Qvariant &val)` 设置序号为 **index** 的字段的值为 **val** 

---

**QT 多线程**

***QT 创建线程***
- 继承 `QThread`
  - 在 QT 中, `QThread` 类提供了一个平台独立的方式来管理线程, 每个 `QThread` 对象就是一个子线程
  - **在 QT 应用程序中如果想要开启子线程, 一种简单的方式是 *继承*** `QThread`, 重写 `QThread::run()` 函数, 将来通过调用 `QThread::start()` 即可开启子线程, 让 `run()` 在子线程中执行 
    ```
    // QThread 类
    class QThread {
    public:
        void start(...) {
            run();
        }
    protected:
        virtual void run() { // 虚函数
            exec();
        }
    }

    // 继承 QThread 类的的自定义线程类
    class MyThread:public QThread {
    protected:
        void run(void) {
            // 子线程要执行的功能
        }
    }

    // 使用
    MyThread thread;
    thread.start();
    ```
- `QThread` 类常用函数
  - 公有函数
    | 函数 | 功能 |
    | :-: | :-: |
    | `bool isFinished()` | 线程是否结束 |
    | `bool isRunning()` | 线程是否正在运行 |
    | `Priority priority()` | 返回线程的优先级 |
    | `void setPriority(Priority priority)` | 设置进程的优先级 |
    | `void exit(int returnCode=0)` | 退出线程的事件循环, 退出码为 **returnCode**, **0**表示成功退出; 否则表示有**错误** |
    | `bool wait(unsigned long time)` | 阻止线程执行, 直到线程结束(从 `run()` 函数返回), 或等待时间超过 **time** 毫秒 |
  - 公有槽函数
    | 函数 | 功能 |
    | :-: | :-: |
    | `void quit()` | 退出线程的事件循环, 并返回代码 0, 等效于 `exit(0)` |
    | `void start(Priority priority)` | 内部调用 `run()` 开始执行线程, 操作系统根据 `priority` 参数进行调度 |
    | `void terminate()` | 终止线程的运行, 但不是立即结束线程, 而是等待操作系统结束线程, 使用 `terminate()` 后应该使用 `wait()` <p> ***需要注意 : terminate() 并不是系统推荐的终止线程的方式, 建议开发人员自己定义终止线程方式或者使用其他方法***|
  - 信号
    | 函数 | 功能 |
    | :-: | :-: |
    | `void finished()` | 在线程就要结束时发送此信号 |
    | `void started()` | 在线程开始执行、`run()` 函数被调用之前发射此信号 |
  - 静态共有函数
    | 函数 | 功能 |
    | :-: | :-: |
    | `int idealThreadCount()` | 返回系统上能运行的线程的理想个数 |
    | `void msleep(unsigned long msecs)` | 强制线程休眠 `msecs` 毫秒 |
    | `void sleep(unsigned long secs)`| 强制线程休眠 `secs` 秒 |
    | `void usleep(unsigned long usecs)` | 强制当前线程休眠 `usecs` 微秒 |
  - 保护函数
    | 函数 | 功能 |
    | :-: | :-: |
    | `vitual void run()` | `start()` 调用 `run()` 函数开始线程任务的执行, 所以在 `run()` 函数中实现线程的任务功能 |
    | `int exec()` | 由 `run()` 函数调用, 进入线程的事件循环, 等待 `exit()` 退出 |

***线程同步***
- 为什么要使用线程同步——当多个线程对同一块内存进行访问时, 有可能会导致出现问题
- 线程同步的方式
  - QT 中提供线程同步的几种机制
    - `QMutex` 互斥锁(互斥量)
    - `QReadWriteLock` 读写锁
    - `QSemaphore` 信号量
    - `QWaitCondition` 条件等待
- **互斥锁 —— `QMutex` 和 `QMutexLocker` 类**
  - `QMutex` (互斥锁) 提供多线程间串行访问共享资源的方式, 本质上是基于相互排斥的锁, 也称为互斥量
  - `QMutex` 常用于在多线程中保护对象、数据结构或者代码段, 在同一时刻只能有一个线程可以拥有互斥量 **(更多内容详见手册)**
    - **`lock()` :** 锁定互斥量, 如果另外一个线程锁定了这个互斥量, 它将阻塞执行知道其他线程解锁这个互斥量
    - **`unlock()` :** 解锁一个互斥量, 需要与 lock() 配对使用
    - **`tryLock()` :** 试图锁定一个互斥量, 如果成功锁定就返回 `true`; 如果其他线程已经锁定了这个互斥量, 就返回 `false`, 但不阻塞程序的执行
  - `QMutexLocker` 是一个简化了互斥量处理的类
  - `QMutexLocker` 的构造函数接收一个互斥量作为参数并将其锁定, 析构函数则将此互斥量解锁, 所以在 `QMutexLocker` 实例变量的生存期内的代码段得到保护, 自动进行互斥量的锁定和解锁
  - `QMutexLocker(QMutex* mutex)`
  - **互斥锁(互斥量) 的不足**
    - 每次只能有一个线程获得互斥量的权限
    - 如果在一个程序中有多个线程读取某个变量, 使用互斥量时也必须排队, 而实际上若只是读取一个变量, 是可以让多个线程同时访问的, 这样互斥量就会降低程序的性能
- **读写锁 —— `QReadWriteLock`** 类
  - `QReadWriteLock` 以读或写锁定的同步方法允许以读或者写的方式保护一段代码
  - 可以允许多个线程以只读方式同步访问资源, 但是只要有一个线程在以写方式访问资源时, 其他线程就必须等待直到写操作结束
  - **`QReadWriteLock`** 提供的主要的函数
    - `lockForRead()` , 以只读方式锁定资源, 如果有其他线程以写入方式锁定这个函数会阻塞
    - `lockForWrite()` , 以写入方式锁定资源, 如果本线程或其他线程以读或写模式锁定资源, 这个函数就阻塞
    - `unlock()` , 解锁;
    - `tryLockForRead()` , 是 `lockForRead()` 的非阻塞版本
    - `tryLockForWrite()` , 是 `lockForWrite()` 的非阻塞版本
- **信号量 —— `QSemaphore`类**
  - 信号量 (Semaphore) 是一种限制对共享资源进行访问的线程同步机制, 它与互斥量 (Mutex) 相似, 但是有区别
  - 一个互斥量只能被锁定一次, 而信号量可以多次使用
  - 信号量通常用来保护一定数量的相同的资源
  - **`QSemaphore`** 提供的主要函数
    - `acquire(int n)` , 尝试获得 `n` 个资源, 如果没有这么多资源, 线程将阻塞直到有 `n` 个资源可用
    - `release(int n)` , 释放 `n` 个资源, 如果信号量的资源已全部可用之后再 `release()` , 就可以**创建**更多的资源, 增加可用资源的个数
    - `int available()` , **返回当前信号量可用的资源个数**, 这个数永远不可能为负数, 如果为 `0`, 就说明当前没有资源可用
    - `bool tryAcquire(int n=1)` , 尝试获取 `n` 个资源, 不成功时不阻塞线程
- **基于条件变量的线程同步 —— `QWaitCondition` 类**
  - `QWaitCondition` 与 `QMutex` 结合, 可以使一个线程在满足一定条件时通知其他一个或多个线程, 使它们及时作出响应, 这样比只使用互斥量效率要高一些
  - `QWaitCondition` 一般用于 _"生产者/消费者" (Producer/Consumer)模型中_
  - **`QWaitCondition`** 提供的主要函数
  - `wait(QMutex* lockedMutex)` , 解锁互斥量 `lockedMutex` , 并阻塞等待唤醒条件, 被唤醒后锁定 `lockedMutex` 并退出函数
  - `wakeAll()` , 唤醒所有处于等待状态的线程, 线程唤醒的顺序不确定, 由操作系统的调度策略决定
  - `wakeOne()` , 唤醒一个处于等待状态的线程, 唤醒哪个线程不确定由操作系统的调度策略决定
  - **程序员在编写代码时可能会遇到条件容易混淆的情况, 可用按照如下方式进行判断 :** *当执行 `wait()` 的时候说明条件不满足, 当前正处于该条件的反条件, 当执行 `wakeAll()` 或者 `wakeOne()` 时说明条件满足, 当前正处于该条件下* 

---

**QT 网络编程** <p>
使用时需要添加 `QT += network` <p>
***主机信息查询***
- **`QHostlnfo`类**
  - 公有函数
    | 函数原型 | 作用 |
    | :-: | :-: |
    | `QList<QHostAddress> addresses()` | 返回与hostName()主机关联的IP地址列表 |
    | `HostlnfoError error()` | 如果主机查找失败, 返回失败类型 |
    | `QString errorString()` | 如果主机查找失败, 返回错误描述字符串 |
    | `QString hostName()` | 返回通过IP查找的主机的名称 |
    | `int lookupId()` | 返回本次查找的ID |
  - 静态函数
    | 函数原型 | 作用 |
    | :-: | :-: |
    | `void abortHostLookup(int id)` | 中断主机查找 |
    | `QHostInfo fromName(QString& name)` | 返回指定的主机名的 IP 地址 |
    | `QString localDomainName()` | 返回主机 DNS 域名 |
    | `QString localHostName()` | 返回本机主机名 |
    | `int lookupHost(QString& name, QObject* receiver, char* member)` | **(该函数的使用方式需要仔细查阅手册)** 以异步方式根据主机名查找主机的 IP 地址, 并返回一个表示本次查找的 ID, 可用于 `abortHostLookup()` |
- **`QNetWorkInterface`类**
  - 公有函数
    | 函数原型 | 作用 |
    | :-: | :-: |
    | `QList<QNetwoekAddressEntry> addressEntries()`| 返回该网络接口(包括子网掩码和广播地址)的 IP 地址列表 |
    | `QString hardwareAddress()` | 返回该接口的低级硬件地址, 以太网里就是 `MAC` 地址 |
    | `QString humanReadableName()`| 返回人类可读的接口名称, 如果名称不确定, 得到的就是 `name()` 函数的返回值 |
    | `bool isValid()` | 如果接口有效即返回 `true` |
    | `QString name()` | 返回网络接口名称 |
  - 静态函数
    | 函数原型 | 作用 |
    | :-: | :-: |
    | `QList<QHostAddress> allAddresses()` | 返回主机上所有 IP 地址的列表 |
    | `QList<QNetworkInterface> allInterfaces()` | 返回主机上所有接口的网络列表 |

***TCP 通信***
- *TCP(Transmission Control Protocol)* 是一种被大多数 Internet网络协议 (如 HTTP 和 FTP)用于数据传输的低级网络协议, 它是可靠的、面向流、面向连接的传输协议, 特别适合用于连续数据传输
- TCP通信必须先建立TCP连接,  通信端分为客户端和服务器端
  ![](./src/QT_TCP.png)
- QT 提供 `QTcpSocket` 类和 `QTcpServer` 类用于建立 TCP 通信应用程序
- 服务器端程序必须使用 `QTcpServer` 用于端口监听, 建立服务器 ; `QTcpSocket` 用于建立连接后使用套接字 (Socket) 进行通信
- `QTcpServer` 是从 `QObject` 继承的类, 它主要用于服务器端建立网络监听, 创建网络 Socket 连接

- **`QTcpServer`类**
  - 公有函数
    | 函数 | 作用 |
    | :-: | :-: |
    | `void close()` | 关闭服务器 |
    | `bool listen()` | 监听 |
    | `bool isListening()` | 判断是否处于监听状态 |
    | `QTcpSocket* nextPendingConnection()` | 下一个未决的连接 |
    | `QHostAddress serverAddress()` | 获取服务器端 IP 地址 |
    | `quint16 serverPort()` | 获取服务器端端口号 |
    | `bool waitForNewConnection()` | 等待新的连接 |
  - 信号
    | 函数 | 作用 |
    | :-: | :-: |
    | `void acceptError(QAbstractSocket::SocketError socketError)` | 接收新的连接过程中出现错误 |
    | `void newConnection()` | 有一个新的连接变得可用 |
  - 保护函数
    | 函数 | 作用 |
    | :-: | :-: |
    | `incommingConnection(qintptr socketDescriptor)` |  |
    | `void addPendingConnection(QTcpSocket* socket)`| 添加未决连接 |
  - 简单流程
    ```
    // QTcpServer 类使用伪代码
    // 1. 开始监听
    bool QTcpServer::listen(const QHostAddress=QHostAddress::Any, quint16 port=0);
    // 2. 当客户端接入时, QTcpServer 调用 incomingConnection() 函数
    void QTcpServer::incomingConnection(qintptr socketDescriptor) {
        创建 QTcpSocket 对象;
        调用 addPendingConnection(QTcpSocket* socket)函数;
        发射 newConnection() 信号;
    }
    // 3. 在 newConnection() 信号连接的槽函数中, 调用 nextPendingConnection()
    // 获取下一个未决连接的 QTcpSocket 对象
    // 4. 使用 QTcpSocket 进行通信
    // 5. 关闭服务器, 停止监听
    void QTcpServer::close();
    ```
- **`QTcpSocket`类**
- `QTcpSocket` 是从 `QIODevice` 间接继承的类, 所以具有流读写的功能
- `QTcpSocket` 类除了构造函数和析构函数, 其他函数都是从 `QAbstractSocket` 继承或重定义的
- `QAbstractSocket` 用于TCP通信的主要接口函数如下:
  - 公有函数
    | 函数 | 作用 |
    | :-: | :-: |
    | `void connectToHost(QHostAddress& address,quint16 port)` | 连接到主机 |
    | `void disconnectFromHost()` | 从主机断开 |
    | `bool waitForConnected()` | 等待连接 |
    | `bool waitForDisconnected()` | 等待断开连接 |
    | `QHostAddress localAddress()` | 获取本地主机 |
    | `quint16 localPort()` | 获取本地端口 |
    | `QHostAddress peerAddress()` | 获取一对主机地址 |
    | `QString peerName()` | 获取一对主机名 |
    | `quint16 peerPort()` | 获取一对端口号 |
    | `qint64 readBufferSize()` | 读取缓冲区大小 |
    | `void setReadBufferSize(qint64 size)` | 设置读取缓冲区的大小 |
    | `qint64 bytesAvailable()` | 返回有多少可供读取的数据 |
    | `bool canReadLine()` | 判断是否能够读取一行 |
    | `QAbstractSocket:SocketState state()` | 返回当前套接字的状态 |

  - 信号
    | 函数 | 作用 |
    | :-: | :-: |
    | `void connection` | `connectToHost()` 成功连接到服务器后发射此信号  |
    | `void disconnected()` | 当Socket断开连接后发射此信号 |
    | `void error(QAbstractSocket::SocketError socketError)` | 当 Socket 发生错误时发射此信号 |
    | `void hostFound()` | 调用 `connectToHost()` 找到主机后发射此信号 |
    | `void stateChanged(QAbstractSocket::SocketState socketState)` | 当Socket 的状态变化时发射此信号, 参数 `socketState` 表示了 Socket 当前的状态 |
    | `void readyRead()` | 当缓冲区有新数据需要读取时发射此信号, 在此信号的槽函数里, 读取缓冲区的数据 |

  - 简单流程
    ```
    // 1. 连接到服务器
    void QAbstractSocket::connectToHost(const QHostAddress &address, quint16 port, QIODeviceOpenMode openMode=ReadWrite);
    // 尝试在给定的端口上, 创建一个到给定主机名的连接
    // protocol 参数用于指定使用的网络协议(IPV4/IPv6)
    // 连接过程:
    //     1> Socket 在给定 openMode 中打开
    //     2> QAbstractSocket 进入 HostLookupState 状态
    //     3> 执行主机名(hostName)的查找
    //     4> 如果查找成功, 发射信号 hostFound(), 同时 QAbstractSocket 进入 ConnectingState 状态
    //     5> 然后尝试连接到查找到的一个或者多个地址
    //     6> 如果建立了连接, QAbstractSocket 进入 ConnectingState 状态并发射信号 connected()

    // 2. 断开连接
    void QAbstractSocket::disconnectFromHost();
    // 断开过程:
    //     1> 尝试关闭 Socket
    //     2> 如果有待写入数据正在写入, QAbstractSocket 进入 ClosingState 状态并等待, 直到所有数据写入完毕
    //     3> 最后, QAbstractSocket 进入 UnconnectedState状态, 同时发射信号 disconnected()
    ```
    ![](./src/TCP_STREAM.png)

***UDP 通信***
- **UDP(User Datagram Protocol, 用户数据报协议)** 是轻量的、不可靠的、面向数据报(datagram)、无连接的协议, 它可以用于对可靠性要求不高的场合
- 两个程序之间进行 UDP 通信无需预先建立持久的 socket 连接, UDP 每次发送数据报都需要指定目标地址和端口
