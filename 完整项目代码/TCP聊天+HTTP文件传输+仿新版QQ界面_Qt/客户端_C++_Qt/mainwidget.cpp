#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "recvbox.h"
#include "sendbox.h"
#include "sendfilethread.h"
#include "ProgressWidget.h"
#include "globals.h"

#include <functional>

#define getFilePath QFileDialog::getOpenFileName
#define HomeLocation QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
#define PicturesLocation QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::MainWidget),
      login(new Login),
      tcpSocket(new QTcpSocket(this)),
      fileServer(new FileSrever(this))
{
    // 登录窗口点击连接,开始连接服务器
    connect(login, &Login::ServerMsg, this, &MainWidget::connectToServer);

    // 成功连接
    connect(tcpSocket, &QTcpSocket::connected, this, &MainWidget::SuccessConnectedServer);

    // 连接发生错误时弹出错误提示
    connect(tcpSocket, &QTcpSocket::errorOccurred, this, &MainWidget::cnnectError);

    login->exec(); // 阻塞等待连接窗口关闭
    InItUI();      // 加载主窗口UI

    // 接收消息
    connect(tcpSocket, &QTcpSocket::readyRead, this, &MainWidget::rcevServerMessage);

    // 发送文本消息
    connect(ui->sendBtn, &QPushButton::clicked, this, &MainWidget::sendMsgToSelectServer);

    // 关闭主窗口
    connect(ui->colseBtn, &QPushButton::clicked, this, &QWidget::close);

    // 最大化窗口
    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWidget::maximizeWindow);

    // 最小化窗口
    connect(ui->pushButton_9, &QPushButton::clicked, this, &QWidget::showMinimized);

    // 打开保存文件的文件夹
    connect(ui->openSavePath, &QPushButton::clicked, this, &MainWidget::openSavePathFolder);

    // 设置接收文件的保存目录
    connect(ui->setSavePath, &QPushButton::clicked, this, &MainWidget::setSavePath);

    // 向服务端发送文件(文件下载连接)
    connect(ui->pushButton, &QPushButton::clicked, this, std::bind(&MainWidget::sendFileToServer, this, fileType::all));

    // 向客户端发送图片(文件下载连接)
    connect(ui->pushButton_2, &QPushButton::clicked, this, std::bind(&MainWidget::sendFileToServer, this, fileType::img));

    // 文件服务器有新的连接
    connect(this->fileServer, &FileSrever::newDescriptor, this, &MainWidget::fileServerNewConnect);
}

MainWidget::~MainWidget()
{
    delete ui;
}

// 主窗口的界面初始化
void MainWidget::InItUI()
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/ico/client.ico"));   // 设置程序图标
    this->setWindowTitle("TCP客户端");                // 设置程序标题
    this->setWindowFlags(Qt::FramelessWindowHint);    // 隐藏标题栏
    this->setAttribute(Qt::WA_TranslucentBackground); // 设置窗口透明
    this->setMouseTracking(true);                     // 开启鼠标追踪
    for (auto &i : findChildren<QWidget *>())
        i->setMouseTracking(true);                            // 所有子控件也开启鼠标追踪
    ui->selfPhoto->setScaledContents(true);                   // 头像图片适应label大小
    ui->selfPhoto->setPixmap(QPixmap(":/IMAGE/default.png")); // 加载头像图片
    ui->sendEdit->setFocus();                                 // 设置发送文本框为焦点
    ui->chat->setChecked(true);                               // 设置聊天功能的单选框为选中状态

    // 设置水平分割布局属性
    ui->HorizontalSplitter->setChildrenCollapsible(false); // 设置不允许把分割出的子窗口拖小到0
    QList<int> HorizontalScale{305, 1020};
    ui->HorizontalSplitter->setSizes(HorizontalScale);
    ui->HorizontalSplitter->setHandleWidth(2); // 分割线的宽度
    // 设置垂直分割布局属性
    ui->VerticalSplitter->setChildrenCollapsible(false);
    ui->VerticalSplitter->setSizes(QList<int>{570, 260});
    ui->VerticalSplitter->setHandleWidth(2);
    // 初始化scroll Widget垂直布局
    this->scrollWidget = new QWidget(ui->scrollArea);              // 创建内容QWidget
    this->scrollLayout = new QVBoxLayout(this->scrollWidget);      // 创建一个垂直布局管理器
    this->scrollLayout->setSpacing(25);                            // 设置垂直布局里控件间的距离为25像素
    this->scrollWidget->setLayout(this->scrollLayout);             // 将垂直布局设置给内容QWidget
    ui->scrollArea->setWidget(this->scrollWidget);                 // 设置内容QWidget为QScrollArea的内部控件
    this->verticalScrollBar = ui->scrollArea->verticalScrollBar(); // 获取QScrollArea的垂直滚动条

    // 设置主界面样式表
    QFile f(":/mainwidgetStyle.qss");
    if (f.open(QFile::ReadOnly))
    {
        this->setStyleSheet(QString(f.readAll()));
        f.close();
    }

    ui->label_2->setText(tcpSocket->peerAddress().toString() + ":" + QString::number(tcpSocket->peerPort()));
    ui->label_3->setScaledContents(true);
    ui->label_3->setPixmap(QPixmap(":/IMAGE/eromanga.png"));
    ui->label_4->setText(ui->label_2->text());
    ui->widget_3->setStyleSheet("#widget_3 {background-color: rgb(0,153,255);}");
}

