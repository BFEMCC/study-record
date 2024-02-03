#ifndef SENDFILETHREAD_H
#define SENDFILETHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QFileInfo>
#include <QIODevice>
#include <QFile>
#include <QString>
#include <QUrl>
#include <QFileInfo>
#include <QMultiMap>

class sendFileThread : public QThread
{
    Q_OBJECT
public:
    explicit sendFileThread(qintptr Socket, QObject *parent = nullptr);

signals:
    void Progress(int);     // 告诉主线程进度窗口发送进度
    void finish();          // 告诉主线程当前的客户端发送完毕
    void fileOpenError();   // 告诉文件打开错误
    void filePath(QString); // 告诉进度窗口文件路径
protected:
    void run() override;

private:
    QTcpSocket *client;
    qintptr sockt;
};

#endif // SENDFILETHREAD_H
