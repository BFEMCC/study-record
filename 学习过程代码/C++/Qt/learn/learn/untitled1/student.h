#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = nullptr);

signals:


public slots://公共槽函数
    //槽函数写在这里，或者写在public下或全局
    //早期Qt必须写在public slots:下

    //返回值：void，需要声明，需要实现，可以重载

    void test_sut();
};

#endif // STUDENT_H
