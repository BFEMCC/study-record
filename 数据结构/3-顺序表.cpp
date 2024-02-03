#pragma once
#include<iostream>     
#include<stdlib.h>
#include<assert.h>
#include<conio.h>
using namespace std;

#define INIT_SEQLINIT_SIZE 10//顺序表的初始大小
typedef int Date;
typedef struct
{
	Date* base;//指向首地址的指针
	int capacity;//最大容量
	int size;//当前元素数量
}SeqiList;

//线性表的初始化
void initList(SeqiList* list) 
{
	list->capacity = INIT_SEQLINIT_SIZE;//最大容量=顺序表的初始大小
	list->size = 0;//当前元素数量
	list->base = (Date*)calloc(list->capacity,sizeof(Date));//使用calloc()函数申请内存
	assert(list->base!=NULL);//检验初始化是否成功（内存申请是否成功）
}

Date Gte_base(SeqiList* list, int i)
{
	return 0;
}


//尾部插入,按键：主键区 1
void push_back(SeqiList* list,Date date) 
{
	if (list->size >= list->capacity)//如果当前元素数量大于等于最大容量，插入失败
	{
		cout << "插入失败，元素数量已达最大" << endl;
		return;
	}
	list->base[list->size] = date;
	list->size++;
}

//打印整个顺序表,按键：主键区 3
void show_list(SeqiList* list) 
{
	for (int i = 0; i < list->size; i++)
	{
		cout << list->base[i] << endl;
	}
}

//主界面
void meu() 
{
	cout << "[1]尾部插入" << "     " << "[2]" << endl;
	cout << "[3]" << "     " << "[4]" << endl;
	cout << "[5]" << "     " << "[6]" << endl;
	cout << "[7]" << "     " << "[8]" << endl;
	cout << "[9]" << "     " << "[0]" << endl;
	cout << "[A]" << "     " << "[B]" << endl;
	cout << "[C]" << "     " << "[D]" << endl;
	cout << "[E]" << "     " << "[F]" << endl;
}

int main4()
{
	meu();//主界面
	SeqiList list;//创建线性表
	initList(&list);//线性表初始化
	Date i = 0;
	while (1)
	{
		if (_kbhit())
		{
			int userkey = _getch();
			switch (userkey)
			{
			case 49://1
				cout  << "请输入要插入的元素：";
				cin >> i;
				push_back(&list, i);
				break;
			case 50://2

				break;
			case 51://3
				show_list(&list);
				break;
			case 52://4

				break;
			case 53://5

				break;
			case 54://6

				break;
			case 55://7

				break;
			case 56://8

				break;
			case 57://9

				break;
			case 48://0

				break;
			case 65://A

				break;
			}
		}
	}
	system("pause");
	return 0;
}

	
