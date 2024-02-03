# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'widget.ui'
##
## Created by: Qt User Interface Compiler version 6.6.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
                            QMetaObject, QObject, QPoint, QRect,
                            QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
                           QFont, QFontDatabase, QGradient, QIcon,
                           QImage, QKeySequence, QLinearGradient, QPainter,
                           QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QGridLayout, QHBoxLayout, QSizePolicy,
                               QSpacerItem, QVBoxLayout, QWidget)

from qfluentwidgets import (BodyLabel, CaptionLabel, CardWidget, CheckBox,
                            ElevatedCardWidget, LineEdit, PrimaryPushButton, PrimaryToolButton,
                            PushButton, ScrollArea, SimpleCardWidget, StrongBodyLabel,
                            TextEdit, ToolButton)


class Ui_Widget(object):
    def setupUi(self, Widget):
        if not Widget.objectName():
            Widget.setObjectName(u"Widget")
        Widget.resize(668, 544)
        self.gridLayout_3 = QGridLayout(Widget)
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.gridLayout_3.setContentsMargins(0, 0, 0, 0)
        self.CardWidget_2 = CardWidget(Widget)
        self.CardWidget_2.setObjectName(u"CardWidget_2")
        self.verticalLayout = QVBoxLayout(self.CardWidget_2)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(9, 9, 9, 6)
        self.ElevatedCardWidget_2 = ElevatedCardWidget(self.CardWidget_2)
        self.ElevatedCardWidget_2.setObjectName(u"ElevatedCardWidget_2")
        self.horizontalLayout = QHBoxLayout(self.ElevatedCardWidget_2)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.addressLabel = BodyLabel(self.ElevatedCardWidget_2)
        self.addressLabel.setObjectName(u"addressLabel")

        self.horizontalLayout.addWidget(self.addressLabel)

        self.addressEdit = LineEdit(self.ElevatedCardWidget_2)
        self.addressEdit.setObjectName(u"addressEdit")
        self.addressEdit.setMinimumSize(QSize(138, 33))

        self.horizontalLayout.addWidget(self.addressEdit)

        self.WLANaddress = PrimaryPushButton(self.ElevatedCardWidget_2)
        self.WLANaddress.setObjectName(u"WLANaddress")
        sizePolicy = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.WLANaddress.sizePolicy().hasHeightForWidth())
        self.WLANaddress.setSizePolicy(sizePolicy)

        self.horizontalLayout.addWidget(self.WLANaddress)

        self.localAddressBtn = PrimaryPushButton(self.ElevatedCardWidget_2)
        self.localAddressBtn.setObjectName(u"localAddressBtn")
        sizePolicy.setHeightForWidth(self.localAddressBtn.sizePolicy().hasHeightForWidth())
        self.localAddressBtn.setSizePolicy(sizePolicy)

        self.horizontalLayout.addWidget(self.localAddressBtn)

        self.portLabel = BodyLabel(self.ElevatedCardWidget_2)
        self.portLabel.setObjectName(u"portLabel")

        self.horizontalLayout.addWidget(self.portLabel)

        self.portEdit = LineEdit(self.ElevatedCardWidget_2)
        self.portEdit.setObjectName(u"portEdit")
        self.portEdit.setMinimumSize(QSize(122, 33))

        self.horizontalLayout.addWidget(self.portEdit)

        self.verticalLayout.addWidget(self.ElevatedCardWidget_2)

        self.ElevatedCardWidget_3 = ElevatedCardWidget(self.CardWidget_2)
        self.ElevatedCardWidget_3.setObjectName(u"ElevatedCardWidget_3")
        self.horizontalLayout_3 = QHBoxLayout(self.ElevatedCardWidget_3)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.startListen = PrimaryPushButton(self.ElevatedCardWidget_3)
        self.startListen.setObjectName(u"startListen")

        self.horizontalLayout_3.addWidget(self.startListen)

        self.stopListen = PrimaryPushButton(self.ElevatedCardWidget_3)
        self.stopListen.setObjectName(u"stopListen")

        self.horizontalLayout_3.addWidget(self.stopListen)

        self.disconnectAll = PushButton(self.ElevatedCardWidget_3)
        self.disconnectAll.setObjectName(u"disconnectAll")

        self.horizontalLayout_3.addWidget(self.disconnectAll)

        self.clearMessage = PushButton(self.ElevatedCardWidget_3)
        self.clearMessage.setObjectName(u"clearMessage")

        self.horizontalLayout_3.addWidget(self.clearMessage)

        self.setSavePath = PrimaryToolButton(self.ElevatedCardWidget_3)
        self.setSavePath.setObjectName(u"setSavePath")

        self.horizontalLayout_3.addWidget(self.setSavePath)

        self.openSavePath = PrimaryToolButton(self.ElevatedCardWidget_3)
        self.openSavePath.setObjectName(u"openSavePath")

        self.horizontalLayout_3.addWidget(self.openSavePath)

        self.switchTopics = PrimaryToolButton(self.ElevatedCardWidget_3)
        self.switchTopics.setObjectName(u"switchTopics")

        self.horizontalLayout_3.addWidget(self.switchTopics)

        self.verticalLayout.addWidget(self.ElevatedCardWidget_3)

        self.ElevatedCardWidget_4 = ElevatedCardWidget(self.CardWidget_2)
        self.ElevatedCardWidget_4.setObjectName(u"ElevatedCardWidget_4")
        self.gridLayout_2 = QGridLayout(self.ElevatedCardWidget_4)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.messageLabel = StrongBodyLabel(self.ElevatedCardWidget_4)
        self.messageLabel.setObjectName(u"messageLabel")
        sizePolicy1 = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Preferred)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.messageLabel.sizePolicy().hasHeightForWidth())
        self.messageLabel.setSizePolicy(sizePolicy1)

        self.gridLayout_2.addWidget(self.messageLabel, 0, 0, 1, 1)

        self.clientListLebel = StrongBodyLabel(self.ElevatedCardWidget_4)
        self.clientListLebel.setObjectName(u"clientListLebel")
        sizePolicy1.setHeightForWidth(self.clientListLebel.sizePolicy().hasHeightForWidth())
        self.clientListLebel.setSizePolicy(sizePolicy1)

        self.gridLayout_2.addWidget(self.clientListLebel, 0, 2, 1, 1)

        self.messageEdit = TextEdit(self.ElevatedCardWidget_4)
        self.messageEdit.setObjectName(u"messageEdit")

        self.gridLayout_2.addWidget(self.messageEdit, 1, 0, 4, 1)

        self.clientListScrollArea = ScrollArea(self.ElevatedCardWidget_4)
        self.clientListScrollArea.setObjectName(u"clientListScrollArea")
        self.clientListScrollArea.setWidgetResizable(True)
        self.VboxWidget = QWidget()
        self.VboxWidget.setObjectName(u"VboxWidget")
        self.VboxWidget.setGeometry(QRect(0, 0, 311, 98))
        self.clientListScrollArea.setWidget(self.VboxWidget)

        self.gridLayout_2.addWidget(self.clientListScrollArea, 1, 2, 1, 1)

        self.widget = QWidget(self.ElevatedCardWidget_4)
        self.widget.setObjectName(u"widget")
        self.horizontalLayout_2 = QHBoxLayout(self.widget)
        self.horizontalLayout_2.setSpacing(6)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.selectAll = CheckBox(self.widget)
        self.selectAll.setObjectName(u"selectAll")
        sizePolicy2 = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.selectAll.sizePolicy().hasHeightForWidth())
        self.selectAll.setSizePolicy(sizePolicy2)

        self.horizontalLayout_2.addWidget(self.selectAll)

        self.disconnectSelect = PrimaryPushButton(self.widget)
        self.disconnectSelect.setObjectName(u"disconnectSelect")

        self.horizontalLayout_2.addWidget(self.disconnectSelect)

        self.gridLayout_2.addWidget(self.widget, 3, 2, 1, 1)

        self.verticalLayout.addWidget(self.ElevatedCardWidget_4)

        self.ElevatedCardWidget_5 = ElevatedCardWidget(self.CardWidget_2)
        self.ElevatedCardWidget_5.setObjectName(u"ElevatedCardWidget_5")
        self.gridLayout_4 = QGridLayout(self.ElevatedCardWidget_5)
        self.gridLayout_4.setObjectName(u"gridLayout_4")
        self.gridLayout_4.setContentsMargins(9, 0, 9, -1)
        self.sendMessageBtn = PrimaryPushButton(self.ElevatedCardWidget_5)
        self.sendMessageBtn.setObjectName(u"sendMessageBtn")

        self.gridLayout_4.addWidget(self.sendMessageBtn, 1, 0, 1, 1)

        self.sendEdit = TextEdit(self.ElevatedCardWidget_5)
        self.sendEdit.setObjectName(u"sendEdit")

        self.gridLayout_4.addWidget(self.sendEdit, 0, 0, 1, 2)

        self.sendFileBtn = PrimaryPushButton(self.ElevatedCardWidget_5)
        self.sendFileBtn.setObjectName(u"sendFileBtn")

        self.gridLayout_4.addWidget(self.sendFileBtn, 1, 1, 1, 1)

        self.verticalLayout.addWidget(self.ElevatedCardWidget_5)

        self.ElevatedCardWidget = ElevatedCardWidget(self.CardWidget_2)
        self.ElevatedCardWidget.setObjectName(u"ElevatedCardWidget")
        self.horizontalLayout_7 = QHBoxLayout(self.ElevatedCardWidget)
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.state_listenState = CaptionLabel(self.ElevatedCardWidget)
        self.state_listenState.setObjectName(u"state_listenState")

        self.horizontalLayout_7.addWidget(self.state_listenState)

        self.horizontalSpacer_2 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_7.addItem(self.horizontalSpacer_2)

        self.state_listenAddress = CaptionLabel(self.ElevatedCardWidget)
        self.state_listenAddress.setObjectName(u"state_listenAddress")

        self.horizontalLayout_7.addWidget(self.state_listenAddress)

        self.horizontalSpacer_3 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_7.addItem(self.horizontalSpacer_3)

        self.state_listenPort = CaptionLabel(self.ElevatedCardWidget)
        self.state_listenPort.setObjectName(u"state_listenPort")

        self.horizontalLayout_7.addWidget(self.state_listenPort)

        self.horizontalSpacer_4 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_7.addItem(self.horizontalSpacer_4)

        self.state_cilentNum_text = CaptionLabel(self.ElevatedCardWidget)
        self.state_cilentNum_text.setObjectName(u"state_cilentNum_text")

        self.horizontalLayout_7.addWidget(self.state_cilentNum_text)

        self.state_cilentNum = CaptionLabel(self.ElevatedCardWidget)
        self.state_cilentNum.setObjectName(u"state_cilentNum")

        self.horizontalLayout_7.addWidget(self.state_cilentNum)

        self.verticalLayout.addWidget(self.ElevatedCardWidget)

        self.gridLayout_3.addWidget(self.CardWidget_2, 0, 0, 1, 1)

        self.retranslateUi(Widget)

        QMetaObject.connectSlotsByName(Widget)

    # setupUi

    def retranslateUi(self, Widget):
        Widget.setWindowTitle(QCoreApplication.translate("Widget", u"Widget", None))
        self.addressLabel.setText(QCoreApplication.translate("Widget", u"\u76d1\u542c\u5730\u5740", None))
        self.addressEdit.setText(QCoreApplication.translate("Widget", u"127.0.0.1", None))
        self.WLANaddress.setText(QCoreApplication.translate("Widget", u"\u65e0\u7ebfWLANIPv4\u5730\u5740", None))
        self.localAddressBtn.setText(QCoreApplication.translate("Widget", u"\u672c\u673a\u5730\u5740", None))
        self.portLabel.setText(QCoreApplication.translate("Widget", u"\u76d1\u542c\u7aef\u53e3", None))
        self.portEdit.setText(QCoreApplication.translate("Widget", u"12345", None))
        self.startListen.setText(QCoreApplication.translate("Widget", u"\u5f00\u59cb\u76d1\u542c", None))
        self.stopListen.setText(QCoreApplication.translate("Widget", u"\u505c\u6b62\u76d1\u542c", None))
        self.disconnectAll.setText(QCoreApplication.translate("Widget", u"\u65ad\u5f00\u6240\u6709\u8fde\u63a5", None))
        self.clearMessage.setText(QCoreApplication.translate("Widget", u"\u6e05\u7a7a\u6d88\u606f\u8bb0\u5f55", None))
        self.messageLabel.setText(QCoreApplication.translate("Widget", u"\u6d88\u606f\u8bb0\u5f55", None))
        self.clientListLebel.setText(QCoreApplication.translate("Widget", u"\u5ba2\u6237\u7aef\u5217\u8868", None))
        self.selectAll.setText(QCoreApplication.translate("Widget", u"\u5168\u9009", None))
        self.disconnectSelect.setText(
            QCoreApplication.translate("Widget", u"\u65ad\u5f00\u9009\u4e2d\u5ba2\u6237\u7aef", None))
        self.sendMessageBtn.setText(
            QCoreApplication.translate("Widget", u"\u5411\u9009\u4e2d\u5ba2\u6237\u7aef\u53d1\u9001\u6d88\u606f", None))
        self.sendFileBtn.setText(
            QCoreApplication.translate("Widget", u"\u5411\u9009\u4e2d\u5ba2\u6237\u7aef\u53d1\u9001\u6587\u4ef6", None))
        self.state_listenState.setText(
            QCoreApplication.translate("Widget", u"\u76d1\u542c\u72b6\u6001\uff1a\u505c\u6b62\u76d1\u542c", None))
        self.state_listenAddress.setText(QCoreApplication.translate("Widget", u"\u76d1\u542c\u5730\u5740\uff1a", None))
        self.state_listenPort.setText(QCoreApplication.translate("Widget", u"\u76d1\u542c\u7aef\u53e3\uff1a", None))
        self.state_cilentNum_text.setText(
            QCoreApplication.translate("Widget", u"\u5ba2\u6237\u7aef\u6570\u91cf\uff1a", None))
        self.state_cilentNum.setText(QCoreApplication.translate("Widget", u"0", None))
    # retranslateUi
