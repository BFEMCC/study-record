#include "MyWidget.h"
#include <QToolBar>
#include <qpushbutton.h>
#include <qlabel>
#include <QDockWidget>
#include <qtextedit.h>
MyWidget::MyWidget(QWidget *parent): QMainWindow(parent)
{
	//ui.setupUi(this);//也可以使用UI布局，这句话用以显示UI文件
	this->resize(640, 480);


	//创建菜单栏
	QMenuBar* bar = this->menuBar();
	//将菜单栏放到窗口中
	this->setMenuBar(bar);
	//创建菜单，菜单栏最多只能有一个
	QMenu* fileMenu = bar->addMenu("文件");
	QMenu* editMenu = bar->addMenu("编辑");
	QMenu* vidoMenu = bar->addMenu("视图");
	//为菜单添加菜单项
	QAction* fileAction = fileMenu->addAction("新建");
	QAction* openAction = fileMenu->addAction("打开");
	//添加分隔线
	fileMenu->addSeparator();
	QAction* exitAction = fileMenu->addAction("退出");


	//创建工具栏，工具栏可以有多个
	QToolBar* toolBar = new QToolBar(this);
	this->addToolBar(Qt::LeftToolBarArea,toolBar);
	//设置停靠范围
	toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea | Qt::TopToolBarArea);
	//设置允许浮动
	toolBar->setFloatable(true);
	//设置可以移动
	toolBar->setMovable(true);
	//添加选项
	toolBar->addAction(fileAction);
	toolBar->addAction(openAction);
	toolBar->addSeparator();
	toolBar->addAction(exitAction);
	toolBar->addSeparator();
	//添加一个按钮控件
	QPushButton* toolButton = new QPushButton("选项",this);
	toolBar->addWidget(toolButton);

	//创建状态栏，最多有一个
	QStatusBar* stbar = statusBar();
	//设置到窗口中
	this->setStatusBar(stbar);
	//在状态栏中添加一些控件
	QLabel* lab1 = new QLabel("状态栏，左侧提示信息：", this);
	QLabel* lab2 = new QLabel("状态栏，右侧提示信息：", this);
	stbar->addWidget(lab1);
	stbar->addPermanentWidget(lab2);

	//铆接部件，浮动窗口，可以有多个
	QDockWidget* dockWidget = new QDockWidget("浮动选项卡", this);
	this->addDockWidget(Qt::RightDockWidgetArea, dockWidget);
	//设置吸附位置
	dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	//中心部件（核心部件），只能有一个
	QTextEdit* edit = new QTextEdit(this);
	this->setCentralWidget(edit);



}

MyWidget::~MyWidget()
{}
