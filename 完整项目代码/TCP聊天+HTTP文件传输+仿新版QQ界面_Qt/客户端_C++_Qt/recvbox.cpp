#include "recvbox.h"
#include "ui_recvbox.h"
#include "globals.h"

RecvBox::RecvBox(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::RecvBox)
{
    ui->setupUi(this);
    ui->label_2->setTextInteractionFlags(Qt::TextSelectableByMouse); // 支持复制
    ui->label_2->setWordWrap(true);                                  // 非ascll字符自动换行
    ui->label->setScaledContents(true);                              // 图片适应控件大小
    setStyleSheet("#label_2 { padding: 12px; }");
    ui->label->setPixmap(QPixmap(":/IMAGE/eromanga.png"));
    setStyleSheet(QString("#label_2{background-color: %1;}").arg(QColor(Qt::white).name()));
    setStyleSheet(QString("#label_2{border-radius: 10px;}"));
    setStyleSheet(QString("#label_2 {color: %1;}").arg(QColor(Qt::black).name()));
}

RecvBox::~RecvBox()
{
    delete ui;
}

void RecvBox::setStyleSheet(const QString &style)
{
    QWidget::setStyleSheet(styleSheet() + style);
}

void RecvBox::setText(const QString &text)
{
    ui->label_2->setText(text);
}

void RecvBox::setImageMsg(const QPixmap &img)
{
    ui->label_2->setWordWrap(false);
    ui->label_2->setPixmap(img);
    this->isFile = true;
}

void RecvBox::setFilePath(const QString &filePath)
{
    this->filePath = filePath;
}

void RecvBox::setUrl(const QString &url)
{
    this->url = url;
}

void RecvBox::mouseDoubleClickEvent(QMouseEvent *event)
{
    QWidget::mouseDoubleClickEvent(event);
    // 第一次双击下载文件
    // 第二次双击打开文件
    if (this->isFile)
    {
        if (isDownload)
        {
            QProcess process;
            this->filePath.replace("/", "\\"); // windows文件路径使用 "\",要替换一下
            process.startDetached(QString("explorer.exe /select,\"%1\"").arg(this->filePath));
        }
        else
        {
            // 启动py脚本下载文件
            starDoload(QFileInfo(this->filePath).absolutePath(), url);
            isDownload = true;
        }
    }
}
