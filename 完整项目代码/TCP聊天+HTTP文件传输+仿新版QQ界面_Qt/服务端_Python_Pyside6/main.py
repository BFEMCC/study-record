import rec  # 资源文件,ide无提示但不可删除
import ctypes
import subprocess
from copy import copy
from typing import Dict
from urllib.parse import unquote
from PySide6.QtCore import QRegularExpression, Slot, QDateTime, QByteArray, QStandardPaths, QCoreApplication, QUrl
from PySide6.QtGui import QRegularExpressionValidator, QIntValidator, QDesktopServices, QIcon
from PySide6.QtNetwork import QTcpServer, QHostAddress, QTcpSocket, QNetworkInterface, QAbstractSocket
from PySide6.QtWidgets import QApplication, QVBoxLayout, QFileDialog, QWidget
from qfluentwidgets import CheckBox, FluentIcon, setTheme, Theme, toggleTheme, isDarkTheme, MessageBox
from sendFileThread import sendFileThread
from progressWidget import progressWidget
from ui_widget import Ui_Widget


dwmapi = ctypes.windll.dwmapi  # 加载dwmapi.dll
DWMWA_USE_IMMERSIVE_DARK_MODE = 20  # 定义常量


# 定义winAPi COLORREF结构体
class COLORREF(ctypes.Structure):
    _fields_ = [("rgbRed", ctypes.c_byte),
                ("rgbGreen", ctypes.c_byte),
                ("rgbBlue", ctypes.c_byte),
                ("rgbReserved", ctypes.c_byte)]


# 设置或取消标题栏深色模式
def set_title_bar_dark_mode(hwnd, enable_dark_mode):
    if not hwnd:
        return False
    value = ctypes.c_int(enable_dark_mode)
    result = dwmapi.DwmSetWindowAttribute(
        hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, ctypes.byref(value), ctypes.sizeof(value))
    return result == 0


MATCH_KEY = "RbURpoNPc2MAcHknE1Gm"  # 匹配密钥, 确认是在发送文件
valid_download_link = set()


def fileDownload(savePath: str, url: str):
    exe_file = "./fileDownload.exe"
    args = [savePath, url]  # 传递的参数列表
    return subprocess.Popen([exe_file] + args, start_new_session=True)


