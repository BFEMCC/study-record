#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QLineEdit>
#include <QTextEdit>
#include <QStringConverter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //点击选择文件按钮弹出文件对话框
    connect(ui->pushButton,&QPushButton::clicked,this,[=](){

        //读取内容放到lineEdit中
        QString path = QFileDialog::getOpenFileName(this,"选择文件","D:\\TX4\\Desktop");
        ui->lineEdit->setText(path);

        //读取文档内容放到textEdit中
        QFile readfile(path);//参数就是读取的文件路径
        readfile.open(QFile::ReadOnly);//设置打开方式
        QByteArray arry = readfile.readAll();//可以自动转换成QString，但只支持UTF8/UTF8-bom，ANSI和UTF16 LE/BE不支持，需要额外转换


        QStringDecoder gbkToUtf16 = QStringDecoder(QStringDecoder::Encoding::System);// 创建一个 GBK 到 UTF-16 的解码器
        QStringEncoder utf16ToUtf8 = QStringEncoder(QStringEncoder::Utf8);// 创建一个 UTF-16 到 UTF-8 的编码器

        // 将 GBK 编码的字符串转换为 UTF-8 编码
        QString utf16String = gbkToUtf16(arry);
        QByteArray utf8EncodedString = utf16ToUtf8(utf16String);

        ui->textEdit->setText(utf8EncodedString);
    });



}

Widget::~Widget()
{
    delete ui;
}




















































