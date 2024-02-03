#pragma once

#include <graphics.h>//包含已经被淘汰的函数
#include <easyx.h>//只包含最新的函数
void four()
{
	//鼠标交互
	//ExMessage 类型变量存储鼠标消息
	//获取鼠标消息，用Windows提供的api
		//peekmessage(&ExMessage变量名)
	//讨论鼠标消息
		//msg.message	区分鼠标消息
		//msg.x	msg.y	鼠标当前坐标

	ExMessage msg;
	//案例：左键画圆，右键画方
	while (1)
	{
		setlinecolor(RED);
		while (peekmessage(&msg))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				circle(msg.x, msg.y, 10);
				break;
			case WM_RBUTTONDOWN:
				rectangle(msg.x, msg.y, msg.x + 10, msg.y + 10);
				break;
			}
		}
	}
}
