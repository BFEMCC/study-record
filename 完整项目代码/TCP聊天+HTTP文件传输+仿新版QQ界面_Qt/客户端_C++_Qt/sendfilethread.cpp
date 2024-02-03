#include "sendfilethread.h"
#include "globals.h"

sendFileThread::sendFileThread(qintptr Socket, QObject *parent)
    : QThread{parent}
{
    this->sockt = Socket;
}

void sendFileThread::run()
{
    this->client = new QTcpSocket();
    this->client->setSocketDescriptor(this->sockt);

    this->client->waitForReadyRead();

    QString data = QString(client->readAll());
    QStringList substringList = data.split(" "); // 对接收到的请求报文按空格进行分割

    // 正常使用情况下,文件服务器接收到的一定是正确的GET请求
    // 以防万一,做一下正确性判断
    if (substringList.length() >= 3 &&
        (substringList[0] == "GET") &&
        (valid_download_link.contains(QUrl::fromPercentEncoding(substringList[1].toUtf8()))) &&
        (substringList[2].contains("HTTP/1.1")))
    {
        // 对资源路径进行转码和切片,获取完整正确的路径
        QString fullFilePath = QUrl::fromPercentEncoding(substringList[1].toUtf8()).mid(1);
        emit this->filePath(fullFilePath); // 告诉进度窗口文件路径

        QFileInfo fileInfo = QFileInfo(fullFilePath);
        double fileSize = static_cast<double>(fileInfo.size());
        QString fileName = fileInfo.fileName();
        // 生成http响应,让下载方知道文件大小和文件名及文件类型
        QString response = "HTTP/1.1 200 OK\r\n";
        QMultiMap<QString, QString> headers;
        headers.insert("Content-Type", "application/octet-stream");
        headers.insert("Content-Disposition", QString("attachment; filename='%1'").arg(fileName));
        headers.insert("Content-Length", QString::number(fileSize, 'f', 0));
        for (const QString &key : headers.keys())response += key + ": " + headers.value(key) + "\r\n";
        response += "\r\n";

        // 发送响应头
        client->write(QByteArray(response.toUtf8()));
        client->waitForBytesWritten();

        // 发送文件内容并告诉主线程发送进度
        QFile file = QFile(fullFilePath);
        if (file.open(QIODevice::OpenModeFlag::ReadOnly))
        {
            double sendSize = 0; // 已发送数据大小
            // 循环读取文件内容
            while (!file.atEnd())
            {
                QByteArray data = file.read(1048576);                               // 每次最多读取1Mb(1024*1024)
                client->write(data);                                                // 发送内容
                client->waitForBytesWritten();                                      // 等待当前数据发送完毕再发送下一次数据
                sendSize += data.size();                                            // 记录发送大小
                emit this->Progress(static_cast<int>((sendSize / fileSize) * 100)); // 告诉主线程已发送数据的大小
            }
            file.close();
        }
        else
        {
            emit this->fileOpenError(); // 文件打开失败
        }
    }

    client->disconnectFromHost();
    client->close();
    client->deleteLater();
    emit this->finish(); // 发送完毕或文件打开失败,通知主线程
    this->exec();        // 进入事件循环,线程退出由主线程操作
}
