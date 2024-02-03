import sys
from PySide6.QtCore import Slot, QUrl, QFile, QIODevice, Signal
from PySide6.QtNetwork import QNetworkRequest, QNetworkAccessManager
from PySide6.QtWidgets import QApplication
from PySide6.QtWidgets import QWidget
from qfluentwidgets import MessageBox
from ui_fileDownload import Ui_Form


class Widget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.ui = Ui_Form()

        self.ui.setupUi(self)
        self.ui.urlEdit.setReadOnly(True)
        self.ui.savePathEdit.setReadOnly(True)
        self.ui.ProgressBar.setMaximum(100)
        self.setWindowTitle("下载文件")

        self.networkManager = QNetworkAccessManager()  # 网络管理，协调网络操作

        self.ui.savePathEdit.setText(sys.argv[1])
        self.ui.urlEdit.setText(sys.argv[2])

    # 开始下载
    def starDownload(self):
        newUrl = QUrl.fromUserInput(self.ui.urlEdit.text())
        fullFileName = self.ui.savePathEdit.text() + '/' + newUrl.fileName()  # 文件路径+文件名

        if QFile.exists(fullFileName):
            QFile.remove(fullFileName)
        self.downloadFile = QFile(fullFileName)  # 下载保存的临时文件

        if not self.downloadFile.open(QIODevice.OpenModeFlag.WriteOnly):
            MessageBox('错误', '临时文件打开错误', self).exec()
            return
        self.ui.ProgressBar.setValue(0)

        # 发送网络请求，创建网络响应
        self.reply = self.networkManager.get(QNetworkRequest(newUrl))

        self.reply.readyRead.connect(self.do_readyRead)
        self.reply.downloadProgress.connect(self.do_downloadProgress)
        self.reply.finished.connect(self.do_finished)

    @Slot()
    def do_readyRead(self):
        self.downloadFile.write(self.reply.readAll())

    @Slot()
    def do_downloadProgress(self, *args, **kwargs):  # int
        if args[1] > 0:
            progress = (args[0] / args[1]) * 100  # float
            self.ui.ProgressBar.setValue(int(progress))  # int

    finish = Signal()

    @Slot()
    def do_finished(self):
        self.downloadFile.close()
        self.downloadFile.deleteLater()
        self.reply.deleteLater()
        self.finish.emit()


if __name__ == '__main__':
    app = QApplication()
    w = Widget()
    w.finish.connect(w.close)
    w.show()
    w.starDownload()
    app.exec()
