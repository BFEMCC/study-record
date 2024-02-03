#ifndef SENDBOX_H
#define SENDBOX_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QString>
#include <QColor>
#include <QPalette>
#include <QPainterPath>
#include <QRegion>
#include <QPaintEngine>
#include <QMouseEvent>
#include <QProcess>

namespace Ui
{
    class SendBox;
}

class SendBox : public QWidget
{
    Q_OBJECT

public:
    explicit SendBox(QWidget *parent = nullptr);
    ~SendBox();

public:
    void setStyleSheet(const QString &style);
    void setText(const QString &text);
    void setImageMsg(const QPixmap &img);
    void setFilePath(const QString &filePath);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    Ui::SendBox *ui;

    bool isFile = false;
    QString filePath;
};

#endif // SENDBOX_H