class Widget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.ui = Ui_Widget()
        self.ui.setupUi(self)

        self.vboxLayout = QVBoxLayout(self.ui.VboxWidget)
        self.tcpserver = QTcpServer(self)
        self.address = QHostAddress()
        self.clients: Dict[QTcpSocket, CheckBox] = {}
        self.saveFilePath = QCoreApplication.applicationDirPath()  # 默认的文件保存路径, 当前的程序目录
        self.newPort = "None"

        self.inItUi()  # 初始化控件
        self.connectSlots()  # 槽函数连接

    def connectSlots(self):
        self.ui.startListen.clicked.connect(self.starListen)  # 开始监听
        self.tcpserver.newConnection.connect(self.newConnect)  # 客户端连接
        self.ui.stopListen.clicked.connect(self.stopLinten)  # 停止监听
        self.ui.disconnectAll.clicked.connect(self.disconnectAll)  # 断开所有连接
        self.ui.clearMessage.clicked.connect(self.ui.messageEdit.clear)  # 清空消息记录
        self.ui.WLANaddress.clicked.connect(
            lambda: self.ui.addressEdit.setText(self.getWirelessIPv4Address()))  # 使用本机无线局域网IPv4地
        self.ui.localAddressBtn.clicked.connect(lambda: self.ui.addressEdit.setText("127.0.0.1"))  # 使用本机地址
        self.ui.selectAll.clicked.connect(self.selectAllClient)  # 客户端全选
        self.ui.sendMessageBtn.clicked.connect(self.sendMsgToSelectClient)  # 向选中客户端发送文本消息
        self.ui.sendFileBtn.clicked.connect(self.sendFileToSelectClient)  # 向选中客户端发送文件
        self.ui.disconnectSelect.clicked.connect(self.disconnectSelectClient)  # 断开选中的客户端
        self.ui.setSavePath.clicked.connect(self.setSavePath)  # 设置文件保存路径
        self.ui.openSavePath.clicked.connect(self.openSavePathFolder)  # 打开保存文件的文件夹
        self.ui.switchTopics.clicked.connect(self.toggleTheme)  # 切换深色/浅色主题

    @Slot()  # 开始监听
    def starListen(self):
        if not self.tcpserver.isListening():
            self.address.setAddress(self.ui.addressEdit.text())  # 设置Ip地址
            if len(self.ui.portEdit.text()) == 0:
                self.tcpserver.listen(self.address)  # 未指定则随机端口
                self.ui.portEdit.setText(str(self.tcpserver.serverPort()))
            else:
                self.tcpserver.listen(self.address, int(self.ui.portEdit.text()))

            # 控件状态更新
            self.ui.startListen.setEnabled(False)  # 开始监听
            self.ui.stopListen.setEnabled(True)  # 停止监听
            self.ui.WLANaddress.setEnabled(False)  # 使用无线网IP
            self.ui.localAddressBtn.setEnabled(False)  # 使用本机地址
            self.ui.addressEdit.setEnabled(False)  # IP地址文本框
            self.ui.portEdit.setEnabled(False)  # 端口文本框

            # 状态栏更新
            self.ui.state_listenState.setText("监听状态：正在监听")
            self.ui.state_listenAddress.setText("监听地址：" + self.ui.addressEdit.text())
            self.ui.state_listenPort.setText("监听端口：" + self.ui.portEdit.text())

    @Slot()  # 停止监听
    def stopLinten(self):
        if self.tcpserver.isListening():
            self.tcpserver.close()
            # 控件可选状态更新
            self.ui.startListen.setEnabled(True)  # 开始监听
            self.ui.stopListen.setEnabled(False)  # 停止监听
            self.ui.WLANaddress.setEnabled(True)  # 使用无线网IP
            self.ui.localAddressBtn.setEnabled(True)  # 使用本机地址
            self.ui.addressEdit.setEnabled(True)  # 监听地址文本框
            self.ui.portEdit.setEnabled(True)  # 监听端口文本框
            self.ui.state_listenState.setText("监听状态：停止监听")
            self.ui.state_listenAddress.setText("监听地址：")
            self.ui.state_listenPort.setText("监听端口：")
            if len(self.clients) == 0:
                self.ui.disconnectAll.setEnabled(False)  # 断开所有连接

    @Slot()  # 新连接
    def newConnect(self):
        # 连接后自动创建一个QTcpSocket对象
        tcpsocket = self.tcpserver.nextPendingConnection()
        clientaddr = tcpsocket.peerAddress().toString() + ":" + str(tcpsocket.peerPort())
        self.ui.messageEdit.append(self.datatime() + "-" + clientaddr + "连接服务器")  # 更新消息记录
        checkbox = CheckBox(clientaddr, self.ui.VboxWidget)  # 创建checkbox
        self.vboxLayout.addWidget(checkbox)  # 加入客户端列表的垂直布局中
        self.clients[tcpsocket] = checkbox  # 存入字典
        self.ui.state_cilentNum.setText(str(len(self.clients)))  # 更新客户端数量
        checkbox.clicked.connect(self.checkBoxUpDate)
        # 更新控件状态
        if self.ui.selectAll.isChecked():
            checkbox.setChecked(True)
        self.ui.sendMessageBtn.setEnabled(True)  # 向选中客户端发送消息
        self.ui.disconnectAll.setEnabled(True)  # 断开所有连接
        self.ui.sendFileBtn.setEnabled(True)  # 向选中客户端发送文件
        self.ui.disconnectSelect.setEnabled(True)  # 断开选中客户端
        self.ui.selectAll.setEnabled(True)
        tcpsocket.readyRead.connect(lambda: self.rcevClientMessage(tcpsocket))
        tcpsocket.disconnected.connect(lambda: self.clientDisconnect(tcpsocket))

    @Slot()  # 断开所有连接
    def disconnectAll(self):
        for socket, checkbox in copy(self.clients).items():
            if socket.state() == QAbstractSocket.SocketState.ConnectedState:
                socket.disconnectFromHost()

        self.ui.state_cilentNum.setText(str(len(self.clients)))  # 更新客户端数量
        # 更新控件选中状态
        self.ui.disconnectAll.setEnabled(False)
        self.ui.selectAll.setChecked(False)
        self.ui.selectAll.setEnabled(False)
        self.ui.disconnectSelect.setEnabled(False)
        self.ui.sendMessageBtn.setEnabled(False)
        self.ui.sendFileBtn.setEnabled(False)

        self.clients.clear()  # 清空容器

    @Slot()  # 客户端全选
    def selectAllClient(self, isChecked: bool):
        for socket, checkbox in self.clients.items():
            if isChecked:
                checkbox.setChecked(True)
            else:
                checkbox.setChecked(False)

    @Slot()  # 断开选中的客户端连接
    def disconnectSelectClient(self):
        if self.ui.selectAll.isChecked():
            self.disconnectAll()
            return
        for client in self.SelectClientList():
            client.disconnectFromHost()  # 会触发disconnected信号

    @Slot()  # 向选中客户端发送消息
    def sendMsgToSelectClient(self):
        message = self.ui.sendEdit.toPlainText().encode("utf8")
        if len(message) == 0:
            return
        for client in self.SelectClientList():
            clientaddr = client.peerAddress().toString() + ":" + str(client.peerPort())
            client.write(QByteArray(message))
            self.ui.messageEdit.append(self.datatime() + "向" + clientaddr + "发送" + message.decode("utf8"))
        self.ui.sendEdit.clear()

    @Slot()  # 向选中客户算发送文件(发送文件下载链接)
    def sendFileToSelectClient(self):
        filePath = QFileDialog.getOpenFileName(self, "选择发送文件", QStandardPaths.writableLocation(
            QStandardPaths.HomeLocation))[0]  # 获取待发送文件的路径
        if len(filePath) == 0:  # 取消发送
            return
        valid_download_link.add('/' + filePath)  # 存储文件地址
        downloadPath = (MATCH_KEY +
                        'http://' + self.tcpserver.serverAddress().toString() + ':' +
                        str(self.tcpserver.serverPort()) + '/' + filePath)

        # 向选中客户端发送文件下载链接
        for client in self.SelectClientList():
            clientaddr = client.peerAddress().toString() + ":" + str(client.peerPort())
            client.write(QByteArray(downloadPath.encode("utf8")))
            self.ui.messageEdit.append(self.datatime() + "向" + clientaddr + "发送文件下载链接:" + downloadPath)

    @Slot()  # 任何一个客户端取消选中,全选复选框取消选中,所有客户端复选框选中,全选框选中
    def checkBoxUpDate(self, isChecked: bool):
        if not isChecked:
            self.ui.selectAll.setChecked(False)
            return
        elif isChecked and len(self.SelectClientList()) == int(self.ui.state_cilentNum.text()):
            self.ui.selectAll.setChecked(True)

    @Slot()  # 设置接收到的文件保存的路径
    def setSavePath(self):
        self.saveFilePath = QFileDialog.getExistingDirectory(self, "设置文件保存路径", QStandardPaths.writableLocation(
            QStandardPaths.DownloadLocation))  # 获取文件路径
        if len(self.saveFilePath) == 0:  # 取消了文件夹选择
            self.saveFilePath = QCoreApplication.applicationDirPath()  # 默认的文件保存路径, 当前的程序目录

    @Slot()  # 打开保存文件的文件夹
    def openSavePathFolder(self):
        QDesktopServices.openUrl(QUrl(self.saveFilePath))

    @Slot()  # 切换深/浅主题
    def toggleTheme(self):
        toggleTheme()
        if isDarkTheme():  # 如果切换后是深色主题
            set_title_bar_dark_mode(self.winId(), True)
            self.setStyleSheet("CardWidget{background-color:rgb(33,39,54)}")
            self.ui.clientListScrollArea.setStyleSheet("background-color:rgb(33,39,54)")
        else:
            set_title_bar_dark_mode(self.winId(), False)
            self.setStyleSheet("CardWidget{background-color:rgb(244,244,244)")
            self.ui.clientListScrollArea.setStyleSheet("background-color:rgb(240,240,240)")

    @Slot()  # 文件发送完毕时,断开接收文件的客户端
    def disconnectRecvFileCilent(self, client: QTcpSocket):
        client.disconnectFromHost()

    @Slot()
    def sendFileError(self):
        error = MessageBox("文件发送失败", "文件打开错误,请检查文件是否存在", self)
        error.exec()

    @staticmethod  # 获取本机无线局域网IPv4地址
    def getWirelessIPv4Address():
        for i in QNetworkInterface.allInterfaces():
            if i.name() == "wireless_32768":  # 无线局域网适配器的网络接口名称
                for k in i.addressEntries():
                    if k.ip().protocol() == QAbstractSocket.NetworkLayerProtocol.IPv4Protocol:
                        return k.ip().toString()
        return "127.0.0.1"

    @staticmethod  # 获取当前时间并格式化
    def datatime():
        return QDateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")

    # 初始化控件和UI
    def inItUi(self):
        self.ui.addressEdit.setValidator(QRegularExpressionValidator(  # 限制IP文本框输入限制
            QRegularExpression(r"^(1\d{2}|2[0-4]\d|25[0-5]|[1-9]\d|[1-9])\."
                               r"(1\d{2}|2[0-4]\d|25[0-5]|[1-9]\d|\d)\."
                               r"(1\d{2}|2[0-4]\d|25[0-5]|[1-9]\d|\d)\."
                               r"(1\d{2}|2[0-4]\d|25[0-5]|[1-9]\d|\d)$")))
        self.ui.portEdit.setValidator(QIntValidator(0, 65535, self))  # 限制端口号输入

        # 设置图标
        self.ui.setSavePath.setIcon(FluentIcon.SETTING)
        self.ui.openSavePath.setIcon(FluentIcon.FOLDER)
        self.ui.sendMessageBtn.setIcon(FluentIcon.MESSAGE)
        self.ui.sendFileBtn.setIcon(FluentIcon.SEND_FILL)
        self.ui.startListen.setIcon(FluentIcon.PLAY)
        self.ui.stopListen.setIcon(FluentIcon.PAUSE)
        self.ui.WLANaddress.setIcon(FluentIcon.WIFI)
        self.ui.localAddressBtn.setIcon(FluentIcon.COMMAND_PROMPT)
        self.ui.switchTopics.setIcon(FluentIcon.CONSTRACT)

        # 设置悬浮提示
        self.ui.startListen.setToolTip("开始监听")
        self.ui.stopListen.setToolTip("停止监听")
        self.ui.WLANaddress.setToolTip("使用无线局域网的IPv4地址\n若获取失败则使用环回地址")
        self.ui.setSavePath.setToolTip("设置接收文件的保存路径")
        self.ui.openSavePath.setToolTip("打开文件保存的文件夹")
        self.ui.sendMessageBtn.setToolTip("向选中客户端发送文本消息")
        self.ui.sendFileBtn.setToolTip("向选中客户端发送文件")
        self.ui.localAddressBtn.setToolTip("使用环回地址:127.0.0.1")
        self.ui.switchTopics.setToolTip("切换深色/浅色主题")
        self.ui.disconnectAll.setToolTip("断开所有连接")
        self.ui.disconnectSelect.setToolTip("断开选中的客户端")
        self.ui.selectAll.setToolTip("选中所有客户端")
        self.ui.clearMessage.setToolTip("清空消息记录文本框")

        # 初始化控件状态
        self.ui.stopListen.setEnabled(False)  # 停止监听按钮
        self.ui.sendMessageBtn.setEnabled(False)  # 向客户端发送消息
        self.ui.disconnectAll.setEnabled(False)  # 断开所有连接
        self.ui.sendFileBtn.setEnabled(False)  # 向客户端发送文件
        self.ui.disconnectSelect.setEnabled(False)  # 断开选中客户端
        self.ui.selectAll.setEnabled(False)  # 全选框
        self.ui.messageEdit.setReadOnly(True)  # 消息记录文本框

        self.ui.addressEdit.setClearButtonEnabled(True)
        self.ui.portEdit.setClearButtonEnabled(True)

        # 客户端列表垂直布局
        self.ui.VboxWidget.setLayout(self.vboxLayout)

        # 设置主题色
        setTheme(Theme.AUTO)  # 跟随系统
        if isDarkTheme():  # 如果是深色主题
            set_title_bar_dark_mode(self.winId(), True)
            self.setStyleSheet("CardWidget{background-color:rgb(33,39,54)}")
            self.ui.clientListScrollArea.setStyleSheet("background-color:rgb(33,39,54)")

    # 接收到客户端消息
    def rcevClientMessage(self, tcpsocket: QTcpSocket):
        clientaddr = tcpsocket.peerAddress().toString() + ":" + str(tcpsocket.peerPort())

        data = tcpsocket.readAll().data().decode("utf8")

        # 客户端发来文件
        if MATCH_KEY in data:
            url = data[data.find(MATCH_KEY) + len(MATCH_KEY):]
            url = url.replace("clientIP", tcpsocket.peerAddress().toString())

            if MessageBox('客户端发来文件', '是否接收？\n下载链接：' + url, self).exec():
                # 运行用于下载的文件
                fileDownload(self.saveFilePath, url=url)
                self.ui.messageEdit.append(
                    self.datatime() + " 接收到来自" + clientaddr + "的文件下载链接：" + url + "\n确认接收")
            else:
                self.ui.messageEdit.append(
                    self.datatime() + " 接收到来自" + clientaddr + "的文件下载链接：" + url + "\n取消下载")
        else:
            # 对接收到的消息进行切割
            substring = data.split(" ")  # 按空格进行分割
            # 如果是正确的请求报文
            if (len(substring) >= 3
                    and (substring[0] == "GET")
                    and (unquote(substring[1], encoding='utf-8') in valid_download_link)  # 资源路径要进行url转码
                    and ("HTTP/1.1" in substring[2])):
                fullFilePath = unquote(substring[1][1:], encoding='utf-8')  # 资源路径进行url转码
                self.ui.messageEdit.append(
                    self.datatime() + clientaddr + "接收了文件：" + fullFilePath + '\n' + "开始向对方发送")  # 显示日志

                send_fileThread = sendFileThread(fullFilePath, tcpsocket, self)  # 发送文件线程
                sendProgressWidget = progressWidget(self)  # 发送进度窗口
                sendProgressWidget.setTips("发送进度")
                send_fileThread.finish.connect(self.disconnectRecvFileCilent)  # 发送完毕断开接收文件的客户端,并显示日志
                send_fileThread.finish.connect(lambda: self.ui.messageEdit.append(
                    self.datatime() + "向" + clientaddr + "发送的文件：" + fullFilePath + '\n' + "发送完毕"))  # 显示日志
                send_fileThread.finish.connect(sendProgressWidget.close)  # 发送完毕关闭进度显示窗口,释放内存
                send_fileThread.fileOpenError.connect(self.sendFileError)  # 发送文件时,文件打开失败的处理
                send_fileThread.Progress.connect(sendProgressWidget.updateProgress)  # 更新发送进度

                sendProgressWidget.show()  # 显示发送进度窗口
                send_fileThread.start()  # 启动发送文件线程

            # 当作文本消息处理
            else:
                self.ui.messageEdit.append(self.datatime() + " 接收到来自" + clientaddr + "的消息：" + data)

    # 客户端断开连接
    def clientDisconnect(self, tcpsocket: QTcpSocket):
        # 更新消息记录
        clientaddr = tcpsocket.peerAddress().toString() + ":" + str(tcpsocket.peerPort())
        self.ui.messageEdit.append(self.datatime() + "-" + clientaddr + "断开连接")

        # 获取断开连接的客户端对应的checkbox, 移除复选框
        disconnectCheckbox = self.clients[tcpsocket]
        disconnectCheckbox.close()
        self.vboxLayout.removeWidget(disconnectCheckbox)
        disconnectCheckbox.deleteLater()

        self.clients.pop(tcpsocket)  # 从字典中移除
        self.ui.state_cilentNum.setText(str(len(self.clients)))  # 更新客户端数量
        # 关闭并释放
        tcpsocket.close()
        tcpsocket.deleteLater()

    # 获取选中客户端列表
    def SelectClientList(self):
        SL = []
        for i in self.ui.VboxWidget.findChildren(CheckBox):
            for socket, checkbox in self.clients.items():
                if i.isChecked() and id(i) == id(checkbox):
                    SL.append(socket)
        return SL


if __name__ == '__main__':
    app = QApplication()
    w = Widget()
    w.setWindowIcon(QIcon(":/ico/server.ico"))  # 设置程序图标
    w.setWindowTitle("TCPServer")  # 设置程序标题
    w.show()
    app.exec()
