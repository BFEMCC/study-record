#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->radioButton_black->setChecked(true);
   //connect(ui->radioButton_red,SIGNAL(clicked()),this,SLOT(setFontColot()));//Qt4版本信号和槽的连接

    connect(ui->radioButton_red,&ui->radioButton_red->clicked,this,&this->setFontColot);//Qt5以上版本的信号和槽的连接

    connect(ui->radioButton_black,SIGNAL(clicked()),this,SLOT(setFontColot()));
    connect(ui->radioButton_blue,SIGNAL(clicked()),this,SLOT(setFontColot()));
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_xiahuaxian_clicked(bool checked)
{
   QFont font = ui->plainTextEdit->font();
   font.setUnderline(checked);
   ui->plainTextEdit->setFont(font);
}


void Dialog::on_xieti_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setItalic(checked);
    ui->plainTextEdit->setFont(font);
}


void Dialog::on_jiacu_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setBold(checked);
    ui->plainTextEdit->setFont(font);
}

void Dialog::setFontColot()
{
    QPalette plet=ui->plainTextEdit->palette();
    if(ui->radioButton_red->isChecked())
        plet.setColor(QPalette::Text,qRgb(255,0,0));
    if(ui->radioButton_black->isChecked())
        plet.setColor(QPalette::Text,qRgb(0,0,0));
    if(ui->radioButton_blue->isChecked())
        plet.setColor(QPalette::Text,Qt::blue);
    ui->plainTextEdit->setPalette(plet);
}
















