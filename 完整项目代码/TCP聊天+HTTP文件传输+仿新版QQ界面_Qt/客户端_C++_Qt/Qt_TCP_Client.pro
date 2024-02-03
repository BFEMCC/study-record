QT       += core gui
QT       += network
QT       += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++23

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AnimatedButton.cpp \
    DynamicLineEdit.cpp \
    ProgressWidget.cpp \
    filesrever.cpp \
    globals.cpp \
    login.cpp \
    main.cpp \
    mainwidget.cpp \
    recvbox.cpp \
    sendbox.cpp \
    sendfilethread.cpp

HEADERS += \
    AnimatedButton.h \
    DynamicLineEdit.h \
    ProgressWidget.h \
    filesrever.h \
    globals.h \
    login.h \
    mainwidget.h \
    recvbox.h \
    sendbox.h \
    sendfilethread.h

FORMS += \
    ProgressWidget.ui \
    login.ui \
    mainwidget.ui \
    recvbox.ui \
    sendbox.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qrc.qrc

RC_ICONS = ico\client.ico

DISTFILES +=
