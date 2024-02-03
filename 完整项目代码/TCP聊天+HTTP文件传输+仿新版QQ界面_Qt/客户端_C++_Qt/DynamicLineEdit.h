#ifndef DynamicLineEdit_H
#define DynamicLineEdit_H

#include <QWidget>
#include <QLineEdit>
#include <QPainter>
#include <QPaintEvent>
#include <QFocusEvent>
#include <QFocusEvent>
#include <QTimer>
#include <QColor>
#include <QPainterPath>
#include <QPointF>
#include <QPalette>
#include <functional>

using std::function;

class DynamicLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    DynamicLineEdit(QWidget *parent = nullptr);

    void setLineColor(const QColor &focusOutcolor, const QColor &focusIncolor); // 设置线条颜色，参数：失去焦点颜色，获取焦点颜色

    void setFontColor(const QColor &fontColor); // 设置字体颜色

    void setFontStyle(const QFont &font, const QColor &fontcolor = Qt::white); // 设置字体及颜色

    void setLineSpeed(const int speed); // 设置线条填速度

    void setLineHeight(const int lineHeight); // 设置线条像素高度

    void setText(const QString &text); // 设置文本
private:
    int border_radius{10};     // 圆角半径
    int line_height{2};        // 线的高度(像素)
    int line_width_anim{-1};   // 线条长度(坐标)
    int line_width_offset{10}; // 线条长度的增量

    int msec{10}; // 定时器间隔
    QTimer *timer;

    QColor line_color_1{66, 66, 66}; // 未获得焦点时的颜色
    QColor line_color_2{255, 0, 0};  // 获得焦点时的颜色

    QString prompt; // 默认文本

    QPainterPath path; // 绘制路径

    function<void(void)> Slot_in_focus{// 获得焦点的槽函数
                                       [&]()
                                       {
                                           line_width_anim += line_width_offset;
                                           if (line_width_anim > width())
                                               timer->stop();
                                           update();
                                       }};

    function<void(void)> Slot_out_focus{// 失去焦点的槽函数
                                        [&]()
                                        {
                                            line_width_anim -= line_width_offset;
                                            if (line_width_anim < 0)
                                                timer->stop();
                                            update();
                                        }};

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void focusInEvent(QFocusEvent *event) override;  // 获取焦点事件
    virtual void focusOutEvent(QFocusEvent *event) override; // 失去焦点事件
};

#endif // DynamicLineEdit_H
