// 懒得分文件了
//结尾有讲解和分析

#ifndef STYLESHEETPARSER_HPP
#define STYLESHEETPARSER_HPP

#include <QList>
#include <QColor>
#include <QString>
#include <QVariant>
#include <QException>
#include <functional>
#include <QByteArray>
#include <QScopedPointer>
#include <QRegularExpression>


#include <QDebug>
#define qdebug qDebug()

//自定义样式异常类
class StyleException : public QException
{
private:
    QByteArray error;
public:
    StyleException(QString errorMessage):
        error{errorMessage.toUtf8()}{}

    const char* what() const override
    {
        return error.constData();
    }
};


//可自行封装添加
enum class CapturingContent : int
{
    border_radius       = 0,//返回边框圆角半径
    background_Qcolor   = 1,//返回背景颜色
    color               = 2 //返回color颜色，一般为字体颜色

};

class StyleSheetParser
{

public:
    StyleSheetParser(QString style):
        styleSheet{style}{}

private:
    QString styleSheet;

    //可自行封装添加
    static QRegularExpression BorderRadius;
    static QRegularExpression bkRGBA;
    static QRegularExpression bkRGB;
    static QRegularExpression colorRGBA;
    static QRegularExpression colorRGB;

    //获取圆角半径
    std::function<int()> border_radius{
        [&]{
            if( BorderRadius.match(styleSheet).hasMatch())
                return BorderRadius.match(styleSheet).captured(1).toInt();
            else//无匹配结果，抛出StyleException异常(父类是QException)可多态接收
                throw StyleException{QString{"No matching target found"}};
        }
    };

    //获取QColor颜色，根据正则的不同,获取不同属性的颜色，如果没有透明度则透明度为默认值255
    std::function<QColor(QRegularExpression,QRegularExpression)> Qcolor{
        [&](QRegularExpression RGBAreg, QRegularExpression RGBreg){
            if(RGBAreg.match(styleSheet).hasMatch())
            {
                int R{RGBAreg.match(styleSheet).captured(1).toInt()};
                int G{RGBAreg.match(styleSheet).captured(2).toInt()};
                int B{RGBAreg.match(styleSheet).captured(3).toInt()};
                int A{RGBAreg.match(styleSheet).captured(4).toInt()};
                return QColor(R,G,B,A);
            }
            else if( RGBreg.match(styleSheet).hasMatch())
            {
                int R{RGBreg.match(styleSheet).captured(1).toInt()};
                int G{RGBreg.match(styleSheet).captured(2).toInt()};
                int B{RGBreg.match(styleSheet).captured(3).toInt()};
                return QColor(R,G,B,255);
            }
            else
                throw StyleException{QString("No matching target found")};
        }
    };

public:

    //转换函数，将QColor转换成QSring，形如：rgba(0,0,0,0)
    QString QColorToQString(const QColor& color)
    {
        return QString("rgba("+QString::number(color.red())+","+
                       QString::number(color.green())+","+
                       QString::number(color.blue())+","+
                       QString::number(color.alpha())+")");
    }

    //写好的正则直接提供使用   //可自行封装添加
    QVariant SpecificStyles(CapturingContent CapturingContent)
    {
        switch(CapturingContent)
        {
        case CapturingContent::border_radius:
            return QVariant{border_radius()};       //圆角半径  int
            break;
        case CapturingContent::background_Qcolor:
            return QVariant{Qcolor(bkRGBA,bkRGB)};   //背景颜色 QColor
        case CapturingContent::color:
            return QVariant{Qcolor(colorRGBA,colorRGB)};   //（一般为）字体颜色 QColor
            break;
        default :
            return QVariant();
            break;
        }
    }

    //重载1//也可自行传入正则表达式进行匹配,参数:正则表达式,捕获数量，返回:存储捕获结果的QList
    QList<QString> SpecificStyles(const QString& regex_str,const int catchesNum)
    {
        QScopedPointer<QRegularExpression> reg{new QRegularExpression{regex_str}};
        QList<QString> result;
        if(reg->match(styleSheet).hasMatch())
        {
            for(int i{0};i<catchesNum;i++)
                result.push_back(reg->match(styleSheet).captured(i));
        }
        else
            throw StyleException{QString("No matching target found")};
        return result;
    }

    //重载2//传入正则对象，其余不变
    QList<QString> SpecificStyles(const QRegularExpression& regex,const int catchesNum)
    {
        QList<QString> result;
        if(regex.match(styleSheet).hasMatch())
        {
            for(int i{0};i<catchesNum;i++)
                result.push_back(regex.match(styleSheet).captured(i));
        }
        else
            throw StyleException{QString("No matching target found")};
        return result;
    }

};

