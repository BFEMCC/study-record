#pragma once
#include "HiEasyX/HiEasyX.h"
class ConnectWatieWnd
{
private:
    hiex::Window wnd;
    hiex::Canvas can;
    LPCTSTR tip1 = L"�����У����Ժ�...";
    LPCTSTR tip2 = L"���ӳɹ��󱾴����Զ��ر�";
    LPCTSTR tip3 = L"���ӳɹ���";
    LPCTSTR tip4 = L"1��󱾴����Զ��ر�";

public:
    void init(HWND hwnd = nullptr);
    void closewnd();
    bool iswndalive();
    void drawwaite();
    void drawsuccsee();
    ~ConnectWatieWnd();
};

