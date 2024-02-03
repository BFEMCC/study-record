#include "ProgressWidget.h"
#include "ui_ProgressWidget.h"

#include <QThread>

ProgressWidget::ProgressWidget(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::FileSend)
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    ui->progressBar->setMaximum(100);
    this->setModal(false);
    this->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose); // 设置在关闭时自动删除
}

ProgressWidget::~ProgressWidget()
{
    delete ui;
}

void ProgressWidget::setTips(const QString &downloadOrSend)
{
    ui->label_2->setText(downloadOrSend);
}

void ProgressWidget::updateProgress(int progress)
{
    ui->progressBar->setValue(progress);
}

void ProgressWidget::setFilePath(QString path)
{
    ui->lineEdit->setText(path);
}
