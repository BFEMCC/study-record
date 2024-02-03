#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QPainterPath>
#include <QPixmap>
#include <QPointF>
#include <QIcon>
#include <QImage>
#include <QRegularExpression>
#include <functional>
#include <QRegularExpressionValidator>
#include <QIntValidator>
#include <QFile>
#include <QFileDialog>
#include <QPair>
#include <QDialog>

using std::function;
QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Widget *ui;
    QPushButton *exitbtn = nullptr; // 关闭按钮
    QPainterPath painterPath;       // 绘制路径
    QImage BackgroundImg;           // 背景图片
    QPointF m_click;                // 鼠标点击坐标
    QPointF w_left_top;             // 窗口左上角坐标

    static QRegularExpression regexIP;

signals:
    void ServerMsg(QPair<QString, quint16>);

private slots:
    void onConnect();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // LOGIN_H
