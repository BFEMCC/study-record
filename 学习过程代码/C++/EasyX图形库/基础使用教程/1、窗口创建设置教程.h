#pragma once
#include<easyx.h>
void one()
{
	//����ͼ�δ��ں���	initraph(int x,int y,bool),����������,���Σ�0��1���޲�������Ӧ�������Ƿ���ʾ����̨���������������޲���Ĭ�ϲ���ʾ����̨
		//ͼ�λ����������Ͻ�Ϊԭ�㣬����Ϊx������������Ϊy��������
	initgraph(600, 400, 1);

	//������ɫ���ã�������	setbkcolor();	���������÷�ʽ����ɫ�꣬RGB���á���ɫ��ָ������ɫ��Ӣ���д���ʣ���RED��YELLOW��
	setbkcolor(WHITE);

	//ˢ�´��ڣ�����	cleardevice();
	cleardevice();

	//������ͼ����
	
	//���û���ͼ�ߵĵ���ɫ��������setlinecolor();��Ҫ������
	setlinecolor(RED);

	//��ֱ�ߣ�������	line(int x1,int x2,int x3,int x4); ��������(x1,x2)��һ��ֱ�ߵ�����(x3,x4)
	line(0, 0, 600, 400);

	//��Բ��������	circle(int x,int y��int r);����(x1,x2)ΪԲ�ģ�int rΪ�뾶��Բ
	circle(100, 100, 50);

	//�����Σ�������	rectangle(int x1,int y1,int x2,int y2);�����Ͻ�����(x1,y1),���½�����(x2,y2)
	rectangle(300, 300, 200, 200);

	//���������ɫ��������setfliicolor();��Ҫ������
	//�����Բ�����߿�fillcircle();�����ͻ�Բһ���������߿�solidcircle();�����ͻ�Բһ��
	//�������Σ����߿�fillrectangle();�������߿�solidrectangle();����������ͬ������
}