#include<cstdio>
#include<cstdlib>
#include<WinSock2.h>
#include<Windows.h>

#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

int main(int argc, char *argv[])
{
    //初始化DLL
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA wsdata;
    if (WSAStartup(sockVersion, &wsdata) != 0)
    {
        exit(-1);
    }
    //创建客户端socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket == INVALID_SOCKET)
    {
        printf("socket, error!\n");
        exit(-1);
    }
    //服务端地址信息数据结构
    sockaddr_in severAddr;
    severAddr.sin_family = AF_INET;
    severAddr.sin_port = htons(5051);
    severAddr.sin_addr.S_un.S_addr = inet_addr("192.168.31.105");
    //发出连接请求
    if(connect(clientSocket, (sockaddr *)&severAddr, sizeof(severAddr)) == SOCKET_ERROR)
    {
        printf("connect Error!\n");
        exit(-1);
    }

    const int bufferSize = 1024;
    char sendBuffer[bufferSize];
    char recvBuffer[bufferSize];

    for(int i = 0; i < 5; i++)
    {
        sprintf(sendBuffer, "这是第%d条信息。\n", i+1);
        send(clientSocket, sendBuffer, bufferSize, 0);
        recv(clientSocket, recvBuffer, bufferSize, 0);
        printf("收到sever信息：%s\n", recvBuffer);
    }
    closesocket(clientSocket);

    return 0;
}
