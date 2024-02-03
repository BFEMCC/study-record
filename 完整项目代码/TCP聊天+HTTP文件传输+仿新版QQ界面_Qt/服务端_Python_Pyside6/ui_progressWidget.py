# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'progressWidget.ui'
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
    QWidget)

from qfluentwidgets import (BodyLabel, CardWidget, ProgressBar, ProgressRing,
    SimpleCardWidget)

class Ui_Form(object):
    def setupUi(self, Form):
        if not Form.objectName():
            Form.setObjectName(u"Form")
        Form.resize(180, 118)
        self.gridLayout = QGridLayout(Form)
        self.gridLayout.setObjectName(u"gridLayout")
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.SimpleCardWidget = SimpleCardWidget(Form)
        self.SimpleCardWidget.setObjectName(u"SimpleCardWidget")
        self.horizontalLayout = QHBoxLayout(self.SimpleCardWidget)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.tips_label = BodyLabel(self.SimpleCardWidget)
        self.tips_label.setObjectName(u"tips_label")

        self.horizontalLayout.addWidget(self.tips_label)

        self.ProgressRing = ProgressRing(self.SimpleCardWidget)
        self.ProgressRing.setObjectName(u"ProgressRing")

        self.horizontalLayout.addWidget(self.ProgressRing)


        self.gridLayout.addWidget(self.SimpleCardWidget, 0, 0, 1, 1)


        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"Form", None))
        self.tips_label.setText(QCoreApplication.translate("Form", u"\u4e0b\u8f7d\u8fdb\u5ea6", None))
    # retranslateUi

