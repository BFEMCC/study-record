#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimerEvent>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //重写QTimer定时器
    virtual void timerEvent(QTimerEvent *event) override;





private:
    Ui::Widget *ui;

    int id1;//定时器1的id值
    int id2;//...
};
#endif // WIDGET_H
