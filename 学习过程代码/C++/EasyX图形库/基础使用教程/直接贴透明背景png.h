#pragma once
#include<easyx.h>
//把像素的颜色拆解出来 ARGB
typedef struct _ARGB
{
	byte a;
	byte r;
	byte g;
	byte b;
}ARGB;
//把颜色拆解
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
//把彩色图转成黑白图
void toGray(IMAGE* src)
{
	DWORD* psrc = GetImageBuffer(src);
	for (int i = 0; i < src->getwidth() * src->getheight(); i++)
	{
		//获取每一个像素点的颜色值
		ARGB t = color2Argb(psrc[i]);
		//灰度图，求三个或四个颜色的平均值
		byte arv = (t.r + t.g + t.b) / 3;
		ARGB res = { t.a,arv,arv };
		psrc[i] = argb2Color(res);
	}
}
/*
	*@png透明贴图
*/
void drawImg(int x, int y, IMAGE* src)
{
	//变量初始化
	DWORD* pwin = GetImageBuffer();		//窗口缓冲区指针
	DWORD* psrc = GetImageBuffer(src);	//图片缓冲区指针
	int win_w = getwidth();				//窗口宽高
	int win_h = getheight();
	int src_w = src->getwidth();		//图片宽高
	int src_h = src->getheight();

	//计算贴图的实际长宽
	int real_w = (x + src_w > win_w) ? win_w - x : src_w;		//处理超出右边界
	int real_h = (y + src_h > win_h) ? win_h - y : src_h;		//处理超出下边界
	if (x < 0) { psrc += -x;		real_w -= -x; x = 0; }		//处理超出左边界
	if (y < 0) { psrc +=(src_w*-y); real_h -= -y; y = 0; }		//处理超出上边界


	//修正贴图起始位置
	pwin += (win_w * y + x);

	//实现透明贴图
	for (int iy = 0; iy < real_h; iy++);
	{
		for (int ix = 0; ix < real_w; ix++)
		{
			byte a = (byte)(psrc[ix] >> 24);//计算透明通道的值[0，256） 0为完全透明 255为完全不透明
			if (a > 100)
			{
				pwin[ix] = psrc[ix];
			}
		}
		//换到下一行
		pwin += win_w;
		psrc += src_w;
	}
}



/*------------------------------------------------------------------------------------------------------*/

//上述为看的视频教程中讲师分享的他自己封装的.h文件（包含头文件），实现直接贴png透明图
//但实际使用没有任何效果
//以下为本人在CSDN中找的一个函数，可以实现直接贴png透明图的功能
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //x为载入图片的X坐标，y为Y坐标
{

	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}