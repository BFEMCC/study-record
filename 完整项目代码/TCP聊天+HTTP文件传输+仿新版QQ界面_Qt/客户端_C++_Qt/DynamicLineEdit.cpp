#include "DynamicLineEdit.h"

DynamicLineEdit::DynamicLineEdit(QWidget *parent)
    : QLineEdit{parent},
      timer{new QTimer(this)}
{
    path.addRoundedRect(rect(), border_radius, border_radius); // 添加圆角矩形区域
    setFocusPolicy(Qt::ClickFocus);                            // 设置焦点策略
    timer->setInterval(msec);
    connect(timer, &QTimer::timeout, this, Slot_in_focus);
    setStyleSheet(R"(DynamicLineEdit{
                        background-color:rgba(255,255,255,0);
                        border-radius:10px;
                        padding-left:10px;
                    })");
}

void DynamicLineEdit::setLineColor(const QColor &focusOutcolor, const QColor &focusIncolor)
{
    line_color_1 = focusOutcolor;
    line_color_2 = focusIncolor;
}

void DynamicLineEdit::setFontColor(const QColor &fontColor)
{
    QPalette fontcolor{palette()};
    fontcolor.setColor(QPalette::Text, fontColor);
    setPalette(fontcolor);
}

void DynamicLineEdit::setFontStyle(const QFont &font, const QColor &fontcolor)
{
    setFont(font);
    setFontColor(fontcolor);
}

void DynamicLineEdit::setLineSpeed(const int speed)
{
    msec = speed;
}

void DynamicLineEdit::setLineHeight(const int lineHeight)
{
    line_height = lineHeight;
}

void DynamicLineEdit::setText(const QString &text)
{
    QLineEdit::setText(text);
    prompt = text;
}

void DynamicLineEdit::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);

    QPainter painter = QPainter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿

    painter.setPen(QPen(line_color_1, line_height, Qt::SolidLine));                                 // 设置画笔颜色和线条样式
    painter.drawLine(QPointF(0, height() - line_height), QPointF(width(), height() - line_height)); // 在底部画未选中时的线条

    painter.setPen(QPen(line_color_2, line_height, Qt::SolidLine));
    painter.drawLine(QPointF(-2, height() - line_height), QPointF(line_width_anim, height() - line_height)); // 在底部画选中时的线条
}

void DynamicLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    timer->disconnect();
    connect(timer, &QTimer::timeout, this, Slot_in_focus);
    timer->start();
    if (text() == prompt)
    {
        // setAlignment(Qt::AlignCenter);//居中输入
        clear();
    }
}

void DynamicLineEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    timer->disconnect();
    connect(timer, &QTimer::timeout, this, Slot_out_focus);
    timer->start();
    if (text().isEmpty())
    {
        //        setAlignment(Qt::AlignLeft);//居左
        setText(prompt);
    }
}
