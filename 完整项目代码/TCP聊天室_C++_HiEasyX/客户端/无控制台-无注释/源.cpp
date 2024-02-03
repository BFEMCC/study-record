#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <regex>
#include <string>
#include <fstream>
#include <Windows.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <locale>
#include <codecvt>
#include <io.h>
#include"HiEasyX.h"
#include"resource.h"
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib,"ws2_32.lib")
class Connect
{
private:
    hiex::Window ConnectWnd;
    hiex::SysEdit IP;
    hiex::SysEdit PORT;
    hiex::SysButton ConnectBtn;
public:
    Connect()
    {
        hiex::SetCustomIcon(((LPWSTR)((ULONG_PTR)((WORD)(101)))), ((LPWSTR)((ULONG_PTR)((WORD)(101)))));
        this->ConnectWnd.Create(180, 150, 4 | 1, L"连接服务器");
        this->IP.PreSetStyle({ false, false, false, false, false, true });
        this->IP.Create(this->GetHandle(), 10, 10, 160, 25, L"在此输入服务器地址");
        this->IP.SetFont(20, 0, L"微软雅黑");
        this->IP.SetMaxTextLength(15);
        this->IP.NumberOnly(false);
        this->PORT.PreSetStyle({ false, false, false, false, false, true });
        this->PORT.Create(this->GetHandle(), 10, 45, 160, 25, L"在此输入服务器端口");
        this->PORT.SetFont(20, 0, L"微软雅黑");
        this->PORT.SetMaxTextLength(5);
        this->PORT.NumberOnly(true);
        this->ConnectBtn.Create(this->GetHandle(), 50, 85, 80, 30, L"连接");
        this->ConnectBtn.SetFont(20, 0, L"微软雅黑");
    }
    HWND GetHandle()
    {
        return this->ConnectWnd.GetHandle();
    }
    bool IsWndAlive()
    {
        return this->ConnectWnd.IsAlive();
    }
    void UnAliveExit()
    {
        if (!this->IsWndAlive())
        {
            exit(2);
        }
    }
    void CloseWnd()
    {
        this->ConnectWnd.CloseWindow();
    }
    bool IsBtnClick()
    {
        return this->ConnectBtn.IsClicked();
    }
    bool IsBtnVisible()
    {
        return this->ConnectBtn.IsVisible();
    }
    void SetBtnvisible(bool able)
    {
        this->ConnectBtn.Enable(able);
    }
    std::wstring GetIP()
    {
        return this->IP.GetText();
    }
    std::wstring GetPORT()
    {
        return this->PORT.GetText();
    }
};
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
    void init(HWND hwnd = nullptr)
    {
        wnd.Create(200, 100, 4 | 2, L"提示", nullptr, hwnd);
        can.InIt(250, 180, ((COLORREF)(((BYTE)(240) | ((WORD)((BYTE)(240)) << 8)) | (((DWORD)(BYTE)(240)) << 16))));
        can.Clear();
        wnd.BindCanvas(&can);
    }
    void closewnd()
    {
        this->wnd.CloseWindow();
    }
    bool iswndalive()
    {
        return this->wnd.IsAlive();
    }
    void drawwaite()
    {
        can.SetTextStyle(20, 0, L"微软雅黑");
        can.OutTextXY(((200 - textwidth(tip1)) / 2), ((100 - textheight(tip1)) / 2 - 30), tip1, true, 0);
        can.OutTextXY(((200 - textwidth(tip2)) / 2), ((100 - textheight(tip2)) / 2), tip2, true, 0);
        wnd.Redraw();
    }
    void drawsuccsee()
    {
        can.Clear();
        can.SetTextStyle(20, 0, L"微软雅黑");
        can.OutTextXY(((200 - textwidth(tip3)) / 2), ((100 - textheight(tip3)) / 2 - 30), tip3, true, 0);
        can.OutTextXY(((200 - textwidth(tip4)) / 2), ((100 - textheight(tip4)) / 2), tip4, true, 0);
        wnd.Redraw();
        Sleep(1000);
    }
};
WSADATA wsaData;
wchar_t ErrorMessage[128];
SOCKET TcpSocket;
struct sockaddr_in Addr;
std::wstring WSTRIP = L"";
std::string STRIP = "";
const char* CHARIP = nullptr;
unsigned long IP = 0;
int PORT = 0;
int ConnectRes = -1;
char recv_buf[1024] = {};
DWORD RecvThread;
HANDLE hThread = 0;
bool ConnectStatus = false;
std::ofstream filew;
std::ifstream filer;
std::ofstream filed;
int EptyLength1 = 0;
int EptyLength2 = 0;
std::wstring SendWstr = L"";
std::string SendStr = "";
int SendLength = 0;
std::string SocketIP = "";
std::string strrecv = "";
std::wstring wsrtrecv = L"";
const char* CharSend = nullptr;
struct RecvThreadParameter
{
    SOCKET Tcpsocket;
    hiex::Window wnd;
    hiex::SysEdit recvedit;
    hiex::SysEdit sendedit;
    hiex::SysButton ExitBtn;
    hiex::SysButton SaveAndExit;
    hiex::SysButton ClearHistory;
};
std::string charToString(char* charArray)
{
    std::string str(charArray);
    return str;
}
bool wstrToint(std::wstring str, int* intstr)
{
    wchar_t* end = nullptr;
    *intstr = std::wcstol(str.c_str(), &end, 10);
    if (end == str.c_str() + str.size())
    {
        return true;
    }
    return false;
}
std::wstring charTowstring(char* charstr)
{
    std::string str = charstr;
    std::wstring result;
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
    if (len < 0)return result;
    wchar_t* buffer = new wchar_t[len + 1];
    if (buffer == NULL)return result;
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
    buffer[len] = '\0';
    result.append(buffer);
    delete[] buffer;
    return result;
}
std::wstring stringTowstring(std::string str)
{
    std::wstring result;
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
    if (len < 0)return result;
    wchar_t* buffer = new wchar_t[len + 1];
    if (buffer == NULL)return result;
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
    buffer[len] = '\0';
    result.append(buffer);
    delete[] buffer;
    return result;
}
std::string wstringTostring(std::wstring wstr)
{
    std::string result;
    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
    if (len <= 0)return result;
    char* buffer = new char[len + 1];
    if (buffer == NULL)return result;
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
    buffer[len] = '\0';
    result.append(buffer);
    delete[] buffer;
    return result;
}
std::string GetCurrentTimeStr()
{
    SYSTEMTIME sys_time;
    GetLocalTime(&sys_time);
    char time_str[30];
    sprintf_s(time_str, "[%04d/%02d/%02d_%02d:%02d:%02d]", sys_time.wYear, sys_time.wMonth, sys_time.wDay, sys_time.wHour, sys_time.wMinute, sys_time.wSecond);
    std::string str_time(time_str);
    return (str_time);
}
std::string GetClientInfo(SOCKET sock)
{
    sockaddr_in client_addr;
    int addr_len = sizeof(client_addr);
    getpeername(sock, (sockaddr*)&client_addr, &addr_len);
    char* ip_str = inet_ntoa(client_addr.sin_addr);
    int port = ntohs(client_addr.sin_port);
    std::string client_info = "[" + std::string(ip_str) + "_" + std::to_string(port) + "]";
    return client_info;
}
std::string getLocalSocketAddrName(int socketFd)
{
    sockaddr_in SocketAddr;
    socklen_t nLen = sizeof(SocketAddr);
    memset(&SocketAddr, 0, sizeof(SocketAddr));
    int nRet = getsockname(socketFd, reinterpret_cast<sockaddr*>(&SocketAddr), &nLen);
    if (nRet == 0)
    {
        uint32_t ip = ntohl(SocketAddr.sin_addr.s_addr);
        uint16_t port = ntohs(SocketAddr.sin_port);
        char strIp[20];
        snprintf(strIp, sizeof(strIp), "%d.%d.%d.%d",
            static_cast<unsigned char>((ip >> 24) & 0xFF),
            static_cast<unsigned char>((ip >> 16) & 0xFF),
            static_cast<unsigned char>((ip >> 8) & 0xFF),
            static_cast<unsigned char>(ip & 0xFF));
        std::string result(strIp);
        result += "_";
        result += std::to_string(port);
        result = "[" + result + "]";
        return result;
    }
    else
    {
        return "";
    }
}
bool is_valid_ip(const std::wstring& ip)
{
    std::wregex pattern(L"^(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})$");
    std::wsmatch matches;
    if (regex_match(ip, matches, pattern))
    {
        for (int i = 1; i <= 4; i++)
        {
            int num = stoi(matches[i]);
            if (num < 0 || num > 255)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
void closeOperations(bool closeFile, bool closeThread, bool cleanInt, bool exitProgram)
{
    if (closeFile)
    {
        if (filew.is_open())
        {
            filew.close();
        }
        if (filer.is_open())
        {
            filer.close();
        }
    }

    if (closeThread && hThread != NULL)
    {
        CloseHandle(hThread);
    }

    if (cleanInt)
    {
        closesocket(TcpSocket);
        WSACleanup();
    }

    if (exitProgram)
    {
        exit(0);
    }
}
void __stdcall ThreadRecv(LPVOID lpParameter)
{
    RecvThreadParameter* parameter = (RecvThreadParameter*)lpParameter;
    int RecvLen = 0;
    while (true)
    {
        RecvLen = 0;
        memset(recv_buf, 0, sizeof(recv_buf));
        RecvLen = recv(parameter->Tcpsocket, recv_buf, 1024, 0);
        if (RecvLen > 0)
        {
            while (true)
            {
                if (!filew.is_open() && !filer.is_open())
                {
                    filew.open("ChatHistory.txt", std::ios::app);
                    if (!filew.is_open())
                    {
                        MessageBox(parameter->wnd.GetHandle(), L"系统错误，文件操作失败\n程序可继续运行，但不会显示和保存历史消息", L"错误", MB_OK | MB_ICONERROR);
                        parameter->recvedit.SetText(charTowstring(recv_buf));
                        break;
                    }
                    else
                    {
                        strrecv = "";
                        strrecv = GetCurrentTimeStr() + "_" + getLocalSocketAddrName(TcpSocket) + "_[接收_来自]_" + GetClientInfo(TcpSocket) + " >>：" + charToString(recv_buf);
                        filew << strrecv << std::endl;
                        filew.close();
                        Sleep(100);
                        while (true)
                        {
                            if (!filew.is_open() && !filer.is_open())
                            {
                                filer.open("ChatHistory.txt", std::ios::in);
                                if (!filer.is_open())
                                {
                                    MessageBox(parameter->wnd.GetHandle(), L"系统错误，文件操作失败\n历史消息已保存，程序可继续运行，但不会显示历史消息", L"错误", MB_OK | MB_ICONERROR);
                                    parameter->recvedit.SetText(charTowstring(recv_buf));
                                    break;
                                }
                                else
                                {
                                    wsrtrecv = L"";
                                    while (std::getline(filer, strrecv))
                                    {
                                        wsrtrecv += stringTowstring(strrecv);
                                        wsrtrecv += L"\r\n";
                                    }
                                    filer.close();
                                    parameter->recvedit.SetText(wsrtrecv);
                                    break;
                                }
                            }
                            Sleep(5);
                        }
                        break;
                    }
                }
                Sleep(5);
            }
            continue;
        }
        else
        {
            ConnectStatus = false;
            closeOperations(true, false, false, false);
            return;
        }
    }
}

int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ int nCmdShow)
{
    if (WSAStartup(((WORD)(((BYTE)(((DWORD_PTR)(2)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(2)) & 0xff))) << 8)), &wsaData) != 0)
    {
        memset(ErrorMessage, 0, sizeof(ErrorMessage));
        swprintf_s(ErrorMessage, L"Windows网络库初始化失败！错误码：%d", WSAGetLastError());
        MessageBoxW(nullptr, ErrorMessage, L"错误", 0x00000000L | 0x00000010L);
        exit(-1);
    }
lab2:
    TcpSocket = socket(2, 1, IPPROTO_TCP);
    if ((-1) == TcpSocket)
    {
        WSACleanup();
        memset(ErrorMessage, 0, sizeof(ErrorMessage));
        swprintf_s(ErrorMessage, L"套接字创建失败！错误码：%d", GetLastError());
        MessageBoxW(nullptr, ErrorMessage, L"错误", 0x00000000L | 0x00000010L);
        exit(-1);
    }
    Connect CWnd;
lab1:
    WSTRIP = L"";
    CHARIP = nullptr;
    IP = 0;
    PORT = 0;
    memset(&Addr, 0, sizeof(struct sockaddr_in));
    CWnd.SetBtnvisible(true);
    while (CWnd.IsWndAlive())
    {
        Sleep(50);
        CWnd.UnAliveExit();
        if (CWnd.IsBtnClick() && CWnd.IsBtnVisible())
        {
            CWnd.SetBtnvisible(false);
            WSTRIP = CWnd.GetIP();
            if (is_valid_ip(WSTRIP))
            {
                STRIP = wstringTostring(WSTRIP);
                CHARIP = STRIP.c_str();
                IP = inet_addr(CHARIP);
                if (wstrToint(CWnd.GetPORT(), &PORT) && IP != 0xffffffff)
                {
                    Addr.sin_family = 2;
                    Addr.sin_addr.S_un.S_addr = IP;
                    Addr.sin_port = htons(PORT);
                    break;
                }
                else
                {
                    MessageBoxW(CWnd.GetHandle(), L"请输入正确的端口号", L"错误", 0x00000000L | 0x00000010L);
                    CWnd.SetBtnvisible(true);
                    continue;
                }
            }
            else
            {
                MessageBoxW(CWnd.GetHandle(), L"请输入正确的IP地址", L"错误", 0x00000000L | 0x00000010L);
                CWnd.SetBtnvisible(true);
                continue;
            }
        }
    }
    ConnectWatieWnd WWnd;
    WWnd.init(CWnd.GetHandle());
    ConnectRes = -1;
    ConnectStatus = false;
    while (CWnd.IsWndAlive())
    {
        Sleep(50);
        WWnd.drawwaite();
        while (WWnd.iswndalive())
        {
            Sleep(50);
            ConnectRes = connect(TcpSocket, (sockaddr*)&Addr, sizeof(Addr));
            if (ConnectRes == 0)
            {
                ConnectStatus = true;
                WWnd.drawsuccsee();
                WWnd.closewnd();
                CWnd.CloseWnd();
            }
            else
            {
                ConnectStatus = true;
                WWnd.closewnd();
                memset(ErrorMessage, 0, sizeof(ErrorMessage));
                swprintf_s(ErrorMessage, L"连接失败！错误码：%d", WSAGetLastError());
                MessageBoxW(CWnd.GetHandle(), ErrorMessage, L"错误", 0x00000000L | 0x00000010L);
                goto lab1;
            }
        }
    }
    hiex::Window mainwnd(800, 640, 4, L"收&发消息");
    hiex::SysEdit RecvEdit;
    RecvEdit.PreSetStyle({ true, false, true, false, false, false, });
    RecvEdit.Create(mainwnd.GetHandle(), 10, 10, 790, 300);
    RecvEdit.SetFont(20, 0, L"微软雅黑");
    RecvEdit.ReadOnly(true);
    hiex::SysEdit SendEdit;
    SendEdit.PreSetStyle({ true, false, true, true, false, false, });
    SendEdit.Create(mainwnd.GetHandle(), 10, 320, 790, 150);
    SendEdit.SetFont(20, 0, L"微软雅黑");
    SendEdit.SetText(L"");
    SendEdit.SetMaxTextLength(1020);
    EptyLength1 = SendEdit.GetTextLength();
    EptyLength2 = SendEdit.GetText().length();
    hiex::SysButton SendBtn;
    SendBtn.Create(mainwnd.GetHandle(), 680, 490, 100, 30, L"发 送");
    SendBtn.SetFont(20, 0, L"微软雅黑");
    hiex::SysButton ExitBtn;
    ExitBtn.Create(mainwnd.GetHandle(), 580, 490, 100, 30, L"退 出");
    ExitBtn.SetFont(20, 0, L"微软雅黑");
    hiex::SysButton SaveAndExit;
    SaveAndExit.Create(mainwnd.GetHandle(), 480, 490, 100, 30, L"保存并退出");
    SaveAndExit.SetFont(20, 0, L"微软雅黑");
    hiex::SysButton ClearHistory;
    ClearHistory.Create(mainwnd.GetHandle(), 380, 490, 100, 30, L"清空聊天记录");
    ClearHistory.SetFont(20, 0, L"微软雅黑");
    hiex::SysButton DeleteChatLogFile;
    DeleteChatLogFile.Create(mainwnd.GetHandle(), 280, 490, 100, 30, L"删除记录文件");
    DeleteChatLogFile.SetFont(20, 0, L"微软雅黑");
    hiex::SysGroupBox BtnArea;
    BtnArea.Create(mainwnd.GetHandle(), 270, 470, 520, 60);
    BtnArea.SetFont(18, 0, L"微软雅黑");
    BtnArea.SetText(L"功能区");
    hiex::SysEdit Developer;
    Developer.PreSetStyle({ true, false, false, false, false, false, });
    Developer.Create(mainwnd.GetHandle(), 10, 478, 255, 105);
    Developer.SetFont(16, 0, L"微软雅黑");
    Developer.SetText(L"B站主页：https://b23.tv/vLGKBCp\r\n邮箱：A1840025658@outlook.com\r\nGitHub：\r\nhttps://github.com/BFEMCC/LAN-Chat-Client.git\r\nGitee：\r\nhttps://gitee.com/happy_emcc/lan-chat-client.git");
    Developer.ReadOnly(true);
    hiex::SysStatic Tips;
    Tips.Create(mainwnd.GetHandle(), 10, 587, 230, 60);
    Tips.SetFont(18, 0, L"微软雅黑");
    Tips.SetText(L"版本：1.3\r\n感谢使用，期待关注！\r\n本软件完全免费！若您收费获得请举报商家");
    RecvThreadParameter parameter = { TcpSocket, mainwnd, RecvEdit, SendEdit, ExitBtn, SaveAndExit, ClearHistory };
    hThread = CreateThread((LPSECURITY_ATTRIBUTES)0, 0, (LPTHREAD_START_ROUTINE)ThreadRecv, (LPVOID)&parameter, (DWORD)0, &RecvThread);
    if (hThread == 0)
    {
        memset(ErrorMessage, 0, sizeof(ErrorMessage));
        swprintf_s(ErrorMessage, L"系统错误\n线程创建失败！错误码：%d\n请尝试重新运行程序", GetLastError());
        MessageBoxW(mainwnd.GetHandle(), ErrorMessage, L"错误", 0x00000000L | 0x00000010L);
        mainwnd.CloseWindow();
        closesocket(TcpSocket);
        WSACleanup();
        exit(-1);
    }
    SocketIP = getLocalSocketAddrName(TcpSocket);
    while (mainwnd.IsAlive())
    {
        Sleep(50);
        if (ConnectStatus == false && hThread != 0)
        {
            CloseHandle(hThread);
            hThread = 0;
            MessageBoxW(mainwnd.GetHandle(), L"与服务器断开连接", L"提示", 0x00000000L | 0x00000010L);
            Sleep(500);
            if (MessageBoxW(mainwnd.GetHandle(), L"是否保存聊天记录？", L"提示", 0x00000001L | 0x00000030L) != 1)
            {
                filed.open("ChatHistory.txt", std::ofstream::trunc);
                filed.close();
                closeOperations(true, false, false, false);
            }
            mainwnd.CloseWindow();
            closesocket(TcpSocket);
            goto lab2;
        }
        if (SendBtn.IsClicked())
        {
            if (EptyLength1 == SendEdit.GetTextLength() || EptyLength2 == SendEdit.GetText().length())
            {
                MessageBoxW(mainwnd.GetHandle(), L"不可发送空内容！", L"警告", 0x00000000L | 0x00000010L);
                continue;
            }
            if (EptyLength1 != SendEdit.GetTextLength() && EptyLength2 != SendEdit.GetText().length())
            {
                SendWstr = SendEdit.GetText();
                SendStr = wstringTostring(SendWstr);
                CharSend = SendStr.c_str();
                SendLength = send(TcpSocket, CharSend, strlen(CharSend), 0);
                if ((-1) == SendLength || SendLength == 0)
                {
                    memset(ErrorMessage, 0, sizeof(ErrorMessage));
                    swprintf_s(ErrorMessage, L"发送失败！错误码：%d", WSAGetLastError());
                    MessageBoxW(mainwnd.GetHandle(), ErrorMessage, L"错误", 0x00000000L | 0x00000010L);
                    continue;
                }
                else
                {
                    SendEdit.SetText(L"");
                    SendStr = GetCurrentTimeStr() + "_" + SocketIP + "_[向]_[" + CHARIP + "_" + std::to_string(PORT) + "]_[发送]>>：" + wstringTostring(SendWstr);
                    while (true)
                    {
                        if (!filew.is_open() && !filer.is_open())
                        {
                            filew.open("ChatHistory.txt", std::ios::app);
                            if (!filew.is_open())
                            {
                                MessageBoxW(mainwnd.GetHandle(), L"系统错误，文件操作失败\n程序可继续运行，但不会显示和保存历史消息", L"错误", 0x00000000L | 0x00000010L);
                                RecvEdit.SetText(stringTowstring(SendStr));
                                break;
                            }
                            else
                            {
                                filew << SendStr << std::endl;
                                filew.close();
                                Sleep(100);
                                while (true)
                                {
                                    if (!filew.is_open() && !filer.is_open())
                                    {
                                        filer.open("ChatHistory.txt", std::ios::in);
                                        if (!filer.is_open())
                                        {
                                            MessageBoxW(mainwnd.GetHandle(), L"系统错误，文件操作失败\n历史消息已保存，程序可继续运行，但不会显示历史消息", L"错误", 0x00000000L | 0x00000010L);
                                            RecvEdit.SetText(stringTowstring(SendStr));
                                            break;
                                        }
                                        else
                                        {
                                            strrecv = "";
                                            wsrtrecv = L"";
                                            while (std::getline(filer, strrecv))
                                            {
                                                wsrtrecv += stringTowstring(strrecv);
                                                wsrtrecv += L"\r\n";
                                            }
                                            filer.close();
                                            RecvEdit.SetText(wsrtrecv);
                                            break;
                                        }
                                    }
                                    Sleep(5);
                                }
                                break;
                            }
                        }
                        Sleep(5);
                    }
                    continue;
                }
            }
        }
        if (ExitBtn.IsClicked())
        {
            if (MessageBoxW(mainwnd.GetHandle(), L"是否确认退出？", L"提示", 0x00000001L | 0x00000030L) == 1)
            {
                Sleep(50);
                if (_access("ChatHistory.txt", 0) == 0)
                {
                    if (MessageBoxW(mainwnd.GetHandle(), L"是否保存聊天记录？\r\n提示：已清空的记录不会保存", L"提示", 0x00000001L | 0x00000040L) == 1)
                    {
                        closeOperations(true, true, true, true);
                    }
                    closeOperations(true, true, true, false);
                    filed.open("ChatHistory.txt", std::ofstream::trunc);
                    filed.close();
                    exit(0);
                }
                closeOperations(true, true, true, true);
            }
            continue;
        }
        if (SaveAndExit.IsClicked())
        {
            if (MessageBoxW(mainwnd.GetHandle(), L"是否确认保存聊天记录并退出？", L"提示", 0x00000001L | 0x00000030L) == 1)
            {
                if (_access("ChatHistory.txt", 0) == 0)
                {
                    closeOperations(true, true, true, true);
                }
                else
                {
                    MessageBoxW(mainwnd.GetHandle(), L"记录文件不存在或已删除", L"提示", 0x00000000L | 0x00000030L);
                    exit(0);
                }
            }
            continue;
        }
        if (ClearHistory.IsClicked())
        {
            if (_access("ChatHistory.txt", 0) == 0)
            {
                if (MessageBoxW(mainwnd.GetHandle(), L"是否确认清空聊天记录？", L"提示", 0x00000001L | 0x00000030L) == 1)
                {
                    closeOperations(true, false, false, false);
                    filed.open("ChatHistory.txt", std::ofstream::trunc);
                    filed.close();
                    RecvEdit.SetText(L"");
                }
                continue;
            }
            else
            {
                MessageBoxW(mainwnd.GetHandle(), L"文件不存在或已删除", L"提示", 0x00000000L | 0x00000010L);
                continue;
            }
        }
        if (DeleteChatLogFile.IsClicked())
        {
            while (true)
            {
                if (!filew.is_open() && !filer.is_open())
                {
                    if (_access("ChatHistory.txt", 0) == 0)
                    {
                        if (MessageBoxW(mainwnd.GetHandle(), L"是否确认删除？", L"提示", 0x00000001L | 0x00000030L) == 1)
                        {
                            if (remove("ChatHistory.txt") == 0)
                            {
                                RecvEdit.SetText(L"");
                                MessageBoxW(mainwnd.GetHandle(), L"删除成功\r\n聊天记录文件已删除", L"提示", 0x00000000L | 0x00000040L);
                                break;
                            }
                            else
                            {
                                MessageBoxW(mainwnd.GetHandle(), L"删除失败\r\n文件不存在或已删除", L"提示", 0x00000000L | 0x00000010L);
                                break;
                            }
                        }
                        break;
                    }
                    else
                    {
                        MessageBoxW(mainwnd.GetHandle(), L"文件不存在或已删除", L"提示", 0x00000000L | 0x00000010L);
                        break;
                    }
                }
                Sleep(5);
            }
            continue;
        }
    }
    if (!mainwnd.IsAlive())
    {
        if (_access("ChatHistory.txt", 0) == 0)
        {
            if (MessageBoxW(nullptr, L"是否保存聊天记录？", L"提示", 0x00000001L | 0x00000040L) == 1)
            {
                closeOperations(true, true, true, true);
            }
            else
            {
                closeOperations(true, true, true, false);
                filed.open("ChatHistory.txt", std::ofstream::trunc);
                filed.close();
                exit(0);
            }
        }
        else
        {
            closeOperations(true, true, true, true);
        }
    }
}