#include <QApplication>
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    //    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
    QApplication a(argc, argv);
    MainWidget w;
    w.show();
    return a.exec();
}
