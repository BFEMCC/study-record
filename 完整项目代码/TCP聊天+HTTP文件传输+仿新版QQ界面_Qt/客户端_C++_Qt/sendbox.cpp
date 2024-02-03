#include "sendbox.h"
#include "ui_sendbox.h"

SendBox::SendBox(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::SendBox)
{
    ui->setupUi(this);
    ui->label_2->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->label_2->setWordWrap(true);
    ui->label->setScaledContents(true);
    setStyleSheet("#label_2 { padding: 12px; }");
    ui->label->setPixmap(QPixmap(":/IMAGE/default.png"));
    setStyleSheet(QString("#label_2{background-color: %1;}").arg(QColor(QColor(0, 153, 255)).name()));
    setStyleSheet(QString("#label_2{border-radius: 10px;}"));
    setStyleSheet(QString("#label_2 {color: %1;}").arg(QColor(Qt::white).name()));
}

SendBox::~SendBox()
{
    delete ui;
}

void SendBox::setStyleSheet(const QString &style)
{
    QWidget::setStyleSheet(styleSheet() + style);
}

void SendBox::setText(const QString &text)
{
    ui->label_2->setText(text);
}
void SendBox::setImageMsg(const QPixmap &img)
{
    ui->label_2->setWordWrap(false);
    ui->label_2->setPixmap(img);
    this->isFile = true;
}

void SendBox::setFilePath(const QString &filePath)
{
    this->filePath = filePath;
}

void SendBox::mouseDoubleClickEvent(QMouseEvent *event)
{
    QWidget::mouseDoubleClickEvent(event);
    if (this->isFile)
    {
        QProcess process;
        filePath.replace("/", "\\"); // 只能识别 "\"
        process.startDetached(QString("explorer.exe /select,\"%1\"").arg(this->filePath));
    }
}
