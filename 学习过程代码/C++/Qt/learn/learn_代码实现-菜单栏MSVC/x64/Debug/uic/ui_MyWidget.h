/********************************************************************************
** Form generated from reading UI file 'MyWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWIDGET_H
#define UI_MYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyWidgetClass
{
public:
    QWidget *centralWidget;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyWidgetClass)
    {
        if (MyWidgetClass->objectName().isEmpty())
            MyWidgetClass->setObjectName(QString::fromUtf8("MyWidgetClass"));
        MyWidgetClass->resize(600, 400);
        centralWidget = new QWidget(MyWidgetClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(170, 100, 118, 23));
        progressBar->setValue(24);
        MyWidgetClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MyWidgetClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        MyWidgetClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyWidgetClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MyWidgetClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MyWidgetClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MyWidgetClass->setStatusBar(statusBar);

        retranslateUi(MyWidgetClass);

        QMetaObject::connectSlotsByName(MyWidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyWidgetClass)
    {
        MyWidgetClass->setWindowTitle(QCoreApplication::translate("MyWidgetClass", "MyWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyWidgetClass: public Ui_MyWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWIDGET_H
