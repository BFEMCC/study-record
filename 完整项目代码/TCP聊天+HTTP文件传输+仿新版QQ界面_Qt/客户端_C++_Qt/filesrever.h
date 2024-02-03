#ifndef FILESREVER_H
#define FILESREVER_H

#include <QObject>
#include <QTcpServer>

class FileSrever : public QTcpServer
{
    Q_OBJECT
public:
    explicit FileSrever(QObject *parent = nullptr);

protected:
    // 有客户端发起连接后这个函数自动被调用
    // 解决nextPendingConnection函数返回的QTcpSocket对象无法在子线程中使用问题
    virtual void incomingConnection(qintptr socketDescriptor) override;
signals:
    void newDescriptor(qintptr);
};

#endif // FILESREVER_H
