#pragma once
/*-----------�������ֲ���----------*/

#include<Windows.h>//����Ҫ����<windows.h>ͷ�ļ�����EasyX���ͷ�ļ��Ѿ����������Բ������

/*��������Ҫ�ڣ�<Windows.h>��EasyXͷ�ļ�����*/
#include<mmsystem.h>//��ý���豸�ӿ�ͷ�ļ�
#pragma comment(lib,"winmm.lib")//���ؾ�̬��

void PlayMusic()
{
	mciSendString("open ./�����ļ�/������_�����_˪ѩǧ��.mp3 alias ˪ѩǧ��", 0, 0, 0);
	mciSendString("play ˪ѩǧ�� repeat", 0, 0, 0);
	if (GetAsyncKeyState(VK_SPACE))
	{
		mciSendString("close ˪ѩǧ��", 0, 0, 0);
	}


}

/*
* ��һ���������֣���������
mciSendString("open ./����Ҫ���ŵ����ֵ�·��(��Ի����) alias �Զ�������,0,0,0")		

//������һ��0��0��0���ɣ�alias��ȡ������������Ҫ���ŵ�����ȡһ�����������������ģ��Ժ���ÿ���ʹ�ñ���������ÿ�ε��ö�Ҫʹ����������Ի����·��

*�ڶ�������������
mciSendString("play ./����Ҫ���ŵ����ֵ�·��(��Ի����",0,0,0)			//������һ��0��0��0����

���ߣ�ʹ��alias����Զ�������

mciSendString("play �Զ�������0,0,0")

��·�����Զ������ƺ������ repeat ����ѭ������
����		mciSendString("play �Զ������� repeat,0,0,0")


*�ر�����
mciSendString("close �Զ������ƻ�·��",0,0,0)


*/