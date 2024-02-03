from PySide6.QtNetwork import QTcpServer, QHostAddress
from PySide6.QtCore import Slot
from PySide6.QtWidgets import QApplication, QWidget, QTextEdit

server = QTcpServer()  # 服务器对象
host_address = QHostAddress(QHostAddress.LocalHost)  # 地址端口信息对象


@Slot()
def new_client():
    client_socket = server.nextPendingConnection()

    print("有客户端连接：", client_socket.peerAddress().toString(), ":", client_socket.peerPort())

    # 接收到消息,readyRead发射信号
    client_socket.readyRead.connect(
        lambda: print("接收到：", client_socket.peerAddress().toString(), ":", client_socket.peerPort(), "的消息：",
                      client_socket.readAll().data().decode("utf8")))

    # 客户端断开连接,disconnected发射信号
    # 客户端断开连接,disconnected发射信号
    client_socket.disconnected.connect(lambda: (
        print(client_socket.peerAddress().toString(), ":", client_socket.peerPort(), "：断开连接"),
        client_socket.close(),
        client_socket.deleteLater()
    ))

    """
    多客户端，发送消息建议使用GUI界面，这里不写代码
    """


if __name__ == '__main__':
    a = QApplication()
    w = QWidget()

    text_edit = QTextEdit(w)

    if not server.isListening():  # 如果不在监听
        server.listen(host_address, 8080)  # 开始监听，指定地址和端口，不指定端口则随机选择端口
        print("服务器已启动,监听中")

    # 客户端连接，newConnection发射信号
    server.newConnection.connect(new_client)

    w.show()
    a.exec()
