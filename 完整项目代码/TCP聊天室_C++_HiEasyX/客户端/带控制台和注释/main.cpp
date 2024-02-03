//1.3更新
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MAX_BUF_SIZE 1024 
#define MIB_IF_TYPE_IEEE80211 71
#define VERSION L"版本：1.3"
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
#include"HiEasyX/HiEasyX.h"
#include"ConnectWatieWnd.h"
#include"Connect.h"
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib,"ws2_32.lib")

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
char recv_buf[MAX_BUF_SIZE] = {};
DWORD RecvThread;
HANDLE hThread = NULL;
bool ConnectStatus = false;
std::ofstream filew;
std::ifstream filer;
std::ofstream filed;
int EptyLength1 = 0;
int EptyLength2 = 0;
std::wstring SendWstr = L"";
std::string SendStr = "";
int SendLength = 0;
//std::string WifiIP = "";
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

std::string charToString(char* charArray);
//const char* wstrTochar(std::wstring& str);
bool wstrToint(std::wstring str, int* intstr);
std::wstring charTowstring(char* charstr);
std::wstring stringTowstring(std::string str);
std::string wstringTostring(std::wstring wstr);
std::string GetCurrentTimeStr();
std::string GetClientInfo(SOCKET sock);
//std::string getWirelessAdapterIPV4Address();
std::string getLocalSocketAddrName(int socketFd);
bool is_valid_ip(const std::wstring& ip);
void closeOperations(bool closeFile, bool closeThread, bool cleanInt, bool exitProgram);
void WINAPI ThreadRecv(LPVOID lpParameter);


int main()
{
    //1、加载网络库
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        memset(ErrorMessage, 0, sizeof(ErrorMessage));
        swprintf_s(ErrorMessage, L"Windows网络库初始化失败！错误码：%d", WSAGetLastError());
        MessageBox(nullptr, ErrorMessage, L"错误", MB_OK | MB_ICONERROR);
        exit(-1);
    }
