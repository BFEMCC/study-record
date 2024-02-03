from PySide6.QtCore import Qt, Slot
from PySide6.QtWidgets import QDialog

from ui_progressWidget import Ui_Form

"""进度窗口"""


class progressWidget(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        self.ui.ProgressRing.setMaximum(100)
        self.setModal(False)
        self.setAttribute(Qt.WidgetAttribute.WA_DeleteOnClose)  # 设置在关闭时自动删除

    @Slot()
    def updateProgress(self, progress: int):
        self.ui.ProgressRing.setValue(progress)

    def setTips(self, tip: str):
        self.ui.tips_label.setText(tip)
