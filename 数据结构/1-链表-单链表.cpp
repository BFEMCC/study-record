#pragma once
#include <iostream>
using namespace std;

typedef int date;
typedef struct danlianbiao//单链表
{
	date xinxiyu;
	danlianbiao* zhizhengyu;
	
}lianbiao,* lianbiaozhizhenbieming;//单链表别名：lianbiao（链表），单链表指针别名：lianbiaozhizhenbieming（链表指针别名）

//初始化单链表，创建一个空的单链表
lianbiao* initlianbiao()
{
	lianbiao*L = (lianbiao*)malloc(sizeof(lianbiao));//创建一个单链表的头节点
	if (L == NULL)
	{
		cout << "开辟空间失败" << endl;
		return NULL;
	}
	L->xinxiyu = 0;//头节点信息域为0,记录元素数量
	L->zhizhengyu = NULL;//头节点指针域为空
	return L;
}
 
//前插法
void qianchafa(lianbiao *L, date n)
{
	lianbiao* newjiedian = (lianbiao*)malloc(sizeof(lianbiao));//创建新结点
	if (newjiedian == NULL)
	{
		cout << "开辟空间失败" << endl;
		return;
	}
	newjiedian->xinxiyu = n;//将插入数据赋值给新节点的信息域
	newjiedian->zhizhengyu = L->zhizhengyu;//新节点的指针域指向原链表的首元结点
	L->zhizhengyu = newjiedian;//链表的头节点指针域指向新节点
	L->xinxiyu++;
}

//尾插法
void weichafa(lianbiao* L, date n)
{
	lianbiao* newjiedian = (lianbiao*)malloc(sizeof(lianbiao));//创建新结点
	if (newjiedian == NULL)
	{
		cout << "开辟空间失败" << endl;
		return;
	}
	newjiedian->xinxiyu = n;//将插入数据赋值给新节点的信息域
	newjiedian->zhizhengyu = NULL;//新节点的指针域为空
	if (L ->zhizhengyu== NULL) 
	{
		// 链表为空，将新节点作为第一个节点
		L->zhizhengyu = newjiedian;
	}
	else 
	{
		// 找到尾节点
		lianbiao* p = L;
		while (p->zhizhengyu != NULL) 
		{
			p = p->zhizhengyu;
		}
		// 将尾节点的指针域指向新节点
		p->zhizhengyu = newjiedian;
		L->xinxiyu++;
	}
}

//指定位置插入
void zhidingweizhicharu(lianbiao* L,int i, date n)
{
	if (i<1 || i>((L->xinxiyu) + 1))
	{
		cout << "位置非法" << endl;
		return;
	}
	else
	{
		lianbiao* newjiedian = (lianbiao*)malloc(sizeof(lianbiao));//创建新结点
		if (newjiedian == NULL)
		{
			cout << "开辟空间失败" << endl;
			return;
		}
		newjiedian->xinxiyu = n;//将插入数据赋值给新节点的信息域
		lianbiao* p = L;
		for (int j = 1; j < i; j++) //找到待插入位置的前一个节点
		{
			p = p->zhizhengyu;
		}
		newjiedian->zhizhengyu = p->zhizhengyu; //插入操作
		p->zhizhengyu = newjiedian;
		L->xinxiyu++;
	}
}

//指定位置删除
void zhidingweizhishanchu(lianbiao* L, int i)
{
	if (L->zhizhengyu == NULL)
	{
		cout << "链表为空" << endl;
		return;
	}
	else if (i<1 || i>((L->xinxiyu) + 1))
	{
		cout << "位置非法" << endl;
		return;
	}
	else
	{
		lianbiao* p = L;
		for (int j = 1; j < i; j++)
		{
			p = p->zhizhengyu;
		}
		lianbiao* q = p->zhizhengyu; //要删除的节点
		p->zhizhengyu = q->zhizhengyu; //删除操作
		free(q); //释放节点空间
		L->xinxiyu--; //链表长度减1
	}
}

//指定位置修改
void zhidingweizhixiugai(lianbiao* L, int i, date n)
{
	if (L->zhizhengyu == NULL)
	{
		cout << "链表为空" << endl;
		return;
	}
	else if (i<1 || i>(L->xinxiyu))
	{
		cout << "位置非法" << endl;
		return;
	}
	else
	{
		lianbiao* p = L;
		for (int j = 1; j < i; j++)
		{
			p = p->zhizhengyu;
		}
		lianbiao* q = p->zhizhengyu; //要修改的节点
		q->xinxiyu = n;
	}
}

//查找元素，并返回元素下标
int chazhaoyuansu(lianbiao* L, date n)
{
	if (L->zhizhengyu==NULL) 
	{
		cout << "链表为空" << endl;
		return 0;
	}
	else
	{
		lianbiao* p = L;
		int i = 0;
		while (p->zhizhengyu != NULL)
		{
			p = p->zhizhengyu;
			i += 1;
			if (p->xinxiyu == n)
			{
				return i;
			}
		}
	}
	cout << "没有找到" << n << endl;
	return 0;
}

//查看指定位置元素，并返回该位置元素信息域
date chakanzhidingweizhiyuansu(lianbiao* L, int i)
{
	if (L->zhizhengyu == NULL)
	{
		cout << "链表为空" << endl;
		return 0;
	}
	else if (i<1 || i>(L->xinxiyu))
	{
		cout << "位置非法" << endl;
		return 0;
	}
	else
	{
		lianbiao* p = L;
		for (int j=1;j<i+1;j++)
		{
			p = p->zhizhengyu;
		}
		return p->xinxiyu;
	}
	return 0;
}

//顺序输出
void shunxushuchu(lianbiao* L)
{
	lianbiao* p = L->zhizhengyu;
	if(p==NULL)
	{
		cout << "链表为空" << endl;
		return;
	}
	while (p != NULL)
	{
		cout << p->xinxiyu << endl;
		p = p->zhizhengyu;
	}
}

//单链表元素个数
int yuansugeshu(lianbiao* L)
{
	return (L->xinxiyu);
}

//顺序输出所有元素和个数
void showall(lianbiao* L)
{
	shunxushuchu(L);//顺序输出
	cout << "元素个数：" << yuansugeshu(L) << endl;
}


int main1()
{
	lianbiaozhizhenbieming L = initlianbiao();//初始化单链表L

	qianchafa(L, 3);//前插法，插入3
	qianchafa(L,1);//前插法，插入1
	weichafa(L,4);//尾插法，插入4
	zhidingweizhicharu(L,2,2);//在第二个位置插入2
	showall(L);//输出

	zhidingweizhishanchu(L,2);//删除第二个元素，2
	showall(L);//输出

	zhidingweizhicharu(L, 2, 2);//重新在第二个位置插入2
	showall(L);//输出

	zhidingweizhixiugai(L,2,2222);//将第二个元素修改为2222
	showall(L);//输出

	cout << "2222是第"<<chazhaoyuansu(L, 2222) <<"个元素" << endl;
	chazhaoyuansu(L, 2333);

	cout << "第二个元素是：" << chakanzhidingweizhiyuansu(L, 2) << endl;

	cout << endl;
	system("pause");
	return 0;
}

