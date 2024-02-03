from PySide6.QtCore import (QCoreApplication, QMetaObject)
from PySide6.QtWidgets import (QGridLayout, QHBoxLayout, QLabel,
                               QPushButton, QTextEdit, QVBoxLayout,
                               QWidget)


class Ui_Widget(object):
    def __init__(self):
        self.label = None
        self.pushButton_5 = None
        self.pushButton_2 = None
        self.clear = None
        self.stop_listen = None
        self.start_listen = None
        self.horizontalLayout = None
        self.widget_2 = None
        self.data_edit = None
        self.verticalLayout = None
        self.widget = None
        self.gridLayout = None

    def setupUi(self, Widget):
        if not Widget.objectName():
            Widget.setObjectName(u"Widget")
        Widget.resize(535, 441)
        self.gridLayout = QGridLayout(Widget)
        self.gridLayout.setObjectName(u"gridLayout")
        self.widget = QWidget(Widget)
        self.widget.setObjectName(u"widget")
        self.verticalLayout = QVBoxLayout(self.widget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.data_edit = QTextEdit(self.widget)
        self.data_edit.setObjectName(u"data_edit")

        self.verticalLayout.addWidget(self.data_edit)

        self.widget_2 = QWidget(self.widget)
        self.widget_2.setObjectName(u"widget_2")
        self.horizontalLayout = QHBoxLayout(self.widget_2)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.start_listen = QPushButton(self.widget_2)
        self.start_listen.setObjectName(u"start_listen")

        self.horizontalLayout.addWidget(self.start_listen)

        self.stop_listen = QPushButton(self.widget_2)
        self.stop_listen.setObjectName(u"stop_listen")

        self.horizontalLayout.addWidget(self.stop_listen)

        self.clear = QPushButton(self.widget_2)
        self.clear.setObjectName(u"clear")

        self.horizontalLayout.addWidget(self.clear)

        self.pushButton_2 = QPushButton(self.widget_2)
        self.pushButton_2.setObjectName(u"pushButton_2")

        self.horizontalLayout.addWidget(self.pushButton_2)

        self.pushButton_5 = QPushButton(self.widget_2)
        self.pushButton_5.setObjectName(u"pushButton_5")

        self.horizontalLayout.addWidget(self.pushButton_5)

        self.verticalLayout.addWidget(self.widget_2)

        self.gridLayout.addWidget(self.widget, 0, 0, 1, 1)

        self.label = QLabel(Widget)
        self.label.setObjectName(u"label")

        self.gridLayout.addWidget(self.label, 1, 0, 1, 1)

        self.retranslateUi(Widget)

        QMetaObject.connectSlotsByName(Widget)

    # setupUi

    def retranslateUi(self, Widget):
        Widget.setWindowTitle(QCoreApplication.translate("Widget", u"Widget", None))
        self.start_listen.setText(QCoreApplication.translate("Widget", u"\u5f00\u59cb\u76d1\u542c", None))
        self.stop_listen.setText(QCoreApplication.translate("Widget", u"\u505c\u6b62\u76d1\u542c", None))
        self.clear.setText(QCoreApplication.translate("Widget", u"\u6e05\u7a7a\u6587\u672c\u6846", None))
        self.pushButton_2.setText("")
        self.pushButton_5.setText("")
        self.label.setText(QCoreApplication.translate("Widget", u"\u505c\u6b62\u76d1\u542c", None))
    # retranslateUi

