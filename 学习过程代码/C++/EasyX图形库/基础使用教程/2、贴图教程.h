#pragma once
#include<easyx.h>
#include"ֱ����͸������png.h"
void two()
{
	//��ͼ
		//ԭ����ͼ
			// ��IMAGE���ͱ�����ʾͼ��
			// ԭ������ͼƬ������	loadimage(IMAGE*img,URL);�����ż��غ�����	loadimage(IMAGE*img,URL,int height,int width);
			// ��ʾͼ������	putimage(int x,int y,IMAGE*img);

	IMAGE img;
	loadimage(&img, "./��ͼ�ļ�/111.jpg", 800, 650);
	putimage(0, 0, &img);

	//͸����ͼ

	// ͨ��ͼ��Ķ���������ﵽȥ����Ч��
	// ����ͼ������ͼ
	// �����ض�������ͼ����
	// 1��λ������	SRCAND ������ͼ
	// 2���������  SRCPAINT ������ͼ

	IMAGE leimu[2];
	loadimage(leimu + 0, "./��ͼ�ļ�/222����ͼ.jpg", 400, 640);
	loadimage(leimu + 1, "./��ͼ�ļ�/222����ͼ.jpg", 400, 640);
	putimage(0, 0, leimu + 0, SRCAND);
	putimage(0, 0, leimu + 1, SRCPAINT);

	//ͨ����װ�ĺ���ֱ����png͸��ͼ
	IMAGE leimu1;
	loadimage(&leimu1, "./��ͼ�ļ�/222͸��ͼ.png", 400, 640);
	drawAlpha(&leimu1, 400, 0);
}