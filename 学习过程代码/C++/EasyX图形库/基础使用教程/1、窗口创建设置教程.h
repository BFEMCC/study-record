#pragma once
#include<easyx.h>
void one()
{
	//创建图形窗口函数	initraph(int x,int y,bool),参数：整形,整形，0或1或无参数，对应长，宽，是否显示控制台，第三个参数若无参数默认不显示控制台
		//图形化窗口以左上角为原点，向右为x轴正方向，向下为y轴正方向
	initgraph(600, 400, 1);

	//窗口颜色设置，函数：	setbkcolor();	有两种设置方式：颜色宏，RGB设置。颜色宏指各种颜色的英语大写单词，如RED，YELLOW等
	setbkcolor(WHITE);

	//刷新窗口，函数	cleardevice();
	cleardevice();

	//基本绘图函数
	
	//设置画出图线的的颜色，函数：setlinecolor();，要先设置
	setlinecolor(RED);

	//画直线，函数：	line(int x1,int x2,int x3,int x4); ，从坐标(x1,x2)画一条直线到坐标(x3,x4)
	line(0, 0, 600, 400);

	//画圆，函数：	circle(int x,int y，int r);，以(x1,x2)为圆心，int r为半径画圆
	circle(100, 100, 50);

	//画矩形，函数：	rectangle(int x1,int y1,int x2,int y2);，左上角坐标(x1,y1),右下角坐标(x2,y2)
	rectangle(300, 300, 200, 200);

	//设置填充颜色，函数：setfliicolor();，要先设置
	//画填充圆：带边框：fillcircle();参数和画圆一样，不带边框：solidcircle();参数和画圆一样
	//画填充矩形：带边框：fillrectangle();，不带边框solidrectangle();两个参数都同画矩形
}