#include <winsock.h>
#include <windows.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

int main()
{
    SOCKET TcpSocket;        // socket
    struct sockaddr_in Addr; // 服务器地址簇
    char buf[1024];          // 发送数组

    // 1、加载网络库
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cout << "Windows网络库初始化失败！错误码：" << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }

    // 2、创建socket
    TcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SOCKET_ERROR == TcpSocket)
    {
        WSACleanup();
        std::cout << " 创建socket错误！错误码：" << GetLastError() << std::endl;
        return -1;
    }

    // 3、确定服务器地址簇
    memset(&Addr, 0, sizeof(struct sockaddr_in));
    Addr.sin_family = AF_INET;
    Addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // 本地换回地址
    Addr.sin_port = htons(32119);

    // 4、连接服务器
    int r = connect(TcpSocket, (struct sockaddr*)&Addr, sizeof(struct sockaddr_in));
    if (r == -1)
    {
        closesocket(TcpSocket);
        WSACleanup();
        std::cout << "连接服务器错误，错误码：" << GetLastError() << std::endl;
        return -1;
    }
    std::cout << "连接服务器成功！" << std::endl;

    // 5、输入，发送给服务端
    while (1)
    {
        std::cout << "请输入要发送的内容：";
        std::cin >> buf;
        send(TcpSocket, buf, (size_t)strlen(buf), 0);
        memset(buf, 0, sizeof(buf));
    }

    // 6、关闭socket和网络库
    closesocket(TcpSocket);
    WSACleanup();
    return 0;
}
