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
#define width 640 //���ڿ��
#define height 480 //���ڸ߶�
#define max_snake 100//�ߵ������������ȣ�
struct DIR//�ߵķ���
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
struct snake_tlg//�ߵĽṹ��
{
	int num;//�ߵĽ��������ȣ�
	DIR dir;//����
	int score;//����
	int size;//�����ߵĳ��ȣ����α߳���
	POINT coor[max_snake];
}snake;
int randnum_1()//����1�������
{
	srand(GetTickCount64());//��ȡ��������ʱ��Ϊ���������
	return rand();
}
int randnum_2()//����2�������
{
	srand(time(0));//��time�������������
	return rand();
}
void main_music()
{
	mciSendString(_T("open ��������.mp3 alias a"), 0, 0, 0);
	mciSendString(_T("play a repeat"), 0, 0, 0);
}
void eatfood_music()//��ʳ����Ч����ûд�ã�������
{
	mciSendString(_T("open ��ʳ����Ч.mp3 alias a"), 0, 0, 0);
	mciSendString(_T("play a repeat"), 0, 0, 0);
}
void diemusic()//������Ч����ûд
{

}
void gameinit_snake() //��ʼ����
{
	snake.num = 3;//�ߵĳ�ʼ����
	//��ʼ�������ã�Ĭ��Ϊ�ҷ���
	snake.dir.up = 0;
	snake.dir.down = 0;
	snake.dir.left = 0;
	snake.dir.right = 1;
	//
	snake.score = 0;//��ʼ�÷�Ϊ0
	snake.size = 10;//�����ߵı߳�Ϊ10
	snake.coor[2].x = snake.coor[1].x - snake.size;
	snake.coor[2].y = snake.coor[1].y - snake.size;
	snake.coor[1].x = snake.coor[0].x - snake.size;
	snake.coor[1].y = snake.coor[0].y - snake.size;
	snake.coor[0].x = ((randnum_2() % (width / snake.size)) * snake.size);
	snake.coor[0].y = ((randnum_1() % (height / snake.size)) * snake.size);
}
void gameinit_food()//����ʳ�������״̬
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
		food.fd.x = foodx; //�����������ʳ��x����
		food.fd.y = foody; //�����������ʳ��y����
		food.flag = 1;//ʳ�����״̬��1Ϊ����
	}
	else if (k != snake.num)
	{
		goto lab1;
	}
	*/
	food.fd.x = foodx; //�����������ʳ��x����
	food.fd.y = foody; //�����������ʳ��y����
	food.flag = 1;//ʳ�����״̬��1Ϊ����
	cout << foodx << "," << foody  << endl;
	cout << snake.coor[0].x <<"," << snake.coor[0].y << endl;
	//cout << k << "," << snake.num << endl;
}
void drawsnakeandfood()//���ߺ�ʳ��
{
	for (int i = 0; i < snake.num; i++)//����
	{
		setlinecolor(BLACK);//���ñ߿��ߵ���ɫ
		setfillcolor(RGB(255, 100, 100));//�ߵģ����飩��ɫ
		//solidrectangle(snake.coor[i].x, snake.coor[i].y, snake.coor[i].x+snake.size, snake.coor[i].y+snake.size);//�����飬��ʽ����ɫ���,�ޱ߿�
		fillrectangle(snake.coor[i].x, snake.coor[i].y, snake.coor[i].x + snake.size, snake.coor[i].y + snake.size);//�����飬��ʽ�����б߿�Ĭ�ϱ߿���ɫ��ɫ����Ӧ���ǰ�ɫ��
	}
	//��ʳ��
	if (food.flag == 1 )//ʳ����ڣ�����˵Ӧ�ô��ڣ�����ʳ����ߵ�����û���غ�
	{
		setfillcolor(RGB(138, 97, 248));//ʳ����ɫ
		solidrectangle(food.fd.x, food.fd.y, food.fd.x + snake.size, food.fd.y + snake.size); //��ʳ���ʽ����ɫ���, �ޱ߿�
	}
	if (food.flag == 0 )//ʳ�ﲻ���ڣ����Ե��ˣ���Ӧ�ô��ڣ�������ʳ����ߵ������غ���
	{
		gameinit_food();//���³�ʼ��ʳ��
	}
}
void snakemove()//�ߵ��ƶ������������������ǰһ��������
{
	/*
//��ʽһ
	for (int i = 1; i < snake.num; i++)
	{
		int a = snake.coor[0].x;
		int b =  snake.coor[0].y;
		snake.coor[i].x = a;
		snake.coor[i].y = b;
	}
	//ʵ�����һ������
	/**/
	//��ʽ��
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
void keycontrol()//�������
{//ʹ��win32API��ȡ���̰�����Ϣ
	if (GetAsyncKeyState(VK_UP) && snake.dir.down == 0)
	{
		cout << "��" << endl;
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
void eatfood()//��ʳ�����
{
	if (snake.coor[0].x == food.fd.x && snake.coor[0].y == food.fd.y && food.flag == 1)
	{
		eatfood_music();//��ʳ����Ч��ûд�꣬������
		snake.num += 1;//����++
		snake.score++;//����++
		food.flag = 0;//ʳ�����״̬�ж�Ϊ0��
	}
}
void coutscore()//����÷�
{
	TCHAR score[10] = _T("�÷�:");   //http://t.csdn.cn/bzMmf https://docs.easyx.cn/zh-cn/outtextxy�����漰�ַ�����������֪ʶ����ϸ�������������
	for (int i = 0; i < (to_string(snake.score)).length(); i++)//��snake.scoreתΪstring�����ñ����ķ�����stringתΪchar����
	{
		score[i + 3] = to_string(snake.score)[i];
	}
	settextstyle(30, 0, _T("����"));
	settextcolor(BLACK);//��������Ϊ��ɫ
	setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
	outtextxy(20, 20, score);
}
void canteatmyself()//��Ϸ�����ж�
{
	for (int i = 4; i < snake.num; i++)
	{
		if (snake.coor[0].x == snake.coor[i].x && snake.coor[0].y == snake.coor[i].y)
		{
			//diemusic();//������Ч����ûд
			settextstyle(50, 0, _T("����"));
			settextcolor(BLACK);//����������ɫΪ��ɫ
			setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
			outtextxy(180, 200, _T("GAME OVER!�˱�"));
			_getch();
			Sleep(1500);
			longjmp(lab1, 1);//��ת��lab1�������¿�ʼ��Ϸ
		}
	}
}
void pause()//��ͣ���ܣ���ûд
{

}
int main()
{
	setjmp(lab1);//������ת�㣬game overʱ��ת���ˣ����¿�ʼ��Ϸ
	initgraph(width, height, SHOWCONSOLE);//��ʼ��ͼ�δ���,0����SHOWCONSOLE����չʾ����̨
	setbkcolor(RGB(188, 242, 243));//����ͼ�δ��ڱ�����ɫ
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
		cleardevice();//�������ͼ��
		drawsnakeandfood();
		eatfood();
		coutscore();
		keycontrol();
		canteatmyself();
		EndBatchDraw();
		Sleep(1);
	}
	system("pause");
	closegraph();//�ر�ͼ�δ���
	return 0;
}
