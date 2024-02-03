#pragma once
#include <iostream>
using namespace std;


typedef  int date;
typedef struct xunhuanlianbiao
{
	date xinxiyu;
	xunhuanlianbiao* zhizhenyu;
}lianbiao, * lianbiaozhizhen;

//初始化
lianbiaozhizhen chushihuaxunhuanlianbiao()
{
	lianbiaozhizhen L = (lianbiaozhizhen)malloc(sizeof(lianbiao));
	if (L == NULL)
	{
		cout << "开辟空间失败" << endl;
		return NULL;
	}
	L->xinxiyu = 0;
	L->zhizhenyu = L;
}

//头插入
void toucharu(lianbiaozhizhen L, date n)
{
	lianbiaozhizhen newjiedian = (lianbiaozhizhen)malloc(sizeof(lianbiao));
	if (newjiedian == NULL)
	{
		cout << "开辟空间失败" << endl;
		return ;
	}
	newjiedian->xinxiyu = n;
	newjiedian->zhizhenyu = L->zhizhenyu;//新节点的指针域指向原链表的首元结点
	L->zhizhenyu = newjiedian;//链表的头节点指针域指向新节点
	L->xinxiyu++;
}

//尾插入
void weicharu(lianbiaozhizhen L, date n)
{
	lianbiaozhizhen newjieidan = (lianbiaozhizhen)malloc(sizeof(lianbiao));
	if (newjieidan == NULL)
	{
		cout << "开辟空间失败" << endl;
		return;
	}
	newjieidan->xinxiyu = n;
	newjieidan->zhizhenyu = L; //将新节点的指针指向头节点
	lianbiaozhizhen p = L;
	while (p->zhizhenyu != L) //找到尾节点
	{
		p = p->zhizhenyu;
	}
	p->zhizhenyu = newjieidan; //将尾节点的指针指向新节点
	(L->xinxiyu)++;
}

//顺序输出
void shunxushuchu(lianbiaozhizhen L)
{
	lianbiao* p = L->zhizhenyu;
	if (p == L)
	{
		cout << "链表为空" << endl;
		return;
	}
	while (p != L)
	{
		cout << p->xinxiyu << endl;
		p = p->zhizhenyu;
	}
}




int main2()
{
	lianbiaozhizhen L = chushihuaxunhuanlianbiao();	
	toucharu(L, 3);
	toucharu(L, 2);
	toucharu(L, 1);
	weicharu(L,4);
	shunxushuchu(L);

	system("pause");
	return 0;
}


