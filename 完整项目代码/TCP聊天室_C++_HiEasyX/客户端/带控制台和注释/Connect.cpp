#include "Connect.h"

Connect::Connect()
{
	this->ConnectWnd.Create(CWNDW, CWNDH, ONLYEXIT, CWNDTITLE);

	this->IP.PreSetStyle({ false, false, false, false, false, true });//����Ԥ����ʽ
				//�����ı����ı����С�ӵ�д�ֱ���������Զ���ֱ������ӵ��ˮƽ���������Զ�ˮƽ����
	this->IP.Create(this->GetHandle(), IPEDITX, IPEDITY, IPEDITW, IPEDITH, IPEDITTIP);//����
	this->IP.SetFont(EDITFONTSIZE, 0, FONT);//���������ֺ�
	this->IP.SetMaxTextLength(IPMAXLEN);//������󳤶�
	this->IP.NumberOnly(false);//�����Ƿ������

	this->PORT.PreSetStyle({ false, false, false, false, false, true });
	this->PORT.Create(this->GetHandle(), PORTEDITX, PORTEDITY, PORTEDITW, PORTEDITH, PORTEDITTIP);
	this->PORT.SetFont(EDITFONTSIZE, 0, FONT);
	this->PORT.SetMaxTextLength(PORTMAXLEN);
	this->PORT.NumberOnly(true);

	this->ConnectBtn.Create(this->GetHandle(), BTNX, BTNY, BTNW, BTNH, BTNTIP);//������ť
	this->ConnectBtn.SetFont(BTNH - 10, 0, FONT);
}

HWND Connect::GetHandle()
{
	return this->ConnectWnd.GetHandle();
}

bool Connect::IsWndAlive()
{
	return this->ConnectWnd.IsAlive();
}

void Connect::UnAliveExit()
{
	if (!this->IsWndAlive())
	{
		exit(2);
	}
}

void Connect::CloseWnd()
{
	this->ConnectWnd.CloseWindow();
}

bool Connect::IsBtnClick()
{
	return this->ConnectBtn.IsClicked();
}

bool Connect::IsBtnVisible()
{
	return this->ConnectBtn.IsVisible();
}

void Connect::SetBtnvisible(bool able)
{
	this->ConnectBtn.Enable(able);
}

std::wstring Connect::GetIP()
{
	return this->IP.GetText();
}

std::wstring Connect::GetPORT()
{
	return this->PORT.GetText();
}

Connect::~Connect()
{
	
}


