#include "student.h"
#include<QDebug>
Student::Student(QObject *parent)
    : QObject{parent}
{

}

void Student::test_sut()
{
    qDebug()<<"学生的槽函数";
}
