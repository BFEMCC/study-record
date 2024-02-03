from PySide6.QtCore import Slot, QByteArray, QFile
from PySide6.QtNetwork import QTcpServer, QHostAddress, QTcpSocket
from PySide6.QtWidgets import QApplication, QWidget

from Ui import Ui_Widget

response = "HTTP/1.1 200 OK\r\nserver : localhost\r\n\r\n"  # 正常访问,响应头
error = "HTTP/1.1 404 NOT FOUND\r\nserver : localhost\r\n\r\n"  # 404,响应头


class Widget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)

        self.ui = Ui_Widget()
        self.ui.setupUi(self)
        self.ui.data_edit.setStyleSheet("background-color: rgb(50,50,50);color:white")
        self.ui.data_edit.setReadOnly(True)
        self.setWindowTitle("Web Server")

        self.server = QTcpServer()  # 服务器对象
        self.host_address = QHostAddress(QHostAddress.LocalHost)  # 地址端口信息对象

        # 客户端连接，newConnection发射信号
        self.server.newConnection.connect(self.new_client)

        # 手动停止监听实现
        self.ui.stop_listen.clicked.connect(self.stop_listen)

        # 手动开始监听实现
        self.ui.start_listen.clicked.connect(self.star_listen)

        # 清空消息记录
        self.ui.clear.clicked.connect(self.ui.data_edit.clear)

    @Slot()  # 开始监听
    def star_listen(self):
        if not self.server.isListening():  # 如果不在监听
            self.server.listen(self.host_address, 80)  # 开始监听，指定地址和端口，不指定端口则随机选择端口
            self.ui.label.setText("监听中,端口：80")

    @Slot()  # 停止监听
    def stop_listen(self):
        if self.server.isListening():
            self.server.close(),
            self.ui.label.setText("停止监听")

    @Slot()  # 接收请求报文并发送应答报文
    def request_message(self, client_socket: QTcpSocket):

        addr = client_socket.peerAddress().toString() + ":" + str(client_socket.peerPort())  # 获取发送方地址和端口
        data = client_socket.readAll().data().decode("utf-8")  # 获取请求报文
        path = data.split(" ")[1]  # 对请求报文按空格进行分割,获取请求资源路径

        self.ui.data_edit.append("接收到：" + addr + "的数据：\n\n" + data)  # 显示请求报文
        self.ui.data_edit.append("请求资源路径：" + path + "\n")  # 显示请求的资源路径

        # 设置主页面
        if path == "/":
            path = "/index.html"

        if QFile("../static resource" + path).exists():  # 文件存在
            with open("../static resource" + path, "rb") as f:  # 打开资源文件
                response_body = f.read()
            client_socket.write(QByteArray(response.encode("utf-8") + response_body))  # 发送应答报文,响应头+响应体
            self.ui.data_edit.append("找到资源：" + path + ",已发送")

        else:  # 文件不存在,返回404
            with open("../static resource/404NOT FUOND.html", "rb") as f:
                response_body = f.read()  # 读取404页面
            client_socket.write(QByteArray(error.encode("utf-8") + response_body))
            self.ui.data_edit.append("未找到对应资源,返回404页面")

        client_socket.close()  # 应答报文发送完毕断开连接

    @Slot()  # 处理新连接
    def new_client(self):
        client_socket = self.server.nextPendingConnection()
        addr = client_socket.peerAddress().toString() + ":" + str(client_socket.peerPort())  # 获取连接地址和端口
        self.ui.data_edit.append(addr + "连接\n")  # 显示连接方的IP和端口

        # 接收到消息,readyRead发射信号
        client_socket.readyRead.connect(lambda: self.request_message(client_socket))

        # 客户端断开连接,disconnected发射信号
        client_socket.disconnected.connect(lambda: (
            self.ui.data_edit.append(addr + "：断开连接\n"),
            client_socket.close(),
            client_socket.deleteLater()
        ))


if __name__ == "__main__":
    app = QApplication()
    widget = Widget()
    widget.show()
    app.exec()
