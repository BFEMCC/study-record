#pragma once
#include<easyx.h>
#include"直接贴透明背景png.h"
void two()
{
	//贴图
		//原样贴图
			// 用IMAGE类型变量表示图形
			// 原样加载图片函数：	loadimage(IMAGE*img,URL);，缩放加载函数：	loadimage(IMAGE*img,URL,int height,int width);
			// 显示图像函数：	putimage(int x,int y,IMAGE*img);

	IMAGE img;
	loadimage(&img, "./贴图文件/111.jpg", 800, 650);
	putimage(0, 0, &img);

	//透明贴图

	// 通过图像的二进制运算达到去背景效果
	// 掩码图、背景图
	// 按照特定步骤贴图即可
	// 1、位与运算	SRCAND 贴掩码图
	// 2、异或运算  SRCPAINT 贴背景图

	IMAGE leimu[2];
	loadimage(leimu + 0, "./贴图文件/222掩码图.jpg", 400, 640);
	loadimage(leimu + 1, "./贴图文件/222背景图.jpg", 400, 640);
	putimage(0, 0, leimu + 0, SRCAND);
	putimage(0, 0, leimu + 1, SRCPAINT);

	//通过封装的函数直接贴png透明图
	IMAGE leimu1;
	loadimage(&leimu1, "./贴图文件/222透明图.png", 400, 640);
	drawAlpha(&leimu1, 400, 0);
}