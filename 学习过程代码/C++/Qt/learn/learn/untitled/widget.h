#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>  //Qwidget窗口类的头文件

class Widget : public QWidget   //继承Qwidget
{
    Q_OBJECT    //一个宏，允许类中使用信号和槽的机制

public:
    Widget(QWidget *parent = nullptr);//构造函数，参数为基类指针，默认值为空
    ~Widget();//析构函数
};
#endif // WIDGET_H
