#pragma once
#include<iostream>     
#include<stdlib.h>
#include<assert.h>
#include<conio.h>
using namespace std;

#define INIT_SEQLINIT_SIZE 10//˳���ĳ�ʼ��С
typedef int Date;
typedef struct
{
	Date* base;//ָ���׵�ַ��ָ��
	int capacity;//�������
	int size;//��ǰԪ������
}SeqiList;

//���Ա�ĳ�ʼ��
void initList(SeqiList* list) 
{
	list->capacity = INIT_SEQLINIT_SIZE;//�������=˳���ĳ�ʼ��С
	list->size = 0;//��ǰԪ������
	list->base = (Date*)calloc(list->capacity,sizeof(Date));//ʹ��calloc()���������ڴ�
	assert(list->base!=NULL);//�����ʼ���Ƿ�ɹ����ڴ������Ƿ�ɹ���
}

Date Gte_base(SeqiList* list, int i)
{
	return 0;
}


//β������,������������ 1
void push_back(SeqiList* list,Date date) 
{
	if (list->size >= list->capacity)//�����ǰԪ���������ڵ����������������ʧ��
	{
		cout << "����ʧ�ܣ�Ԫ�������Ѵ����" << endl;
		return;
	}
	list->base[list->size] = date;
	list->size++;
}

//��ӡ����˳���,������������ 3
void show_list(SeqiList* list) 
{
	for (int i = 0; i < list->size; i++)
	{
		cout << list->base[i] << endl;
	}
}

//������
void meu() 
{
	cout << "[1]β������" << "     " << "[2]" << endl;
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
	meu();//������
	SeqiList list;//�������Ա�
	initList(&list);//���Ա��ʼ��
	Date i = 0;
	while (1)
	{
		if (_kbhit())
		{
			int userkey = _getch();
			switch (userkey)
			{
			case 49://1
				cout  << "������Ҫ�����Ԫ�أ�";
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

	
