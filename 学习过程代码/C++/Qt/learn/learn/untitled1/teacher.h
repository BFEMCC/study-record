#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>

class Teacher : public QObject
{
    Q_OBJECT
public:
    explicit Teacher(QObject *parent = nullptr);

signals://信号
    //自定义信号 写在signals下
    //返回值：void，只要声明，不要实现
    //可以有参数，可以重载

    void mysignals();
};

#endif // TEACHER_H
