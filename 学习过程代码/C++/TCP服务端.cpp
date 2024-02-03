#include<iostream>
#include<winsock.h>
#include<windows.h>
#pragma comment(lib,"ws2_32.lib")
int main()
{
    SOCKET TcpSocket;           //socket
    struct sockaddr_in Addr;    //服务器地址簇
    char recv_buf[1024]{ 0 };   //接收数组
    //1、加载网络库
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cout << "Windows网络库初始化失败！错误码：" << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }
    //2、创建socket
    TcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SOCKET_ERROR == TcpSocket)
    {
        WSACleanup();
        std::cout << " 创建socket错误！错误码：" << GetLastError() << std::endl;
        return -1;
    }
    //3、确定服务器地址簇
    memset(&Addr, 0, sizeof(struct sockaddr_in));
    Addr.sin_family = AF_INET;
    Addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    Addr.sin_port = htons(32119);
    //4、绑定
    if (SOCKET_ERROR == bind(TcpSocket, (sockaddr*)&Addr, sizeof(Addr)))
    {
        closesocket(TcpSocket);
        WSACleanup();
        std::cout << "绑定错误，错误码：" << GetLastError() << std::endl;
        return -1;
    }
    //5、监听
    if (SOCKET_ERROR == listen(TcpSocket, 10))
    {
        closesocket(TcpSocket);
        WSACleanup();
        std::cout << "监听错误，错误码：" << GetLastError() << std::endl;
        return -1;
    }
    std::cout << "监听成功" << std::endl;

    //6、接受连接

    SOCKET ClientSocket; //客户端socket

    while (1)
    {
        ClientSocket = accept(TcpSocket, NULL, NULL);
        if (ClientSocket > 0)
        {
            std::cout << "客户端连接" <<std::endl;
            break;
        }
    }
    //7、等待客户端发送消息
    while (1)
    {
        if (0 <= recv(ClientSocket, recv_buf, 1023, 0))
            std:: cout << "接收到客户端发送的消息：" << recv_buf << std::endl;
    }
    WSACleanup();
    return 0;
}
