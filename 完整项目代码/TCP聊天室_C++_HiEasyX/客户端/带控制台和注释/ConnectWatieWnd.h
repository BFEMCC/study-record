#pragma once
#include "HiEasyX/HiEasyX.h"
class ConnectWatieWnd
{
private:
    hiex::Window wnd;
    hiex::Canvas can;
    LPCTSTR tip1 = L"连接中，请稍后...";
    LPCTSTR tip2 = L"连接成功后本窗口自动关闭";
    LPCTSTR tip3 = L"连接成功！";
    LPCTSTR tip4 = L"1秒后本窗口自动关闭";

public:
    void init(HWND hwnd = nullptr);
    void closewnd();
    bool iswndalive();
    void drawwaite();
    void drawsuccsee();
    ~ConnectWatieWnd();
};

