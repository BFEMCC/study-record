#include "widget.h"
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QEnterEvent>

class mypushbutton : public QPushButton
{
    using QPushButton::QPushButton;
public:
    virtual void enterEvent(QEnterEvent* event) override//Qt6参数改成了QEventEvent，Qt5是QEvent
    {
        qDebug()<<"鼠标进入\n"
                 <<(QString("控件坐标x：%1，y：%2").arg(event->x()).arg(event->y())).toUtf8().data()
                 <<'\n'
                 <<(QString("屏幕坐标x：%1，y：%2").arg(event->globalX()).arg(event->globalY())).toUtf8().data();
    }

    virtual void leaveEvent(QEvent* event) override
    {
        qDebug()<<"鼠标离开";
    }

    //    virtual bool event(QEvent *e) override
    //    {
    //        return 0;
    //    }

    //    virtual bool hitButton(const QPoint &pos) const override
    //    {
    //        qDebug()<<pos.x()<<","<<pos.y();
    //        return 1;
    //    }
    //    virtual void keyPressEvent(QKeyEvent *e) override
    //    {

    //    }
    virtual void mouseMoveEvent(QMouseEvent *event) override
    {
        if(event->buttons() & Qt::LeftButton)
        {
            qDebug()<<"鼠标左键按下并且移动";
        }
    }
    //    virtual void paintEvent(QPaintEvent *) override
    //    {

    //    }
    virtual void mousePressEvent(QMouseEvent *event) override
    {
        if(event->button() == Qt::LeftButton)
        {
            qDebug()<<"鼠标左键按下\n"<<(QString("控件坐标x：%1，y：%2").arg(event->x()).arg(event->y())).toUtf8().data();
        }
        else if(event->button() == Qt::RightButton)
        {
            qDebug()<<"鼠标右键按下\n"<<(QString("控件坐标x：%1，y：%2").arg(event->x()).arg(event->y())).toUtf8().data();
        }
    }

    virtual void mouseReleaseEvent(QMouseEvent *event) override
    {
        if(event->button() == Qt::LeftButton)
        {
            qDebug()<<"鼠标左键释放\n"<<(QString("控件坐标x：%1，y：%2").arg(event->x()).arg(event->y())).toUtf8().data();
        }
        else if(event->button() == Qt::RightButton)
        {
            qDebug()<<"鼠标右键释放\n"<<(QString("控件坐标x：%1，y：%2").arg(event->x()).arg(event->y())).toUtf8().data();
        }
    }


};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    mypushbutton asdf(&w);
    //asdf.setMouseTracking(true);//设置鼠标追踪
    asdf.resize(100,100);
    asdf.move(200,200);


    w.show();
    return a.exec();
}
