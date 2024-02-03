#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdialog.h"
#include "qcolordialog.h"
#include "qmessagebox.h"
#include "qdebug.h"
#include "qfiledialog.h"
#include "qfontdialog.h"
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->actionnew->setIcon(QIcon(":/image/image/a.ico"));
    ui->actionopen->setIcon(QIcon(":/image/image/q.png"));

    /*
     *添加资源文件步骤：
     *1、讲资源全都放在一个文件夹里，然后放入项目目录中
     *2、 右键项目，点击添加新文件，选择QT->QT Resource File,取一个名
     *3、
    */

    auto dlg1=[=]()
    {
        QDialog dlg(this);
        dlg.resize(200,100);
        dlg.exec();//模态方式创建对话框//阻塞，可以在栈上，会自动释放
    };

    auto dlg2=[=]()
    {
//        QDialog dlg(this);
//        dlg.resize(100,200);
//        dlg.show();//非模态，不阻塞，不能在栈上//函数运行完会直接销毁，窗口一闪而过
        QDialog* dlg=new QDialog(this);
        dlg->resize(200,100);
        dlg->setAttribute(Qt::WA_DeleteOnClose);//当关闭时直接释放//或者手动释放也可以
        dlg->show();
    };

    auto dlg3=[=]()
    {
      QColorDialog dlg(qRgb(255,0,0)/*默认颜色*/);//调色板//或QColor(255,0,0)
      QColor color=dlg.getColor();
      //QColor color=QColorDialog::getColor(QColor(255,0,0));

      qDebug()<<"r = "<<color.red()<<"g = "<<color.green()<<"b = "<<color.blue();
    };

    auto dlg4=[=]()
    {
        QMessageBox::critical(this,"错误","error");//错误对话框
    };

    auto dlg5=[=]()
    {
        QMessageBox::information(this,"提示","information");//提示消息对话框
    };

    auto dlg6=[=]()
    {
        //提问对话框
        //参数1：父窗口
        //参数2：标题
        //参数3：显示的文本内容
        //参数4：按钮类型
        //参数5：默认的关联回车的按钮是哪个
        //返回值：选择的是哪个按钮
       if(QMessageBox::Save==QMessageBox::question(this,"确认吗？","yes or no?",QMessageBox::Save|QMessageBox::Cancel,QMessageBox::Cancel))
       {
           qDebug()<<"选择的是保存Save";
       }
       else
       {
            qDebug()<<"选择的是取消Cancel";
       }
    };

    auto dlg7=[=]()
    {
        QMessageBox::warning(this,"警告","warning");
    };

    auto open=[=]()
    {
        QFileDialog::getOpenFileName(this,"打开","D:/TX4/Desktop","(*.txt");
        //返回值是路径
    };

    auto font=[]()
    {
        bool flag;
       QFont fo= QFontDialog::getFont(&flag,QFont("微软雅黑",18));
       qDebug()<<"字体："<<fo.family().toUtf8().data()<<"字号："<<fo.pointSize()<<"是否加粗："<<fo.bold()<<"是否斜体："<<fo.italic();
    };

    connect(ui->actionnew,&QAction::triggered,this,dlg2);

    connect(ui->actionopen,&QAction::triggered,this,open);

    connect(ui->actionexit,&QAction::triggered,this,exit);

}

MainWindow::~MainWindow()
{
    delete ui;
}

