#pragma once
#include <graphics.h>
#include <easyx.h>
#include"��ʱ��.h"

void three()
{
	//��������
	//1��������������
	//2����������������
	setfillcolor(RED);
	setlinecolor(BLACK);

	int x = 100, y = 100;
	int x1 = 150, y1 = 150;
	int vx = 5, vy = 5;
	BeginBatchDraw();
	while (1)
	{
		cleardevice();//ˢ��ͼ�δ��ڣ����֮ǰ��ͼ��
		fillcircle(x, y, 30);//�����Բ���ܰ��������ƶ�

		/*----------�����Բ�����ܰ������ƣ�һֱ�ƶ��������߿�ᷢ��������----------*/
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
				/*ʹ��switch��ȡ�����������ƶ���ͬ���������������޷�����������ͬʱ���������첽����
				* 
				if(_kbhit())		//_kbbit()�����������Ǽ�����̨���ڵİ����Ƿ񱻰���
									//��û�и��жϣ������ÿ�����е�switch���ʱ������ͣ��ֱ�����������˳�switchѭ������ô����һֱ�ƶ�������Ұ���Ӱ���ͼ�ν��Ῠס
				{
					int userkey = _getch();
					//_getch()�����������Ǵӿ���̨�л�ȡ������ַ����ú����ķ���ֵ�ǻ�ȡ�����ַ�ֵ,_getch()������һ������������ֱ�����ַ�����ʱ�Ż᷵��,����Ҫ�س�ȷ������
					switch (userkey)//˳����������
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
		//Sleep();��������������Ӱ�쵽��������һ���ö�ʱ���������Զ��ƶ���ͼ��
		FlushBatchDraw();

	}
	EndBatchDraw();
}
