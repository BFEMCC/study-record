#pragma once
#include<easyx.h>
//�����ص���ɫ������ ARGB
typedef struct _ARGB
{
	byte a;
	byte r;
	byte g;
	byte b;
}ARGB;
//����ɫ���
ARGB color2Argb(DWORD c)
{
	ARGB res;
	res.r = (byte)c;
	res.g = (byte)(c >> 8);
	res.b = (byte)(c >> 16);
	res.a = (byte)(c >> 24);
	return res;
}
DWORD argb2Color(ARGB c)
{
	DWORD t = RGB(c.r, c.g, c.b);
	return((DWORD)c.a) << 24 | t;
}
//�Ѳ�ɫͼת�ɺڰ�ͼ
void toGray(IMAGE* src)
{
	DWORD* psrc = GetImageBuffer(src);
	for (int i = 0; i < src->getwidth() * src->getheight(); i++)
	{
		//��ȡÿһ�����ص����ɫֵ
		ARGB t = color2Argb(psrc[i]);
		//�Ҷ�ͼ�����������ĸ���ɫ��ƽ��ֵ
		byte arv = (t.r + t.g + t.b) / 3;
		ARGB res = { t.a,arv,arv };
		psrc[i] = argb2Color(res);
	}
}
/*
	*@png͸����ͼ
*/
void drawImg(int x, int y, IMAGE* src)
{
	//������ʼ��
	DWORD* pwin = GetImageBuffer();		//���ڻ�����ָ��
	DWORD* psrc = GetImageBuffer(src);	//ͼƬ������ָ��
	int win_w = getwidth();				//���ڿ��
	int win_h = getheight();
	int src_w = src->getwidth();		//ͼƬ���
	int src_h = src->getheight();

	//������ͼ��ʵ�ʳ���
	int real_w = (x + src_w > win_w) ? win_w - x : src_w;		//�������ұ߽�
	int real_h = (y + src_h > win_h) ? win_h - y : src_h;		//�������±߽�
	if (x < 0) { psrc += -x;		real_w -= -x; x = 0; }		//��������߽�
	if (y < 0) { psrc +=(src_w*-y); real_h -= -y; y = 0; }		//�������ϱ߽�


	//������ͼ��ʼλ��
	pwin += (win_w * y + x);

	//ʵ��͸����ͼ
	for (int iy = 0; iy < real_h; iy++);
	{
		for (int ix = 0; ix < real_w; ix++)
		{
			byte a = (byte)(psrc[ix] >> 24);//����͸��ͨ����ֵ[0��256�� 0Ϊ��ȫ͸�� 255Ϊ��ȫ��͸��
			if (a > 100)
			{
				pwin[ix] = psrc[ix];
			}
		}
		//������һ��
		pwin += win_w;
		psrc += src_w;
	}
}



/*------------------------------------------------------------------------------------------------------*/

//����Ϊ������Ƶ�̳��н�ʦ��������Լ���װ��.h�ļ�������ͷ�ļ�����ʵ��ֱ����png͸��ͼ
//��ʵ��ʹ��û���κ�Ч��
//����Ϊ������CSDN���ҵ�һ������������ʵ��ֱ����png͸��ͼ�Ĺ���
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //xΪ����ͼƬ��X���꣬yΪY����
{

	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}