#pragma once
#include"HiEasyX/HiEasyX.h"
//窗口相关
#define CWNDW 180
#define CWNDH 150
#define ONLYEXIT EX_NOMINIMIZE|EX_SHOWCONSOLE
#define CWNDTITLE L"连接服务器"
//IP输入框相关
#define IPEDITX 10
#define IPEDITY 10
#define IPEDITW 160
#define IPEDITH 25
#define IPEDITTIP L"在此输入服务器地址"
#define IPMAXLEN 15
//端口输入框相关
#define PORTEDITX 10
#define	PORTEDITY 45
#define	PORTEDITW 160
#define	PORTEDITH 25
#define	PORTEDITTIP L"在此输入服务器端口"
#define PORTMAXLEN 5
//按钮相关
#define BTNX 50
#define BTNY 85
#define BTNW 80
#define BTNH 30
#define BTNTIP L"连接"
//杂项
#define FONT L"微软雅黑"
#define EDITFONTSIZE 20 //输入框字号
#define BTNFONTSIZE 20 //按钮字号


class Connect
{
private:
	hiex::Window ConnectWnd;
	hiex::SysEdit IP;
	hiex::SysEdit PORT;
	hiex::SysButton ConnectBtn;

public:
	Connect();
	HWND GetHandle();				//获取窗口句柄
	bool IsWndAlive();				//窗口是否存在
	void UnAliveExit();				//窗口不存在直接退出
	void CloseWnd();				//关闭窗口
	bool IsBtnClick();				//按钮是否点击
	bool IsBtnVisible();			//按钮是否可见
	void SetBtnvisible(bool able);	//设置按钮不可见
	std::wstring GetIP();			//获取输入IP
	std::wstring GetPORT();			//获取输入端口
	~Connect();
};

