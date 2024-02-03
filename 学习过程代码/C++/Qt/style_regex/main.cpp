#include "widget.h"
#include "StyleSheetParser.hpp"

#include <QApplication>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    try
    {
        StyleSheetParser sreg(w.styleSheet());
        qdebug<<sreg.QColorToQString(sreg.SpecificStyles(CapturingContent::color).value<QColor>());

    }
    catch(QException& error)
    {
        qdebug<<error.what();
    }

    w.show();
    return a.exec();
}
