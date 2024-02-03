#include "widget.h"
#include <QPushButton>
#include <qvector.h>
//命名规范
//类名 首字母大写，单词和单词间字母大写
//函数名 变量名称：首字母小写，单词和之间首字母大写

//快捷键
// 注释   ctrl+/
// 运行   ctrl+r
// 编译   ctrl+b
// 字体缩放 ctrl+鼠标滚轮
// 查找 ctrl+f
// 整行移动 ctrl+shift+上方向键/下方向键
// 帮助文档 F1
// 自动对齐 ctrl+i
// 同名.h和.cpp切换  F4

//独立帮助文档
//安装目录，Qt助手



Widget::Widget(QWidget *parent)
    : QWidget(parent)   //初始化列表，使用父类指针初始化父类的
{
    QPushButton *btn = new QPushButton;
//    btn->show();//以单独窗口弹出按钮
    btn->setParent(this);//指定父窗口
    btn->setText("first btn");//设置按钮文本

    QPushButton *btn2 = new QPushButton("退出",this);
    btn2->move(100,100);//将btn2移动到100，100 坐标的位置

 //信号和槽
  //btn2的几种写法：
    //this->connect(btn2,&btn2->clicked,this,[](){exit(0);});
    this->connect(btn2,&QPushButton::clicked,this,&Widget::close);
    //this->connect(btn2,&QPushButton::clicked,this,&this->close);


    //this->resize(640,480);//设置窗口大小
    this->setFixedSize(640,480);//固定窗口大小

    this->setWindowTitle("这是标题");//设置窗口标题

}

Widget::~Widget()
{
}

