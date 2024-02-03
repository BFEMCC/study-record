#pragma once
#include <graphics.h>
#include <easyx.h>
#include"定时器.h"

void three()
{
	//按键交互
	//1、阻塞按键交互
	//2、非阻塞按键交互
	setfillcolor(RED);
	setlinecolor(BLACK);

	int x = 100, y = 100;
	int x1 = 150, y1 = 150;
	int vx = 5, vy = 5;
	BeginBatchDraw();
	while (1)
	{
		cleardevice();//刷新图形窗口，清除之前的图形
		fillcircle(x, y, 30);//画填充圆，受按键控制移动

		/*----------画填充圆，不受按键控制，一直移动，碰到边框会发生物理反弹----------*/
		fillcircle(x1, y1, 20);
		if (Timer(20, 0))
		{

			x1 += vx;
			y1 += vy;
			if (x1 + 20 == 800 || x1 - 20 == 0)
			{
				vx = -vx;
			}
			if (y1 + 20 == 650 || y1 - 20 == 0)
			{
				vy = -vy;
			}
		}
		/*-------------------------------------------------------------------------*/
				/*使用switch获取按键来控制移动是同步交互不流畅，无法做到两个键同时按，改用异步交互
				* 
				if(_kbhit())		//_kbbit()函数的作用是检查控制台窗口的按键是否被按下
									//若没有该判断，则程序每次运行到switch语句时都会暂停，直到按键按下退出switch循环，那么本该一直移动不受玩家按键影响的图形将会卡住
				{
					int userkey = _getch();
					//_getch()函数的作用是从控制台中获取输入的字符，该函数的返回值是获取到的字符值,_getch()函数是一个阻塞函数，直到有字符输入时才会返回,不需要回车确认输入
					switch (userkey)//顺序：上下左右
					{
					case 72:
						y -= 5;
						break;
					case 80:
						y += 5;
						break;
					case 75:
						x -= 5;
						break;
					case 77:
						x += 5;
						break;
					}
				}
				*/

		/*-------------------------------------------------------------------------*/
		if (Timer(20, 1))
		{
			if (GetAsyncKeyState(VK_UP))
			{
				y -= 5;
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				y += 5;
			}
			if (GetAsyncKeyState(VK_LEFT))
			{
				x -= 5;
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				x += 5;
			}
		}

		//Sleep(10);
		//Sleep();是阻塞函数，会影响到整个程序，一般用定时器来控制自动移动的图形
		FlushBatchDraw();

	}
	EndBatchDraw();
}