lab2:
    //2、创建套接字
    TcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SOCKET_ERROR == TcpSocket)
    {
        WSACleanup();
        memset(ErrorMessage, 0, sizeof(ErrorMessage));
        swprintf_s(ErrorMessage, L"套接字创建失败！错误码：%d", GetLastError());
        MessageBox(nullptr, ErrorMessage, L"错误", MB_OK | MB_ICONERROR);
        exit(-1);
    }

    //3、设置服务器地址簇
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
        if (CWnd.IsBtnClick() && CWnd.IsBtnVisible())//窗口存在且点击按钮
        {
            CWnd.SetBtnvisible(false);
            WSTRIP = CWnd.GetIP();
            if ( is_valid_ip(WSTRIP))//ip地址合法
            {
                STRIP = wstringTostring(WSTRIP);
                CHARIP = STRIP.c_str();
                IP = inet_addr(CHARIP);
                if (wstrToint(CWnd.GetPORT(), &PORT) && IP != INADDR_NONE)//端口号转换成功，并且IP转换成功
                {
                    Addr.sin_family = AF_INET;
                    Addr.sin_addr.S_un.S_addr = IP;
                    Addr.sin_port = htons(PORT);
                    break;
                }
                else
                {
                    MessageBox(CWnd.GetHandle(), L"请输入正确的端口号", L"错误", MB_OK | MB_ICONERROR);
                    CWnd.SetBtnvisible(true);
                    continue;
                }
            }
            else
            {
                MessageBox(CWnd.GetHandle(), L"请输入正确的IP地址", L"错误", MB_OK | MB_ICONERROR);
                CWnd.SetBtnvisible(true);
                continue;
            }
        }
    }

    //4、连接服务器
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
            if (ConnectRes == 0)//连接服务器成功
            {
                ConnectStatus = true;
                WWnd.drawsuccsee();
                WWnd.closewnd();
                CWnd.CloseWnd();   
            }
            else//连接服务器失败
            {
                ConnectStatus = true;
                WWnd.closewnd();
                memset(ErrorMessage, 0, sizeof(ErrorMessage));
                swprintf_s(ErrorMessage, L"连接失败！错误码：%d", WSAGetLastError());
                MessageBox(CWnd.GetHandle(), ErrorMessage, L"错误", MB_OK | MB_ICONERROR);
                goto lab1;
            }
        }
    }

    //主界面UI
    hiex::Window mainwnd(800, 640, EX_NOMINIMIZE, L"收&发消息");

    hiex::SysEdit RecvEdit;
    RecvEdit.PreSetStyle({ true, false, true, false, false, false, });
    RecvEdit.Create(mainwnd.GetHandle(), 10, 10, 790, 300);
    RecvEdit.SetFont(20, 0, FONT);
    RecvEdit.ReadOnly(true);

    hiex::SysEdit SendEdit;
    SendEdit.PreSetStyle({ true, false, true, true, false, false, });
    SendEdit.Create(mainwnd.GetHandle(), 10, 320, 790, 150);
    SendEdit.SetFont(EDITFONTSIZE, 0, FONT);
    SendEdit.SetText(L"");
    SendEdit.SetMaxTextLength(MAX_BUF_SIZE - 4);
    EptyLength1 = SendEdit.GetTextLength();
    EptyLength2 = SendEdit.GetText().length();

    hiex::SysButton SendBtn;
    SendBtn.Create(mainwnd.GetHandle(), 680, 490, 100, 30, L"发 送");
    SendBtn.SetFont(BTNFONTSIZE, 0, FONT);

    hiex::SysButton ExitBtn;
    ExitBtn.Create(mainwnd.GetHandle(), 580, 490, 100, 30, L"退 出");
    ExitBtn.SetFont(BTNFONTSIZE, 0, FONT);

    hiex::SysButton SaveAndExit;
    SaveAndExit.Create(mainwnd.GetHandle(), 480, 490, 100, 30, L"保存并退出");
    SaveAndExit.SetFont(BTNFONTSIZE, 0, FONT);

    hiex::SysButton ClearHistory;
    ClearHistory.Create(mainwnd.GetHandle(), 380, 490, 100, 30, L"清空聊天记录");
    ClearHistory.SetFont(BTNFONTSIZE, 0, FONT);

    hiex::SysButton DeleteChatLogFile;
    DeleteChatLogFile.Create(mainwnd.GetHandle(), 280, 490, 100, 30, L"删除记录文件");
    DeleteChatLogFile.SetFont(BTNFONTSIZE, 0, FONT);

    hiex::SysGroupBox BtnArea;
    BtnArea.Create(mainwnd.GetHandle(), 270, 470, 520, 60);
    BtnArea.SetFont(18, 0, FONT);
    BtnArea.SetText(L"功能区");

    hiex::SysEdit Developer;
    Developer.PreSetStyle({ true, false, false, false, false, false, });
    Developer.Create(mainwnd.GetHandle(), 10, 478, 255, 105);
    Developer.SetFont(16, 0, FONT);
    Developer.SetText(
        L"B站主页：https://b23.tv/vLGKBCp\r\n"
        L"邮箱：A1840025658@outlook.com\r\n"
        L"GitHub:\r\n"
        L"https://github.com/BFEMCC/LAN-Chat-Client.git\r\n"
        L"Gitee:\r\n"
        L"https://gitee.com/happy_emcc/lan-chat-client.git");
    Developer.ReadOnly(true);
    hiex::SysStatic Tips;
    Tips.Create(mainwnd.GetHandle(), 10, 587, 230, 60);
    Tips.SetFont(18, 0, FONT);
    Tips.SetText(VERSION L"\r\n"
        L"感谢使用，期待关注！\r\n"
        L"本软件完全免费！若您收费获得请举报商家");

    //5、接收线程
    RecvThreadParameter parameter = { TcpSocket, mainwnd, RecvEdit, SendEdit, ExitBtn, SaveAndExit, ClearHistory };
    hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 0, (LPTHREAD_START_ROUTINE)ThreadRecv, (LPVOID)&parameter, (DWORD)0, &RecvThread);
    if (hThread == NULL) 
    {
        memset(ErrorMessage, 0, sizeof(ErrorMessage));
        swprintf_s(ErrorMessage, L"系统错误\n线程创建失败！错误码：%d\n请尝试重新运行程序", GetLastError());
        MessageBox(mainwnd.GetHandle(), ErrorMessage, L"错误", MB_OK | MB_ICONERROR);
        mainwnd.CloseWindow();
        closesocket(TcpSocket);
        WSACleanup();
        exit(-1);
    }

    //6、发送及其他功能
   // WifiIP = getWirelessAdapterIPV4Address();
    SocketIP = getLocalSocketAddrName(TcpSocket);
    while (mainwnd.IsAlive())
    {
        Sleep(50);
        if (ConnectStatus == false && hThread != NULL)//断开连接
        {
           CloseHandle(hThread);// 关闭线程句柄
           hThread = NULL;
           MessageBox(mainwnd.GetHandle(), L"与服务器断开连接", L"提示", MB_OK | MB_ICONERROR);
           Sleep(500);
           if (MessageBox(mainwnd.GetHandle(), L"是否保存聊天记录？", L"提示", MB_OKCANCEL | MB_ICONWARNING) != IDOK)
            {
                filed.open("ChatHistory.txt", std::ofstream::trunc);
                filed.close();
                closeOperations(true, false, false, false);
            }
           mainwnd.CloseWindow();
           closesocket(TcpSocket);
           goto lab2;
        }

        if (SendBtn.IsClicked())//点击发送按钮
        {
            if (EptyLength1 == SendEdit.GetTextLength() || EptyLength2 == SendEdit.GetText().length())
            {
                MessageBox(mainwnd.GetHandle(), L"不可发送空内容！", L"警告", MB_OK | MB_ICONERROR);
                continue;
            }
            if(EptyLength1 != SendEdit.GetTextLength() && EptyLength2 != SendEdit.GetText().length())
            {
                SendWstr = SendEdit.GetText();
                SendStr = wstringTostring(SendWstr);
                CharSend = SendStr.c_str();
                SendLength = send(TcpSocket, CharSend, strlen(CharSend), 0);
                if (SOCKET_ERROR == SendLength || SendLength == 0)
                {
                    memset(ErrorMessage, 0, sizeof(ErrorMessage));
                    swprintf_s(ErrorMessage, L"发送失败！错误码：%d", WSAGetLastError());
                    MessageBox(mainwnd.GetHandle(), ErrorMessage, L"错误", MB_OK | MB_ICONERROR);
                    continue;
                }
                else
                {
                    SendEdit.SetText(L"");
                    SendStr = GetCurrentTimeStr() + "_" + SocketIP + "_[向]_[" + CHARIP + "_" + std::to_string(PORT) + "]_[发送]>>：" + wstringTostring(SendWstr);
                    while (true)//等待文件关闭
                    {
                        if (!filew.is_open() && !filer.is_open())
                        {
                            filew.open("ChatHistory.txt", std::ios::app);
                            if (!filew.is_open())
                            {
                                MessageBox(mainwnd.GetHandle(),L"系统错误，文件操作失败\n程序可继续运行，但不会显示和保存历史消息", L"错误", MB_OK | MB_ICONERROR);
                                RecvEdit.SetText(stringTowstring(SendStr));
                                break;
                            }
                            else
                            {//打开成功，写入发送内容，保存聊天记录
                                filew << SendStr << std::endl;
                                filew.close();
                                Sleep(100);
                                while (true)//等待文件关闭
                                {
                                    if (!filew.is_open() && !filer.is_open())
                                    {
                                        filer.open("ChatHistory.txt", std::ios::in); // 打开文件，以读取的形式读取
                                        if (!filer.is_open()) // 如果文件打开失败
                                        {
                                            MessageBox(mainwnd.GetHandle(), L"系统错误，文件操作失败\n历史消息已保存，程序可继续运行，但不会显示历史消息", L"错误", MB_OK | MB_ICONERROR);
                                            RecvEdit.SetText(stringTowstring(SendStr));
                                            break;
                                        }
                                        else
                                        {
                                            strrecv = "";
                                            wsrtrecv = L"";
                                            while (std::getline(filer, strrecv)) // 逐行读取文件内容
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

        if (ExitBtn.IsClicked())//点击退出按钮
        {
            if (MessageBox(mainwnd.GetHandle(), L"是否确认退出？", L"提示", MB_OKCANCEL | MB_ICONEXCLAMATION) == IDOK)
            {
                Sleep(50);
                if (_access("ChatHistory.txt", 0) == 0)
                {
                    if (MessageBox(mainwnd.GetHandle(), L"是否保存聊天记录？\r\n提示：已清空的记录不会保存", L"提示", MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
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

        if (SaveAndExit.IsClicked())//点击保存并退出按钮
        {
            if (MessageBox(mainwnd.GetHandle(), L"是否确认保存聊天记录并退出？", L"提示", MB_OKCANCEL | MB_ICONEXCLAMATION) == IDOK)
            {
                if (_access("ChatHistory.txt", 0) == 0)
                {
                    closeOperations(true, true, true, true);
                }
                else
                {
                    MessageBox(mainwnd.GetHandle(), L"记录文件不存在或已删除", L"提示", MB_OK | MB_ICONEXCLAMATION);
                    exit(0);
                }
            }
            continue;
        }

        if (ClearHistory.IsClicked())//清空聊天记录
        {
            if (_access("ChatHistory.txt", 0) == 0)//如果文件存在
            {
                if (MessageBox(mainwnd.GetHandle(), L"是否确认清空聊天记录？", L"提示", MB_OKCANCEL | MB_ICONEXCLAMATION) == IDOK)
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
                MessageBox(mainwnd.GetHandle(), L"文件不存在或已删除", L"提示", MB_OK | MB_ICONERROR);
                continue;
            }
        }

        if (DeleteChatLogFile.IsClicked())//点击删除记录文件按钮
        {
            while (true)//等待文件关闭
            {
                if (!filew.is_open() && !filer.is_open())
                {
                    if (_access("ChatHistory.txt", 0) == 0)//如果记录存在
                    {
                        if (MessageBox(mainwnd.GetHandle(), L"是否确认删除？", L"提示", MB_OKCANCEL | MB_ICONEXCLAMATION) == IDOK)
                        {
                            if (remove("ChatHistory.txt") == 0)
                            {
                                RecvEdit.SetText(L"");
                                MessageBox(mainwnd.GetHandle(), L"删除成功\r\n聊天记录文件已删除", L"提示", MB_OK | MB_ICONINFORMATION);
                                break;
                            }
                            else
                            {
                                MessageBox(mainwnd.GetHandle(), L"删除失败\r\n文件不存在或已删除", L"提示", MB_OK | MB_ICONERROR);
                                break;
                            }
                        }
                        break;
                    }
                    else
                    {
                        MessageBox(mainwnd.GetHandle(), L"文件不存在或已删除", L"提示", MB_OK | MB_ICONERROR);
                        break;
                    }
                }
                Sleep(5);
            }
            continue;
        }
    }
    if (!mainwnd.IsAlive())//直接点x关闭窗口
    {
        if (_access("ChatHistory.txt", 0) == 0) //如果记录文件存在
        {
            if (MessageBox(nullptr, L"是否保存聊天记录？\r\n提示：已清空的记录不会保存", L"提示", MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
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
    return 0;
}

//char数组转string
std::string charToString(char* charArray) 
{
    std::string str(charArray);
    return str;
}

//wstring转char数组!!!!!//不安全，需要手动释放内存，容易泄露内存，并且无法转换中文
//const char* wstrTochar(std::wstring& str)
//{
//    size_t len = str.length() * 2 + 1;
//    const char* charstr = new const char[len] {0};
//    size_t converted = 0;
//    wcstombs_s(&converted, const_cast<char*>(charstr), len, str.c_str(), len);
//    return charstr;
//}

//仅数字的wstring转int //参数：需要转换的wstring，存储转换结果的int地址//返回值：bool是否转换成功
bool wstrToint(std::wstring str, int* intstr)
{
    /*如果end指向字符串的末尾，说明整个字符串都被成功转换了，转换成功。wstr.c_str()返回一个指向字符串首字符的指针，
    加上wstr.size()就是指向字符串的末尾。如果end不等于这个指针，说明有未能成功转换的字符，转换失败。*/
    wchar_t* end = nullptr;
    *intstr = std::wcstol(str.c_str(), &end, 10);//将wstring转换成int
    if (end == str.c_str() + str.size()) // 转换成功
    {
        return true;
    }
    return false;
}

//char数组转wstring
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

//string转wstring
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

//wstring转string
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

//获取本地时间
std::string GetCurrentTimeStr()
{
    SYSTEMTIME sys_time;
    GetLocalTime(&sys_time);
    char time_str[30];
    sprintf_s(time_str, "[%04d/%02d/%02d_%02d:%02d:%02d]", sys_time.wYear, sys_time.wMonth, sys_time.wDay, sys_time.wHour, sys_time.wMinute, sys_time.wSecond);
    std::string str_time(time_str);
    return (str_time);
}

//获取发送消息方的IP地址和端口信息
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

//获取本地无线局域网IP地址
//std::string getWirelessAdapterIPV4Address()
//{
//    std::string ipAddress = "";
//    PIP_ADAPTER_INFO pAdapterInfo;
//    PIP_ADAPTER_INFO pAdapter = NULL;
//    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
//    DWORD dwRetVal = 0;
//
//    pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
//    if (pAdapterInfo == NULL) 
//    {
//        return ipAddress;
//    }
//
//    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) 
//    {
//        free(pAdapterInfo);
//        pAdapterInfo = (IP_ADAPTER_INFO*)malloc(ulOutBufLen);
//        if (pAdapterInfo == NULL) 
//        {
//            return ipAddress;
//        }
//    }
//    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) 
//    {
//        pAdapter = pAdapterInfo;
//        while (pAdapter) {
//            if (pAdapter->Type == MIB_IF_TYPE_IEEE80211) 
//            {
//                IP_ADDR_STRING* pIpAddrString = &(pAdapter->IpAddressList);
//                while (pIpAddrString) {
//                    if (pIpAddrString->IpAddress.String[0] != '0') 
//                    {
//                        ipAddress = pIpAddrString->IpAddress.String;
//                        break;
//                    }
//                    pIpAddrString = pIpAddrString->Next;
//                }
//                break;
//            }
//            pAdapter = pAdapter->Next;
//        }
//    }
//
//    if (pAdapterInfo) {
//        free(pAdapterInfo);
//    }
//
//    return ipAddress;
//}

//获取软件运行时使用的的地址和端口
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

//正则判断ip地址是否合法
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

//关闭文件、线程、网络库、退出相关
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

//接收线程函数
void __stdcall ThreadRecv(LPVOID lpParameter)
{
    RecvThreadParameter* parameter = (RecvThreadParameter*)lpParameter;
    int RecvLen = 0;
    while (true)
    {
        RecvLen = 0;
        memset(recv_buf, 0, sizeof(recv_buf));
        RecvLen = recv(parameter->Tcpsocket, recv_buf, MAX_BUF_SIZE, 0);    //将接收到的消息存储在recv_buf里，是char型数组
        if (RecvLen > 0)
        {
            while (true)
            {
                if (!filew.is_open() && !filer.is_open())
                {
                    filew.open("ChatHistory.txt", std::ios::app); // 打开文件，以追加的形式写入
                    if (!filew.is_open()) // 如果文件打开失败
                    {
                        MessageBox(parameter->wnd.GetHandle(),L"系统错误，文件操作失败\n程序可继续运行，但不会显示和保存历史消息", L"错误", MB_OK | MB_ICONERROR);
                        parameter->recvedit.SetText(charTowstring(recv_buf));
                        break;
                    }
                    else
                    {
                        strrecv = "";
                        strrecv =GetCurrentTimeStr() +"_" + getLocalSocketAddrName(TcpSocket)+"_[接收_来自]_"+ GetClientInfo(TcpSocket) + " >>：" + charToString(recv_buf);
                        filew << strrecv << std::endl;//接收到的内容写入文件保存并换行
                        filew.close();
                        Sleep(100);
                        while (true)
                        {
                            if (!filew.is_open() && !filer.is_open())
                            {
                                filer.open("ChatHistory.txt", std::ios::in); // 打开文件，以读取的形式读取
                                if (!filer.is_open()) // 如果文件打开失败
                                {
                                    MessageBox(parameter->wnd.GetHandle(),L"系统错误，文件操作失败\n历史消息已保存，程序可继续运行，但不会显示历史消息", L"错误", MB_OK | MB_ICONERROR);
                                    parameter->recvedit.SetText(charTowstring(recv_buf));
                                    break;
                                }
                                else
                                {
                                    wsrtrecv = L"";
                                    while (std::getline(filer, strrecv)) // 逐行读取文件内容
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
        else//断开连接
        {
            ConnectStatus = false;
            closeOperations(true, false, false, false);
            return;
        }
    }
}
