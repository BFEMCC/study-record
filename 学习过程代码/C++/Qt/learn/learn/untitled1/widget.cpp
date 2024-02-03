#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    //创建一个老师对象
    this->tea=new Teacher(this);


    //创建一个学生对象
    this->stu=new Student(this);

    //连接
    this->connect(this->tea,&Teacher::mysignals,this->stu,&Student::test_sut);

    //创建按钮
    QPushButton *btn = new QPushButton("调用",this);
    this->connect(btn,&btn->clicked,this->tea,&Teacher::mysignals);

    [this](){auto a=tea;};
}
void Widget::发送()
{
    //调用这个函数时，触发学生的槽函数
    this->tea->mysignals();
}
Widget::~Widget()
{
    delete ui;
}

