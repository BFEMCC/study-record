#include "Connect.h"

Connect::Connect()
{
	this->ConnectWnd.Create(CWNDW, CWNDH, ONLYEXIT, CWNDTITLE);

	this->IP.PreSetStyle({ false, false, false, false, false, true });//设置预设样式
				//多行文本、文本居中、拥有垂直滚动条、自动垂直滚动、拥有水平滚动条、自动水平滚动
	this->IP.Create(this->GetHandle(), IPEDITX, IPEDITY, IPEDITW, IPEDITH, IPEDITTIP);//创建
	this->IP.SetFont(EDITFONTSIZE, 0, FONT);//设置字体字号
	this->IP.SetMaxTextLength(IPMAXLEN);//设置最大长度
	this->IP.NumberOnly(false);//限制是否仅数字

	this->PORT.PreSetStyle({ false, false, false, false, false, true });
	this->PORT.Create(this->GetHandle(), PORTEDITX, PORTEDITY, PORTEDITW, PORTEDITH, PORTEDITTIP);
	this->PORT.SetFont(EDITFONTSIZE, 0, FONT);
	this->PORT.SetMaxTextLength(PORTMAXLEN);
	this->PORT.NumberOnly(true);

	this->ConnectBtn.Create(this->GetHandle(), BTNX, BTNY, BTNW, BTNH, BTNTIP);//创建按钮
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


