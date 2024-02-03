#ifndef PROGRESSWIDGET_H
#define PROGRESSWIDGET_H
// 命名失误,修改太麻烦
#define Ui_ProgressWidget FileSend

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QMap>
#include <QHostInfo>
#include <QIntValidator>
#include <QNetworkInterface>
#include <QCheckBox>
#include <QprogressBar>

namespace Ui
{
    class Ui_ProgressWidget;
}
class MainWidget;

class ProgressWidget : public QDialog
{
    Q_OBJECT

    friend class MainWidget;

public:
    ProgressWidget(QWidget *parent = nullptr);
    ~ProgressWidget();

    void setTips(const QString &downloadOrSend = "下载进度");

public slots:
    void updateProgress(int progress);
    void setFilePath(QString path);

private:
    Ui::Ui_ProgressWidget *ui;
};

#endif // PROGRESSWIDGET_H
