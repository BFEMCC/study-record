#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //启动定时器
    id1 = startTimer(1000);//参数1 间隔，单位：毫秒  返回值：定时器唯一id值

    id2 = startTimer(2000);


    //定时器类的使用
    QTimer* timer = new QTimer(this);//创建一个定时器对象
    timer->start(500);//启动定时器，每500毫秒发送一个信号

    connect(timer,&QTimer::timeout,ui->label_3,[=]{
        static int num3 = 1;
        ui->label_3->setText("每0.5秒+1："+QString::number(num3++));
    });

    //点击暂停按钮暂停
    connect(ui->pushButton,&QPushButton::clicked,timer,&QTimer::stop);
    //点击继续按钮继续
    connect(ui->pushButton_2,&QPushButton::clicked,this,[=]{timer->start(500);});
}

Widget::~Widget()
{
    delete ui;
}


//重写定时器
void Widget::timerEvent(QTimerEvent *event)
{
    static int num1 = 1;
    static int num2 = 1;

    if(event->timerId() == id1)
        ui->label->setText("每1秒+1："+QString::number(num1++));
    else if(event->timerId() == id2)
        ui->label_2->setText("每2秒+1："+QString::number(num2++));
}

