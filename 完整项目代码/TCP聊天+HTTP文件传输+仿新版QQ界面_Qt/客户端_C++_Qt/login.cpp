#include "login.h"
#include "ui_login.h"
#include "globals.h"

#include <QDebug>
#define qdebug qDebug()

Login::Login(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::Widget),
      exitbtn(new QPushButton(this))
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/ico/client.ico")); // 设置程序图标
    setWindowTitle("TCP客户端");              // 设置程序标题
    ui->lineEdit_1->setFontStyle(QFont("微软雅黑", 10), Qt::white);
    ui->lineEdit_2->setFontStyle(QFont("微软雅黑", 10), Qt::white);
    ui->pushButton->setBackgroundColor(QColor(9, 21, 38));
    ui->pushButton->setFontColor(QColor(69, 198, 214), QColor(255, 255, 255));
    ui->pushButton->setFillColor(QColor(29, 84, 125));
    ui->pushButton->setBorderColor(QColor(28, 73, 107), 1);
    ui->pushButton->setStyleSheet(R"(QPushButton:hover{border:0px solid rgb(0,0,0);})");
    ui->pushButton->setFont(QFont("微软雅黑", 13));
    ui->pushButton->setBorderRadius(10);

    // 正则表达式限制IP地址合法
    ui->lineEdit_1->setValidator(new QRegularExpressionValidator(
        QRegularExpression(
            "^(1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|[1-9])\\."
            "(1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|\\d)\\."
            "(1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|\\d)\\."
            "(1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|\\d)$"),
        this));

    // 限制端口号输入合法及限制范围
    ui->lineEdit_2->setValidator(new QIntValidator(0, 65535, this));

    setWindowFlags(Qt::FramelessWindowHint);    // 隐藏标题栏
    setAttribute(Qt::WA_TranslucentBackground); // 设置窗口透明
    setFixedSize(520, 360);                     // 固定大小
    BackgroundImg.load(":/IMAGE/login.png");    // 加载背景图片
    GaussiamBlur(5, 50, BackgroundImg);         // 背景图片高斯模糊
    painterPath.addRoundedRect(rect(), 10, 10); // 添加圆角矩形绘制路径

    // 关闭按钮
    QIcon exitImg;
    exitImg.addFile(":/IMAGE/exit_white.png"); // 加载关闭按钮图片
    exitbtn->resize(40, 25);
    exitbtn->setIcon(exitImg);
    exitbtn->move(width() - exitbtn->width(), 0);
    exitbtn->setStyleSheet(R"(QPushButton {
                                color: white;
                                border: none;
                                border-top-right-radius:10px;
                                background-color: rgba(0, 0, 0, 0);
                               }
                            QPushButton:hover {
                                background-color: rgba(196, 43, 28, 255);
                            })");

    connect(exitbtn, &QPushButton::clicked, this, []
            { exit(1); });

    connect(ui->pushButton, &QPushButton::clicked, this, &Login::onConnect);
}

Login::~Login()
{
    delete ui;
}

void Login::onConnect()
{
    emit ServerMsg(QPair<QString, quint16>(ui->lineEdit_1->text(), ui->lineEdit_2->text().toUShort()));
}

void Login::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);     // 抗锯齿
    painter.setClipPath(painterPath);                  // 设置绘制区域的剪切路径
    painter.drawImage(rect(), BackgroundImg, QRect()); // 绘制背景图片
}

void Login::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);

    if (event->buttons() == Qt::LeftButton) // 左键按下
    {
        QPointF newPos = event->globalPosition() - m_click + w_left_top;
        move(newPos.toPoint()); // 移动窗口到新位置
    }
}

void Login::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

    // 记录坐标参数
    m_click = event->globalPosition();
    w_left_top = frameGeometry().topLeft();
    // 清除输入框焦点
    ui->lineEdit_1->clearFocus();
    ui->lineEdit_2->clearFocus();
}

QRegularExpression Login::regexIP{"^(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})$"};