// 向服务器发送文本消息
void MainWidget::sendMsgToSelectServer()
{
    QByteArray message = ui->sendEdit->toPlainText().toUtf8(); // 获取文本消息转为二进制
    if (!message.isEmpty())
    {
        // 发送消息,更新消息记录,清空原有消息文本
        tcpSocket->write(message);
        ui->sendEdit->clear();

        // 创建一个消息气泡框,添加到滚动区域
        SendBox *sendbox = new SendBox(ui->scrollArea);
        scrollLayout->addWidget(sendbox);
        sendbox->setText(message);
        verticalScrollBar->setValue(verticalScrollBar->maximum()); // 滚动区域滚到最底下
    }
}

// 连接服务器,阻塞等待(3.5秒)
void MainWidget::connectToServer(QPair<QString, quint16> addrAndPort)
{
    tcpSocket->connectToHost(addrAndPort.first, addrAndPort.second);
    tcpSocket->waitForConnected(3500);
}

// 连接出错，打印错误信息
void MainWidget::cnnectError(QAbstractSocket::SocketError errormsg)
{
    switch (errormsg)
    {
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(nullptr, "被拒绝连接或超时", "连接被服务器拒绝或超时！");
        break;
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::warning(nullptr, "连接断开", "服务器断开连接！");
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(nullptr, "地址或端口错误", "找不到指定地址和端口的主机！");
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::critical(nullptr, "连接超时", "连接超时！");
        break;
    default:
        QMessageBox::critical(nullptr, "其他错误", "错误信息：" + tcpSocket->errorString());
        break;
    }
}

// 成功连接服务器,关闭登录窗口,文件服务器开始监听
void MainWidget::SuccessConnectedServer()
{
    this->login->close();
    this->login->deleteLater();
    this->fileServer->listen(); // 全部地址,随机端口
}

// 最大化窗口
void MainWidget::maximizeWindow()
{
    if (!isMaximized())
    {
        style = styleSheet();
        layout()->setContentsMargins(0, 0, 0, 0); // 重设边距
        setStyleSheet(styleSheet() + R"(
                                #frame {
                                    border-top-left-radius:0px;
                                    border-bottom-left-radius:0px;
                                }
                                #frame_5 {
                                    border-top-right-radius:0px;
                                }
                                #colseBtn {
                                        border-radius: 0px;
                                }
                            )");
        showMaximized();
        ui->pushButton_8->setStyleSheet("icon: url(:/IMAGE/resize_original_size.png);");
        update();
    }
    else
    {
        int margin = boundary_width - 5;
        layout()->setContentsMargins(margin, margin, margin, margin);
        showNormal();
        setStyleSheet(style);
        ui->pushButton_8->setStyleSheet("icon: url(:/svg/maxsize.svg);");
        update();
    }
}

// 打开保存文件的文件夹
void MainWidget::openSavePathFolder()
{
    QDesktopServices::openUrl(QUrl(saveDowPath));
}

