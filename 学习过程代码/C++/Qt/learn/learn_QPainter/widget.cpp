#include "widget.h"
#include "ui_widget.h"





Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);//实例化画家对象，这里的this是绘图设备（当前窗口）

    painter.drawLine(0,0,100,100);//画线

    painter.drawEllipse(100,100,50,50);//画椭圆（圆）


    QPen pen = painter.pen();//获取画笔
    pen.setColor(QColor(Qt::red));//设置画笔颜色
    pen.setWidth(3);//设置画笔宽度
    painter.setPen(pen);//设置画笔

    QBrush brush(Qt::cyan);//获取画刷
    painter.setBrush(brush);//设置画刷

    painter.drawRect(100,200,120,100);//画矩形

    painter.drawText(QRect(10,200,100,50),"hello 你好");
}

