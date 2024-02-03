#include<iostream>
#include<string>
#include<windows.h>
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include <setjmp.h>
#include<mmsystem.h>
#include <ctime>
#pragma comment(lib,"winmm.lib")
using namespace std;
jmp_buf lab1;
#define width 640 //窗口宽度
#define height 480 //窗口高度
#define max_snake 100//蛇的最大节数（长度）
struct DIR//蛇的方向
{
	int up;
	int down;
	int left;
	int right;
}dir;
struct food_tlg
{
	POINT fd;
	int flag;
} food;
struct snake_tlg//蛇的结构体
{
	int num;//蛇的节数（长度）
	DIR dir;//方向
	int score;//分数
	int size;//单节蛇的长度（矩形边长）
	POINT coor[max_snake];
}snake;
int randnum_1()//返回1号随机数
{
	srand(GetTickCount64());//获取本机运行时间为随机数种子
	return rand();
}
int randnum_2()//返回2号随机数
{
	srand(time(0));//用time设置随机数种子
	return rand();
}
void main_music()
{
	mciSendString(_T("open 背景音乐.mp3 alias a"), 0, 0, 0);
	mciSendString(_T("play a repeat"), 0, 0, 0);
}
void eatfood_music()//吃食物音效，还没写好，待完善
{
	mciSendString(_T("open 吃食物音效.mp3 alias a"), 0, 0, 0);
	mciSendString(_T("play a repeat"), 0, 0, 0);
}
void diemusic()//死亡音效，还没写
{

}
void gameinit_snake() //初始化蛇
{
	snake.num = 3;//蛇的初始节数
	//初始方向设置，默认为右方向
	snake.dir.up = 0;
	snake.dir.down = 0;
	snake.dir.left = 0;
	snake.dir.right = 1;
	//
	snake.score = 0;//初始得分为0
	snake.size = 10;//单节蛇的边长为10
	snake.coor[2].x = snake.coor[1].x - snake.size;
	snake.coor[2].y = snake.coor[1].y - snake.size;
	snake.coor[1].x = snake.coor[0].x - snake.size;
	snake.coor[1].y = snake.coor[0].y - snake.size;
	snake.coor[0].x = ((randnum_2() % (width / snake.size)) * snake.size);
	snake.coor[0].y = ((randnum_1() % (height / snake.size)) * snake.size);
}
void gameinit_food()//设置食物坐标和状态
{
lab1:
	int foodx = (randnum_1() % (width / snake.size)) * snake.size;
	int foody = (randnum_2() % (height / snake.size)) * snake.size;
	/*
	int k = 0;
	for (int i = 0; i < snake.num; i++)
	{
		if (foodx != snake.coor[i].x && foody != snake.coor[i].y)
		{
			k++;
		}
	}
	if(k==snake.num)
	{
		food.fd.x = foodx; //用随机数设置食物x坐标
		food.fd.y = foody; //用随机数设置食物y坐标
		food.flag = 1;//食物存在状态，1为存在
	}
	else if (k != snake.num)
	{
		goto lab1;
	}
	*/
	food.fd.x = foodx; //用随机数设置食物x坐标
	food.fd.y = foody; //用随机数设置食物y坐标
	food.flag = 1;//食物存在状态，1为存在
	cout << foodx << "," << foody  << endl;
	cout << snake.coor[0].x <<"," << snake.coor[0].y << endl;
	//cout << k << "," << snake.num << endl;
}
void drawsnakeandfood()//画蛇和食物
{
	for (int i = 0; i < snake.num; i++)//画蛇
	{
		setlinecolor(BLACK);//设置边框线的颜色
		setfillcolor(RGB(255, 100, 100));//蛇的（方块）颜色
		//solidrectangle(snake.coor[i].x, snake.coor[i].y, snake.coor[i].x+snake.size, snake.coor[i].y+snake.size);//画方块，方式：颜色填充,无边框
		fillrectangle(snake.coor[i].x, snake.coor[i].y, snake.coor[i].x + snake.size, snake.coor[i].y + snake.size);//画方块，方式：留有边框，默认边框颜色白色？（应该是白色）
	}
	//画食物
	if (food.flag == 1 )//食物存在（或者说应该存在）并且食物和蛇的身体没有重合
	{
		setfillcolor(RGB(138, 97, 248));//食物颜色
		solidrectangle(food.fd.x, food.fd.y, food.fd.x + snake.size, food.fd.y + snake.size); //画食物，方式：颜色填充, 无边框
	}
	if (food.flag == 0 )//食物不存在（被吃掉了，不应该存在），或者食物和蛇的身体重合了
	{
		gameinit_food();//重新初始化食物
	}
}
void snakemove()//蛇的移动，后续方块坐标等于前一方块坐标
{
	/*
//方式一
	for (int i = 1; i < snake.num; i++)
	{
		int a = snake.coor[0].x;
		int b =  snake.coor[0].y;
		snake.coor[i].x = a;
		snake.coor[i].y = b;
	}
	//实测会少一截身体
	/**/
	//方式二
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.coor[i].x = snake.coor[i - 1].x;
		snake.coor[i].y = snake.coor[i - 1].y;
	}
	if (snake.dir.up == 1)
	{
		snake.coor[0].y -= snake.size;
		if (snake.coor[0].y + snake.size == 0)
		{
			snake.coor[0].y = height - snake.size;
		}
		snake.dir.down = 0;
	}
	if (snake.dir.down == 1)
	{
		snake.coor[0].y += snake.size;
		if (snake.coor[0].y == height)
		{
			snake.coor[0].y = 0;
		}
		snake.dir.up = 0;
	}
	if (snake.dir.left == 1)
	{
		snake.coor[0].x -= snake.size;
		if (snake.coor[0].x + snake.size == 0)
		{
			snake.coor[0].x = width - snake.size;
		}
		snake.dir.right = 0;
	}
	if (snake.dir.right == 1)
	{
		snake.coor[0].x += snake.size;
		if (snake.coor[0].x == width)
		{
			snake.coor[0].x = 0;
		}
		snake.dir.left = 0;
	}

}
void keycontrol()//方向控制
{//使用win32API获取键盘按键信息
	if (GetAsyncKeyState(VK_UP) && snake.dir.down == 0)
	{
		cout << "上" << endl;
		snake.dir.up = 1;
		snake.dir.down = 0;
		snake.dir.left = 0;
		snake.dir.right = 0;
	}
	if (GetAsyncKeyState(VK_DOWN) && snake.dir.up == 0)
	{
		snake.dir.up = 0;
		snake.dir.down = 1;
		snake.dir.left = 0;
		snake.dir.right = 0;
	}
	if (GetAsyncKeyState(VK_LEFT) && snake.dir.right == 0)
	{
		snake.dir.up = 0;
		snake.dir.down = 0;
		snake.dir.left = 1;
		snake.dir.right = 0;
	}
	if (GetAsyncKeyState(VK_RIGHT) && snake.dir.left == 0)
	{
		snake.dir.up = 0;
		snake.dir.down = 0;
		snake.dir.left = 0;
		snake.dir.right = 1;
	}
}
void eatfood()//吃食物相关
{
	if (snake.coor[0].x == food.fd.x && snake.coor[0].y == food.fd.y && food.flag == 1)
	{
		eatfood_music();//吃食物音效，没写完，待完善
		snake.num += 1;//节数++
		snake.score++;//分数++
		food.flag = 0;//食物存在状态判定为0；
	}
}
void coutscore()//输出得分
{
	TCHAR score[10] = _T("得分:");   //http://t.csdn.cn/bzMmf https://docs.easyx.cn/zh-cn/outtextxy这里涉及字符集编码等相关知识，详细讲解见链接文章
	for (int i = 0; i < (to_string(snake.score)).length(); i++)//将snake.score转为string，再用遍历的方法将string转为char数组
	{
		score[i + 3] = to_string(snake.score)[i];
	}
	settextstyle(30, 0, _T("楷体"));
	settextcolor(BLACK);//设置字体为黑色
	setbkmode(TRANSPARENT);//设置字体背景为透明
	outtextxy(20, 20, score);
}
void canteatmyself()//游戏结束判断
{
	for (int i = 4; i < snake.num; i++)
	{
		if (snake.coor[0].x == snake.coor[i].x && snake.coor[0].y == snake.coor[i].y)
		{
			//diemusic();//死亡音效，还没写
			settextstyle(50, 0, _T("楷体"));
			settextcolor(BLACK);//设置字体颜色为黑色
			setbkmode(TRANSPARENT);//设置字体背景为透明
			outtextxy(180, 200, _T("GAME OVER!菜逼"));
			_getch();
			Sleep(1500);
			longjmp(lab1, 1);//跳转至lab1处，重新开始游戏
		}
	}
}
void pause()//暂停功能，还没写
{

}
int main()
{
	setjmp(lab1);//设置跳转点，game over时跳转至此，重新开始游戏
	initgraph(width, height, SHOWCONSOLE);//初始化图形窗口,0换成SHOWCONSOLE可以展示控制台
	setbkcolor(RGB(188, 242, 243));//设置图形窗口背景颜色
	gameinit_snake();
	gameinit_food();
	main_music();
	DWORD t1, t2;
	t1 = t2 = GetTickCount64();
	BeginBatchDraw();
	while (1)
	{
		if (t2 - t1 > 100)
		{
			snakemove();
			t1 = t2;
		}
		t2 = GetTickCount64();
		cleardevice();//清除已有图形
		drawsnakeandfood();
		eatfood();
		coutscore();
		keycontrol();
		canteatmyself();
		EndBatchDraw();
		Sleep(1);
	}
	system("pause");
	closegraph();//关闭图形窗口
	return 0;
}