// 设置接收文件的保存目录
void MainWidget::setSavePath()
{
    // 获取文件路径,默认打开路径为资源管理器主页
    QString temp = QFileDialog::getExistingDirectory(this, "选择保存文件位置", QDir::homePath());
    if (temp.isEmpty()) // 取消了文件夹选择
        return;
    this->saveDowPath = temp;
}

// 向服务端发送文件(文件下载连接)
void MainWidget::sendFileToServer(fileType type)
{
    QString filePath;
    // 获取待发送文件的路径
    switch (type)
    {
    case fileType::all:
        filePath = getFilePath(this, "选择发送文件", HomeLocation);
        break;
    case fileType::img:
        filePath = getFilePath(this, "选择发送图片", PicturesLocation, "图片(*.png *.jpg *.jpeg *.bmp *.gif *.webp)");
        break;
    }

    if (filePath.isEmpty())
        return;                                 // 取消发送
    valid_download_link.insert("/" + filePath); // 存储文件地址

    // 生成http下载链接
    QString downloadPath = (MATCH_KEY + "http://" + "clientIP" + ":" +
                            QString::number(this->fileServer->serverPort()) + "/" + filePath);

    // 向服务器发送下载链接
    this->tcpSocket->write(downloadPath.toUtf8());

    // 聊天框中添加发送气泡,根据对应的文件类型,显示图标
    SendBox *sendbox = new SendBox(ui->scrollArea);     // 创建发送气泡框
    this->scrollLayout->addWidget(sendbox);             // 添加到滚动垂直布局中
    QString su = fileimg[QFileInfo(filePath).suffix()]; // 根据文件后缀名找到图标
    QSvgRenderer m_svgRender;
    if (!su.isEmpty())
        m_svgRender.load(su);
    else
        m_svgRender.load(QString(":/svg/file-unknown-fill.svg"));
    QPixmap pix(m_svgRender.defaultSize() * 5);
    pix.fill(Qt::transparent);
    QPainter painter(&pix);
    painter.setRenderHints(QPainter::Antialiasing);
    m_svgRender.render(&painter);
    sendbox->setImageMsg(pix);
    sendbox->setFilePath(filePath); // 因为是发送的文件,所以可以双击打开文件,设置文件路径

    // 滚动区域滚到最底下
    verticalScrollBar->setValue(verticalScrollBar->maximum());
}

// 文件服务器有新的连接,启动子线程发送文件
void MainWidget::fileServerNewConnect(qintptr socket)
{
    sendFileThread *send_fileTherad = new sendFileThread(socket, this);                                     // 创建文件发送线程
    ProgressWidget *sendFileProgress = new ProgressWidget(this);                                            // 创建发送进度窗口
    connect(send_fileTherad, &sendFileThread::filePath, sendFileProgress, &ProgressWidget::setFilePath);    // 设置进度窗口文件路径
    connect(send_fileTherad, &sendFileThread::Progress, sendFileProgress, &ProgressWidget::updateProgress); // 发送进度更新
    connect(send_fileTherad, &sendFileThread::finish, this, &MainWidget::sendFileFinish);                   // 文件发送完毕
    connect(send_fileTherad, &sendFileThread::finish, sendFileProgress, &ProgressWidget::close);            // 文件发送完毕,进度窗口关闭
    sendFileProgress->show();                                                                               // 显示进度窗口
    send_fileTherad->start();                                                                               // 启动子线程
}

// 文件发送完毕
void MainWidget::sendFileFinish()
{
    sendFileThread *fileSendThread = qobject_cast<sendFileThread *>(sender());
    fileSendThread->exit();
    fileSendThread->deleteLater();
}

