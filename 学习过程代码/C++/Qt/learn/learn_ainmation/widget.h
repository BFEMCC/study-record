#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPropertyAnimation>
#include <QPaintEvent>
#include <QVariant>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

private:
    QPropertyAnimation* animation{nullptr};
    QRect star = QRect(0, 0, 100, 100);
    QRect end = QRect(500, 500, 100, 100);
    QRect tempstar = star;

protected:
    virtual void paintEvent(QPaintEvent *event);





public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
