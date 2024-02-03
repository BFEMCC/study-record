#include "AnimatedButton.h"

AnimatedButton::AnimatedButton(QWidget *parent)
    : QPushButton(parent),
      timer(new QTimer(this))
{
    timer->setInterval(fill_speed);
    resize(width(), height());
}

void AnimatedButton::setfillSpeed(const int speed)
{
    fill_speed = speed;
}

void AnimatedButton::setFillColor(const QColor &fillcolor)
{
    fill_color = fillcolor;
}

void AnimatedButton::setFontColor(const QColor &initial, const QColor &hover)
{
    font_initial_color = initial;
    font_hover_color = hover;
    font_paint_color = font_initial_color;
}

void AnimatedButton::setText(const QString &text)
{
    QPushButton::setText("");
    this->text = text;
}

void AnimatedButton::setBackgroundColor(const QColor &bk_color)
{
    setStyleSheet("QPushButton{background-color:" + bk_color.name() + ";}");
}

void AnimatedButton::setBorderRadius(const int border_radius)
{
    this->border_radius = border_radius;
    path.clear();
    path.addRoundedRect(rect(), border_radius, border_radius);
    setStyleSheet(QString("QPushButton{border-radius:%1px;}").arg(QString::number(border_radius)));
}

void AnimatedButton::setBorderColor(const QColor &border_color, const int border_thickness)
{
    setStyleSheet(QString("QPushButton{border:%1px solid %2;}").arg(QString::number(border_thickness), border_color.name()));
}

void AnimatedButton::setStyleSheet(const QString &stylesheet)
{
    QPushButton::setStyleSheet(styleSheet() + stylesheet);
}

void AnimatedButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setClipPath(path);

    painter.save();
    // 绘制填矩形
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(fill_color));

    if (is_hover)
        painter.drawRect(QRectF(0, 0, initial_width, height()));

    else // 从右到左绘画矩形
    {
        painter.translate(width(), height());
        painter.rotate(180);
        painter.drawRect(QRectF(0, 0, initial_width, height()));
    }

    painter.restore();
    // 绘制文字
    painter.setFont(font());
    painter.setPen(font_paint_color);
    painter.drawText(rect(), Qt::AlignCenter, text);
}

void AnimatedButton::resizeEvent(QResizeEvent *event)
{
    QPushButton::resizeEvent(event);
    max_width = qPow(qPow(width(), 2) + qPow(height(), 2), 0.5);
    path.clear();
    path.addRoundedRect(rect(), border_radius, border_radius);
}

void AnimatedButton::enterEvent(QEnterEvent *event)
{
    QPushButton::enterEvent(event);
    is_hover = true;
    font_paint_color = font_hover_color;
    timer->disconnect();
    connect(timer, &QTimer::timeout, this, WidthIncrease);
    timer->start();
}

void AnimatedButton::leaveEvent(QEvent *event)
{
    QPushButton::leaveEvent(event);
    is_hover = false;
    font_paint_color = font_initial_color;
    timer->disconnect();
    connect(timer, &QTimer::timeout, this, WidthDecrease);
    timer->start();
}