// 接收到服务器发来的消息
void MainWidget::rcevServerMessage()
{
    QString data(this->tcpSocket->readAll());       // 读取消息
    RecvBox *recvbox = new RecvBox(ui->scrollArea); // 创建接收消息气泡框
    this->scrollLayout->addWidget(recvbox);         // 添加到滚动垂直布局中

    // 服务器发来文件
    if (data.contains(MATCH_KEY))
    {
        QFileInfo fileInfo = QFileInfo(data);

        QString url = data.mid(data.indexOf(MATCH_KEY) + MATCH_KEY.length());

        QString su = fileimg[fileInfo.suffix()]; // 根据文件后缀名找到图标
        QSvgRenderer m_svgRender;
        if (!su.isEmpty())
            m_svgRender.load(su);
        else
            m_svgRender.load(QString(":/svg/file-unknown-fill.svg"));
        QPixmap pix(m_svgRender.defaultSize() * 5);
        pix.fill(Qt::transparent);
        QPainter painter(&pix);
        painter.setRenderHints(QPainter::Antialiasing);
        m_svgRender.render(&painter);
        recvbox->setImageMsg(pix);
        recvbox->setFilePath(this->saveDowPath + "/" + fileInfo.fileName()); // 文件,可以双击打开文件,设置文件路径
        recvbox->setUrl(url);
    }
    // 是普通的文本消息
    else
    {
        recvbox->setText(data);
    }
    verticalScrollBar->setValue(verticalScrollBar->maximum()); // 将滚动条值设置为最大值，以确保内容滚动到最底部
}

