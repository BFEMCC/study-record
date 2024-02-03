#include <iostream>
//必须包含下面两个头文件之一
#include <graphics.h>//包含已经被淘汰的函数
#include <easyx.h>//只包含最新的函数

#include<conio.h>  //_getch()头文件
#include<timeapi.h>//时间函数头文件



using namespace std;
#include"2、贴图教程.h"
#include"3、按键交互教程.h"
//#include"5、音频播放教程.h"



int main()
{
	initgraph(800, 650,1);
	setbkcolor(LIGHTRED);
	cleardevice();

	IMAGE leimu1;
	loadimage(&leimu1, "./贴图文件/222透明图.png", 400, 640);
	drawAlpha(&leimu1, 400, 0);
	putimage(0, 0, &leimu1);




	system("pause");
}
int main01()
{

	initgraph(800, 650);
	setbkcolor(LIGHTBLUE);
	cleardevice();

	//设置窗口标题
	HWND a = GetHWnd();//获取窗口句柄
	SetWindowText(a,"EasyX基础教程练习");//修改窗口标题

	setfillcolor(WHITE);//设置填充颜色为白色
	setlinecolor(LIGHTRED);//设置画线颜色为浅红色
	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 5);//设置线形为实线，端点为方形，宽度为5个像素
	fillcircle(400, 325, 50);//画填充圆，圆心坐标(400，325)，半径50


	setlinestyle(PS_DASH | PS_ENDCAP_SQUARE, 10);//设置线形为：------------，端点为方形，宽度为10像素
	setlinecolor(YELLOW);//设置画线颜色为黄色
	line(50, 50, 600, 450);
	line(50, 600, 450, 50);

	//字符处理，string转char
	string txt = "Hello world";
	const char* c = txt.data();

	settextcolor(WHITE);//设置文字颜色为白色
	settextstyle(50, 0, "方正楷体_GB2312");//设置文字高度为50，宽度0为自适应，字体为方正楷体
	setbkmode(TRANSPARENT);//设置文字背景透明
	outtextxy(100,320,c);//在窗口坐标(100，320)的位置输出字符串c


	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 5);//设置线形为实线，端点为方形，宽度为5像素
	setlinecolor(BLACK);//设置画线颜色为黑色
	setfillcolor(LIGHTRED);//设置填充颜色为淡红色
	fillrectangle(100, 25, 300, 105);

	//居中显示
	int width = textwidth(c);//获取字符串c的像素宽度
	int height = textheight(c);//获取字符串c的像素高度
	system("pause");
	return 0;
}
