#ifndef RECVBOX_H
#define RECVBOX_H

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
#include <QFileInfo>

namespace Ui
{
    class RecvBox;
}

class RecvBox : public QWidget
{
    Q_OBJECT

public:
    explicit RecvBox(QWidget *parent = nullptr);
    ~RecvBox();

public:
    void setStyleSheet(const QString &style);
    void setText(const QString &text);
    void setImageMsg(const QPixmap &img);
    void setFilePath(const QString &filePath);
    void setUrl(const QString &url);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    Ui::RecvBox *ui;

    bool isFile = false;
    bool isDownload = false;
    QString filePath;
    QString url;
};

#endif // RECVBOX_H
