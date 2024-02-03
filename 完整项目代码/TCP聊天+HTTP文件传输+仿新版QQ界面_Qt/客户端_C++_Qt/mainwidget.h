#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QPixmap>
#include <QSplitter>
#include <QPainter>
#include <QMouseEvent>
#include <QRect>
#include <QResizeEvent>
#include <QPoint>
#include <QPointF>
#include <QMargins>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QByteArray>
#include <QCoreApplication>
#include <QFileInfo>
#include <QFile>
#include <QFileDialog>
#include <QRegion>
#include <QMap>
#include <QSvgRenderer>
#include <QDesktopServices>
#include <QThread>
#include <QDir>
#include <QStandardPaths>
#include <QStringList>
#include <QtTypes>
#include <QString>
#include <QStringList>

#include "login.h"
#include "ProgressWidget.h"
#include "filesrever.h"

namespace Ui
{
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    enum class direction : int // 声明类内枚举 方向:无,上,下,左,右,左上,左下,右上,右下
    {
        none,
        top,
        bottom,
        left,
        right,
        left_top,
        left_bottom,
        right_top,
        right_bottom
    };
    enum class fileType : int
    {
        all,
        img
    };
    int boundary_width;                           // 边界区域的宽度
    int canmove_y;                                // 可移动窗口的y坐标最大值
    int canmove_x;                                // 可移动窗口的x坐标最大值
    QRect mainRect;                               // 主区域
    QPointF m_click;                              // 鼠标点击坐标
    QPointF w_left_top;                           // 窗口左上角坐标
    QPointF w_left_bottom;                        // 窗口左下角坐标
    QPointF w_right_top;                          // 窗口右上角坐标
    bool isresize = false;                        // 是否在调整大小
    bool isdirectionLock = false;                 // 改变大小的方向是否锁定
    bool ismove = false;                          // 是否在移动窗口
    QPainterPath painterPath;                     // 绘制路径
    direction resize_direction = direction::none; // 默认调整方向

    Ui::MainWidget *ui;
    Login *login;                  // 登录界面
    QWidget *scrollWidget;         // scrollArea的内容QWidget
    QVBoxLayout *scrollLayout;     // 内容QWidget的垂直布局
    QScrollBar *verticalScrollBar; // scrollArea的滚动条
    QString style;

    QTcpSocket *tcpSocket;
    FileSrever *fileServer;

    // 默认的文件保存路径,电脑的下载文件夹
    QString saveDowPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);

    // 常见文件后缀对应图标
    const QMap<QString, QString> fileimg{
        {"jpg", ":/svg/file-jpg.svg"},
        {"md", ":/svg/file-md.svg"},
        {"pdf", ":/svg/file-pdf.svg"},
        {"png", ":/svg/file-png.svg"},
        {"txt", ":/svg/file-txt.svg"},
        {"cpp", ":/svg/file-type-cpp2.svg"},
        {"hpp", ":/svg/file-type-cpp2.svg"},
        {"c", ":/svg/file-type-c3.svg"},
        {"h", ":/svg/file-type-c3.svg"},
        {"xlsx", ":/svg/file-type-excel.svg"},
        {"xlsm", ":/svg/file-type-excel.svg"},
        {"xlsb", ":/svg/file-type-excel.svg"},
        {"xltx", ":/svg/file-type-excel.svg"},
        {"xlt", ":/svg/file-type-excel.svg"},
        {"xls", ":/svg/file-type-excel.svg"},
        {"pptx", ":/svg/file-type-powerpoint.svg"},
        {"pptm", ":/svg/file-type-powerpoint.svg"},
        {"ppt", ":/svg/file-type-powerpoint.svg"},
        {"potx", ":/svg/file-type-powerpoint.svg"},
        {"pot", ":/svg/file-type-powerpoint.svg"},
        {"posm", ":/svg/file-type-powerpoint.svg"},
        {"ppam", ":/svg/file-type-powerpoint.svg"},
        {"ppa", ":/svg/file-type-powerpoint.svg"},
        {"docx", ":/svg/file-type-word.svg"},
        {"dotx", ":/svg/file-type-word.svg"},
        {"doc", ":/svg/file-type-word.svg"},
        {"dot", ":/svg/file-type-word.svg"},
        {"dotm", ":/svg/file-type-word.svg"},
        {"py", ":/svg/file-type-python.svg"},
        {"mp3", ":/svg/filetype-mp3.svg"},
        {"mp4", ":/svg/filetype-mp4.svg"},
        {"exe", ":/svg/filetype-exe.svg"},
        {"java", ":/svg/filetype-java.svg"},
        {"7z", ":/svg/7zipper.svg"},
        {"apk", ":/svg/apk-document.svg"},
        {"sql", ":/svg/filetype-sql.svg"},
        {"zip", ":/svg/zip.svg"},
        {"svg", ":/svg/filetype-svg.svg"},
        {"class", ":/svg/filetype-java.svg"},
        {"html", ":/svg/file-html.svg"},
        {"css", ":/svg/document-css-20-filled.svg"},
        {"webp", ":/svg/webp-format.svg"},
        {"js", ":/svg/document-javascript-20-filled.svg"},
        {"psd", ":/svg/filetype-psd.svg"},
        {"ui", ":/svg/qt.svg"},
        {"json", ":/svg/filetype-json.svg"},
        {"gif",":/svg/file-gif.svg"}};

    void InItUI(); // 初始化UI
private slots:
    void sendMsgToSelectServer();                              // 向服务器发送文本消息
    void connectToServer(QPair<QString, quint16> addrAndPort); // 连接服务器
    void cnnectError(QAbstractSocket::SocketError errormsg);   // 提示连接错误信息
    void rcevServerMessage();                                  // 接收到服务器消息
    void SuccessConnectedServer();                             // 成功连接到服务器
    void maximizeWindow();                                     // 将窗口最大化
    void openSavePathFolder();                                 // 打开保存文件的文件夹
    void setSavePath();                                        // 设置接收到的文件保存的路径
    void sendFileToServer(fileType type);                      // 向服务器发送文件(文件下载连接)
    void fileServerNewConnect(qintptr socket);                 // 文件服务器有新连接
    void sendFileFinish();                                     // 文件发送完毕

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
};
#endif // MAINWIDGET_H
