#include "widget.h"
#include "ui_widget.h"

void Widget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);


    QPainter painter(this);
    painter.drawRect(star);
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,animation(new QPropertyAnimation(this, "geometry"))
{
    ui->setupUi(this);

    animation->setTargetObject(this);    //设置作用对象
    animation->setDuration(1000);        //设置持续时间(过度时间)(毫秒)

    animation->setStartValue(end);      //设置起始值
    animation->setEndValue(star);       //设置结束值

    animation->setEasingCurve(QEasingCurve::OutBounce);//设置动画效果(缓和曲线)(值的改变快慢或过程遵循一些特定的函数),提供了一系列枚举值,也可自定义,类型：QEasingCurve


    //动画开始后会将star按设置的时间逐渐变换到end

    connect(ui->pushButton,&QPushButton::clicked,this,[=]{

        if(star == QRect(500, 500, 100, 100))
        {
            //animation->setDirection(QVariantAnimation::Backward);//到达终点，设置成回退动画
            animation->setStartValue(end);
            animation->setEndValue(tempstar); //到达中点后，初始值会被修改成结束之值，用一个副本值存储即可
        }
        else
        {
            animation->setStartValue(star);
            animation->setEndValue(end);
            //animation->setDirection(QVariantAnimation::Forward);//不是终点，设置成正向动画。//这种方式的缓和曲线并会不也倒过来，所以直接将初始位置和结束位置调换即可
        }
        animation->start();
    });//点击按钮，动画开始

    connect(animation,&QPropertyAnimation::valueChanged,this,[=](const QVariant& value){
        star = value.toRect();
        update();
    });//动画开始，值改变，更新绘制事件


}

Widget::~Widget()
{
    delete ui;
}