/*------------窗口绘制,移动操作相关------------*/
void MainWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿
    painter.setPen(Qt::transparent);               // rgba(0,0,0,0)
    if (!isMaximized())
    {
        painter.setBrush(QBrush(QColor(234, 233, 234, 1))); // 背景色
        painter.drawPath(painterPath);                      // 绘制
    }
    else
    {
        painter.setBrush(QBrush(QColor(234, 233, 234))); // 背景色
        painter.drawPath(painterPath);                   // 绘制
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);

    if (!mainRect.contains(event->pos()) && !isdirectionLock && !ismove && !isMaximized()) // 光标在边框区域,并且改变的方向非锁定状态,并且不是在移动窗口,并且窗口不是最大化
    {
        isresize = true;
        // 左上角
        if (event->pos().x() < boundary_width && event->pos().y() < boundary_width)
        {
            setCursor(Qt::SizeFDiagCursor); // 设置光标样式
            resize_direction = direction::left_top;
        }
        // 左下角
        else if (event->pos().x() < boundary_width && event->pos().y() > boundary_width + mainRect.height())
        {
            setCursor(Qt::SizeBDiagCursor);
            resize_direction = direction::left_bottom;
        }
        // 右上角
        else if (event->pos().x() > boundary_width + mainRect.width() && event->pos().y() < boundary_width)
        {
            setCursor(Qt::SizeBDiagCursor);
            resize_direction = direction::right_top;
        }
        // 右下角
        else if (event->pos().x() > boundary_width + mainRect.width() && event->pos().y() > boundary_width + mainRect.height())
        {
            setCursor(Qt::SizeFDiagCursor);
            resize_direction = direction::right_bottom;
        }
        // 左边框
        else if (event->pos().x() < boundary_width)
        {
            setCursor(Qt::SizeHorCursor);
            resize_direction = direction::left;
        }
        // 右边框
        else if (event->pos().x() > boundary_width + mainRect.width())
        {
            setCursor(Qt::SizeHorCursor);
            resize_direction = direction::right;
        }
        // 上边框
        else if (event->pos().y() < boundary_width)
        {
            setCursor(Qt::SizeVerCursor);
            resize_direction = direction::top;
        }
        // 下边框
        else if (event->pos().y() > boundary_width + mainRect.height())
        {
            setCursor(Qt::SizeVerCursor);
            resize_direction = direction::bottom;
        }
    }

    if (mainRect.contains(event->pos()) && event->buttons() == Qt::NoButton) // 鼠标在主区域内,并且没有任何按钮按下
    {
        setCursor(Qt::ArrowCursor); // 恢复鼠标样式
        isresize = false;
        isdirectionLock = false;
        ismove = false;
    }

    if (isresize && event->buttons() & Qt::LeftButton) // 在调整大小
    {
        isdirectionLock = true; // 鼠标点击后变成锁定状态
        ismove = false;
        switch (resize_direction)
        {
        case direction::left: // 左边框
        {
            int dx = m_click.x() - event->globalPosition().x();                                  // 改变量
            int new_x = w_left_top.x() - dx;                                                     // 新的x坐标
            setGeometry(new_x, w_left_top.y(), dx + w_right_top.x() - w_left_top.x(), height()); // 设置新的位置和大小
            update();
            break;
        }
        case direction::right: // 右边框
        {
            int dx = event->globalPosition().x() - m_click.x();
            resize(dx + w_right_top.x() - w_left_top.x(), height()); // 向右改变大小不需要移动窗口
            update();
            break;
        }
        case direction::top: // 上边框
        {
            int dy = m_click.y() - event->globalPosition().y();
            int new_y = w_left_top.y() - dy;
            setGeometry(w_left_top.x(), new_y, width(), dy + w_left_bottom.y() - w_left_top.y());
            update();
            break;
        }
        case direction::bottom: // 下边框
        {
            int dy = event->globalPosition().y() - m_click.y();
            resize(width(), dy + w_left_bottom.y() - w_left_top.y());
            update();
            break;
        }
        case direction::left_top: // 左上角
        {
            int dx = m_click.x() - event->globalPosition().x(); // 改变量
            int new_x = w_left_top.x() - dx;                    // 新的x坐标
            int dy = m_click.y() - event->globalPosition().y();
            int new_y = w_left_top.y() - dy;
            setGeometry(new_x, new_y, dx + w_right_top.x() - w_left_top.x(), dy + w_left_bottom.y() - w_left_top.y());
            update();
            break;
        }
        case direction::left_bottom: // 左下角
        {
            int dx = m_click.x() - event->globalPosition().x(); // 改变量
            int new_x = w_left_top.x() - dx;                    // 新的x坐标
            int dy = event->globalPosition().y() - m_click.y();
            setGeometry(new_x, w_left_top.y(), dx + w_right_top.x() - w_left_top.x(), dy + w_left_bottom.y() - w_left_top.y());
            update();
            break;
        }
        case direction::right_top: // 右上角
        {
            int dx = event->globalPosition().x() - m_click.x();
            int dy = m_click.y() - event->globalPosition().y();
            int new_y = w_left_top.y() - dy;
            setGeometry(w_left_top.x(), new_y, dx + w_right_top.x() - w_left_top.x(), dy + w_left_bottom.y() - w_left_top.y());
            update();
            break;
        }
        case direction::right_bottom: // 右下角
        {
            int dx = event->globalPosition().x() - m_click.x();
            int dy = event->globalPosition().y() - m_click.y();
            resize(dx + w_right_top.x() - w_left_top.x(), dy + w_left_bottom.y() - w_left_top.y());
            update();
            break;
        }
        default: // none
            break;
        }
    }

    if (!isresize && event->buttons() == Qt::LeftButton && (event->pos().y() <= canmove_y || event->pos().x() <= canmove_x)) // 移动窗口
    {
        isdirectionLock = false; // 改变方向变成非锁定状态
        resize_direction = direction::none;
        ismove = true;
        setCursor(Qt::SizeAllCursor); // 设置光标
        if (isMaximized())
        {
            ui->pushButton_8->click();
            return;
        }
        else
        {
            QPointF newPos = event->globalPosition() - m_click + w_left_top;
            move(newPos.toPoint()); // 移动窗口到新位置
        }
    }
}

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    m_click = event->globalPosition(); // 记录鼠标点击坐标
    w_left_top = frameGeometry().topLeft();
    w_left_bottom = frameGeometry().bottomLeft();
    w_right_top = frameGeometry().topRight();
    QWidget::mousePressEvent(event);
}

void MainWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    painterPath.clear();
    if (!isMaximized())
        painterPath.addRoundedRect(rect(), 15, 15); // 添加绘制区域，并设置圆角
    else
        painterPath.addRoundedRect(rect(), 0, 0);
    boundary_width = 5 + layout()->contentsMargins().left(); // 获取布局边距，设置边框宽度
    mainRect.setRect(boundary_width, boundary_width, width() - 2 * boundary_width, height() - 2 * boundary_width);
    canmove_y = ui->frame_10->pos().y() + ui->frame_10->height();
    canmove_x = ui->frame->pos().x() + ui->frame->width();
}

void MainWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    QWidget::mouseDoubleClickEvent(event);
    if (event->button() == Qt::LeftButton && (event->pos().y() <= canmove_y || event->pos().x() <= canmove_x))
        ui->pushButton_8->click();
}