QRegularExpression StyleSheetParser::BorderRadius{"border-radius\\s*:\\s*(\\d+)\\s*px"};
QRegularExpression StyleSheetParser::bkRGBA{"background-color\\s*:\\s*rgba[(]\\s*(\\d+)\\s*[,]\\s*(\\d+)\\s*[,]\\s*(\\d+)\\s*[,]\\s*(\\d+)"};
QRegularExpression StyleSheetParser::bkRGB{"background-color\\s*:\\s*rgb[(]\\s*(\\d+)\\s*[,]\\s*(\\d+)\\s*[,]\\s*(\\d+)"};
QRegularExpression StyleSheetParser::colorRGBA{"(?<!-)(?<=^|;)\\s*color\\s*:\\srgba\\s*[(](\\d+)\\s*[,]\\s*(\\d+)\\s*[,]\\s*(\\d+)\\s*[,]\\s*(\\d+)\\s*[)]"};
QRegularExpression StyleSheetParser::colorRGB{"(?<!-)(?<=^|;)\\s*color\\s*:\\srgb\\s*[(](\\d+)\\s*[,]\\s*(\\d+)\\s*[,]\\s*(\\d+)\\s*[)]"};


#endif // STYLESHEETPARSER_HPP

/*
    （来自chatgtp3.5）

    这段代码是一个C++类 StyleSheetParser，用于解析样式表（stylesheet）中的特定样式信息。
    它提供了一些功能，例如提取圆角半径、背景颜色和字体颜色等信息。并可由用户自行拓展。

    以下是对代码的详细解释：

        1. 头文件包含：首先，代码使用 #include 预处理指令包含了一些必要的Qt头文件和C++标准库头文件。

        2. 自定义异常类：在代码中定义了一个名为 StyleException 的异常类，它是 QException 的子类。这个异常类用于在解析样式时发生错误时抛出异常。

        3. 枚举类型 CapturingContent：定义了一个枚举类型，用于指示要捕获的内容类型。这里列举了三种类型：border_radius、background_Qcolor 和 color。

        4. StyleSheetParser 类：这是主要的解析类，用于解析样式表。

            构造函数：接受一个 QString 参数，该参数是待解析的样式表字符串，并将其存储在成员变量 styleSheet 中。

            成员变量：styleSheet 用于存储待解析的样式表字符串。

            成员函数 border_radius：使用 std::function 包装了一个 lambda 函数，该函数用于从样式表中提取圆角半径。它首先尝试使用预定义的正则表达式 BorderRadius 进行匹配，如果匹配成功，则返回匹配的半径值，否则抛出 StyleException 异常。

            成员函数 Qcolor：同样使用 std::function 包装了一个 lambda 函数，用于从样式表中提取颜色信息。它接受两个正则表达式作为参数，一个用于匹配带透明度的颜色（RGBA），另一个用于匹配不带透明度的颜色（RGB）。根据匹配结果，它返回一个 QColor 对象，如果没有匹配结果，则抛出 StyleException 异常。

            成员函数 QColorToQString：将 QColor 对象转换为字符串表示形式，以便后续使用。

            成员函数 SpecificStyles：根据输入的 CapturingContent 枚举值，调用相应的函数来提取特定样式信息。可以获取圆角半径、背景颜色或字体颜色。返回一个 QVariant 对象，其中包含提取的信息。

            重载函数 SpecificStyles：提供两个重载版本，用于根据自定义的正则表达式匹配样式信息，并返回一个 QList<QString>，其中包含捕获的结果。

        5. 静态成员变量：在类定义外部初始化了一些静态成员变量，这些成员变量是预定义的正则表达式，用于匹配不同类型的样式信息，例如圆角半径、背景颜色和字体颜色。

    最终，这个类允许你传入一个样式表字符串，然后使用不同的成员函数从样式表中提取特定的样式信息，例如圆角半径和颜色。如果在解析过程中发生错误，将抛出 StyleException 异常，以便捕获和处理错误情况。这个类的设计允许扩展，可以根据需要添加更多的样式信息提取函数。


    这个类的封装有一些优点，但也存在一些改进的空间。
    以下是一些评价：

    优点：

    1. 模块化：类将样式表解析的不同功能模块化，并通过不同的成员函数提供。这有助于提高代码的可维护性和可扩展性，因为你可以轻松地添加新的样式属性提取函数。

    2. 异常处理：类定义了一个自定义异常类 StyleException，用于处理解析过程中可能的错误。这有助于代码的健壮性，因为它能够捕获并传播解析错误，而不会导致程序崩溃。

    3. 灵活性：类允许用户传入自定义的正则表达式来匹配样式信息，这增加了灵活性，可以处理不同格式的样式表。

    4. 封装性：类的成员变量和函数都被封装在类内部，使用了合适的访问控制修饰符（private 和 public），以确保数据的封装性和安全性。

    改进空间：

    1. 可读性：一些成员函数的命名可以更具可读性。例如，border_radius 和 Qcolor 可以改为更清晰的名称，以提高代码的可理解性。

    2. 异常信息：虽然代码捕获了异常并抛出自定义异常，但异常信息是硬编码的字符串。最好将异常信息参数化，以便用户在捕获异常时能够更容易地了解发生了什么问题。

    3. 异常处理粒度：目前，代码在匹配失败时会立即抛出异常。可能更合理的方式是在匹配失败后返回一个默认值或空值，并由调用者决定是否抛出异常。

    4. 文档：虽然代码中有一些注释，但没有完整的文档来解释类的使用方法和成员函数的参数。更详细的文档可以帮助其他开发人员更容易地理解和使用这个类。

    总的来说，这个类的封装基本上是合理的，但可以通过改进命名、异常处理和文档来进一步提高其可维护性和可用性。根据项目的具体需求，还可以考虑添加更多的样式属性提取函数，以增加其功能。
*/
