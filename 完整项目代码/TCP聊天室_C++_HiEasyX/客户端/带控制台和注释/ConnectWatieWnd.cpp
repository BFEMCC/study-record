#include "ConnectWatieWnd.h"

void ConnectWatieWnd::init(HWND hwnd)
{
    wnd.Create(200, 100, EX_NOMINIMIZE | EX_NOCLOSE, L"ÌáÊ¾", nullptr, hwnd);
    can.InIt(250, 180, RGB(240, 240, 240));
    can.Clear();
    wnd.BindCanvas(&can);
}

void ConnectWatieWnd::closewnd()
{
    this->wnd.CloseWindow();
}

bool ConnectWatieWnd::iswndalive()
{
    return this->wnd.IsAlive();
}

void ConnectWatieWnd::drawwaite()
{
    can.SetTextStyle(20, 0, L"Î¢ÈíÑÅºÚ");
    can.OutTextXY(((200 - textwidth(tip1)) / 2), ((100 - textheight(tip1)) / 2 - 30), tip1, true, BLACK);
    can.OutTextXY(((200 - textwidth(tip2)) / 2), ((100 - textheight(tip2)) / 2), tip2, true, BLACK);
    wnd.Redraw();
}

void ConnectWatieWnd::drawsuccsee()
{
    can.Clear();
    can.SetTextStyle(20, 0, L"Î¢ÈíÑÅºÚ");
    can.OutTextXY(((200 - textwidth(tip3)) / 2), ((100 - textheight(tip3)) / 2 - 30), tip3, true, BLACK);
    can.OutTextXY(((200 - textwidth(tip4)) / 2), ((100 - textheight(tip4)) / 2), tip4, true, BLACK);
    wnd.Redraw();
    Sleep(1000);
}

ConnectWatieWnd::~ConnectWatieWnd()
{
}
