#pragma once

#include <graphics.h>//�����Ѿ�����̭�ĺ���
#include <easyx.h>//ֻ�������µĺ���
void four()
{
	//��꽻��
	//ExMessage ���ͱ����洢�����Ϣ
	//��ȡ�����Ϣ����Windows�ṩ��api
		//peekmessage(&ExMessage������)
	//���������Ϣ
		//msg.message	���������Ϣ
		//msg.x	msg.y	��굱ǰ����

	ExMessage msg;
	//�����������Բ���Ҽ�����
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
