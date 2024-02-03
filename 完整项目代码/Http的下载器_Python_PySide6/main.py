from PySide6.QtCore import Slot, QStandardPaths, QCoreApplication, \
    QUrl, QFileInfo, QFile, QIODevice
from PySide6.QtGui import QDesktopServices
from PySide6.QtNetwork import QNetworkRequest, QNetworkAccessManager
from PySide6.QtWidgets import QApplication, QFileDialog
from PySide6.QtWidgets import QWidget
from qfluentwidgets import MessageBox

from ui_widget import Ui_Widget


class Widget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.ui = Ui_Widget()

        self.ui.setupUi(self)
        self.ui.LineEdit.setReadOnly(True)
        self.ui.ProgressBar.setMaximum(100)
        self.ui.LineEdit_3.setClearButtonEnabled(True)
        self.ui.LineEdit.setText(QStandardPaths.writableLocation(QStandardPaths.DownloadLocation))  # 默认下载路径

        self.ui.PrimaryPushButton_2.clicked.connect(self.setSavePath)  # 设置下载路径
        self.ui.PrimaryPushButton.clicked.connect(self.starDownload)  # 开始下载
        self.ui.PrimaryPushButton_3.clicked.connect(self.openSavePathFolder)  # 打开下载目录

        self.networkManager = QNetworkAccessManager()  # 网络管理，协调网络操作

    @Slot()  # 设置保存路径
    def setSavePath(self):
        saveFilePath = QFileDialog.getExistingDirectory(self, "设置下载文件的保存路径", QStandardPaths.writableLocation(
            QStandardPaths.DownloadLocation))  # 获取文件路径
        if len(saveFilePath) == 0:  # 取消了文件夹选择
            saveFilePath = QCoreApplication.applicationDirPath()  # 默认的文件保存路径
        self.ui.LineEdit.setText(saveFilePath)

    @Slot()  # 打开保存文件的文件夹
    def openSavePathFolder(self):
        QDesktopServices.openUrl(QUrl(self.ui.LineEdit.text()))

    @Slot()  # 开始下载
    def starDownload(self):
        urlSpec = self.ui.LineEdit_3.text()
        if len(urlSpec) == 0:
            erromsg = MessageBox('URL为空', '请输入正确的URL', self)
            erromsg.exec()
            return
        newUrl = QUrl.fromUserInput(urlSpec)
        if not newUrl.isValid():
            erromsg = MessageBox('无效URL', '这是一个无效的URL\n' + newUrl.errorString(), self)
            erromsg.exec()
            return

        fullFileName = self.ui.LineEdit.text() + '/' + newUrl.fileName()  # 文件路径+文件名

        if QFile.exists(fullFileName):
            QFile.remove(fullFileName)
        self.downloadFile = QFile(fullFileName)  # 下载保存的临时文件
        if not self.downloadFile.open(QIODevice.WriteOnly):
            erromsg = MessageBox('错误', '临时文件打开错误', self)
            erromsg.exec()
            return
        self.ui.PrimaryPushButton.setEnabled(False)
        self.ui.ProgressBar.setValue(0)

        # 发送网络请求，创建网络响应
        self.reply = self.networkManager.get(QNetworkRequest(newUrl))

        self.reply.readyRead.connect(self.do_readyRead)
        self.reply.downloadProgress.connect(self.do_downloadProgress)
        self.reply.finished.connect(self.do_finished)

    @Slot()
    def do_readyRead(self):
        self.downloadFile.write(self.reply.readAll())
        return

    @Slot()
    def do_downloadProgress(self, *args, **kwargs):
        self.ui.ProgressBar.setValue(int(args[0])/int(args[1])*100)
        return

    @Slot()
    def do_finished(self):
        fileInfo = QFileInfo(self.downloadFile.fileName())
        self.downloadFile.close()
        self.downloadFile.deleteLater()
        self.reply.deleteLater()
        self.ui.PrimaryPushButton.setEnabled(True)
        return


if __name__ == '__main__':
    app = QApplication()
    w = Widget()
    w.setWindowTitle("基于HTTP的文件下载")  # 设置程序标题
    w.show()
    app.exec()
