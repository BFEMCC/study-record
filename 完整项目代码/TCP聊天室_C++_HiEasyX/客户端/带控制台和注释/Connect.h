#pragma once
#include"HiEasyX/HiEasyX.h"
//�������
#define CWNDW 180
#define CWNDH 150
#define ONLYEXIT EX_NOMINIMIZE|EX_SHOWCONSOLE
#define CWNDTITLE L"���ӷ�����"
//IP��������
#define IPEDITX 10
#define IPEDITY 10
#define IPEDITW 160
#define IPEDITH 25
#define IPEDITTIP L"�ڴ������������ַ"
#define IPMAXLEN 15
//�˿���������
#define PORTEDITX 10
#define	PORTEDITY 45
#define	PORTEDITW 160
#define	PORTEDITH 25
#define	PORTEDITTIP L"�ڴ�����������˿�"
#define PORTMAXLEN 5
//��ť���
#define BTNX 50
#define BTNY 85
#define BTNW 80
#define BTNH 30
#define BTNTIP L"����"
//����
#define FONT L"΢���ź�"
#define EDITFONTSIZE 20 //������ֺ�
#define BTNFONTSIZE 20 //��ť�ֺ�


class Connect
{
private:
	hiex::Window ConnectWnd;
	hiex::SysEdit IP;
	hiex::SysEdit PORT;
	hiex::SysButton ConnectBtn;

public:
	Connect();
	HWND GetHandle();				//��ȡ���ھ��
	bool IsWndAlive();				//�����Ƿ����
	void UnAliveExit();				//���ڲ�����ֱ���˳�
	void CloseWnd();				//�رմ���
	bool IsBtnClick();				//��ť�Ƿ���
	bool IsBtnVisible();			//��ť�Ƿ�ɼ�
	void SetBtnvisible(bool able);	//���ð�ť���ɼ�
	std::wstring GetIP();			//��ȡ����IP
	std::wstring GetPORT();			//��ȡ����˿�
	~Connect();
};

