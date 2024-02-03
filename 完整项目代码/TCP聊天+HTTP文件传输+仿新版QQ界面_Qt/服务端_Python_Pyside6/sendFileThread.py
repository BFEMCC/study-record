from PySide6.QtCore import QThread, Signal, QFileInfo, QByteArray, QFile, QIODevice
from PySide6.QtNetwork import QTcpSocket

"""发送文件线程"""


class sendFileThread(QThread):
    def __init__(self, fullFilePath: str, clientSocket: QTcpSocket, parent=None):
        super().__init__(parent)
        self.filePath = fullFilePath
        self.client = clientSocket

    Progress = Signal(int)  # 告诉主线程进度窗口发送进度
    finish = Signal(QTcpSocket)  # 告诉主线程当前的客户端发送完毕
    fileOpenError = Signal()  # 告诉文件打开错误

    def run(self):
        fileInfo = QFileInfo(self.filePath)
        fileSize = fileInfo.size()
        # 格式化http响应头,让下载方知道文件大小和文件名及文件类型
        response = ("HTTP/1.1 200 OK\r\n" +
                    "Content-Type: application/octet-stream\r\n" +
                    "Content-Disposition: attachment; filename='{}'\r\n" +
                    "Content-Length: {}\r\n\r\n").format(fileInfo.fileName(), fileSize)
        # 发送响应头
        self.client.write(QByteArray(response.encode("utf8")))
        self.client.waitForBytesWritten()

        # 发送文件内容并告诉主线程发送进度
        file = QFile(self.filePath)
        if file.open(QIODevice.OpenModeFlag.ReadOnly):
            sendSize: int = 0  # 已发送数据大小
            # 循环读取文件内容
            while not file.atEnd():
                data = file.read(1048576)  # 每次最多读取1Mb(1024*1024)
                self.client.write(data)  # 发送内容
                self.client.waitForBytesWritten()  # 等待当前数据发送完毕再发送下一次数据
                sendSize += data.size()  # 记录发送大小
                self.Progress.emit((sendSize / fileSize) * 100)  # 告诉主线程已发送数据的大小
        else:
            self.fileOpenError.emit()  # 文件打开失败

        # 发送完毕或文件打开失败,通知主线程关闭连接
        self.finish.emit(self.client)

        # 释放资源,结束线程
        file.close()
        file.deleteLater()
        self.deleteLater()
        self.exit()
