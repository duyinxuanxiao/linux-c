#ifndef _SEVERSOCKET_H_
#define _SEVERSOCKET_H_

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class CSeverSocket
{
    public:
    //port默认8000, backlog默认5,完成socket,bind,listen
    CSeverSocket(int port = 5051, int backlog = 5);
    ~CSeverSocket();

    //接收请求,成功返回true否则false,会自动close上次accept的socket
    bool Accept();

    //发送接收函数,返回读写字节数
    int Send(const void *buffer, size_t length);
    int Recv(void *buffer, size_t length);

    //输出服务端,客户端地址,端口信息
    void PrintSeverAddr();
    void PrintClientAddr();

    //返回accept了多少个socket
    int GetClientCount() const
    {
        return m_clientCount;
    }
    //在子进程中关闭服务端socket
    void CloseSocket()
    {
        close(m_listenSocket);
        m_listenSocket = -1;
    }
    //在父进程中关闭客户端socket,不用刻意调用
    void CloseClientSocket()
    {
        if(m_clientSocket != -1)
        {
            close(m_clientSocket);
            m_clientSocket = -1;
        }
    }

    private:
    int m_listenSocket;  //监听套接字
    int m_clientSocket;  //客户端套接字
    int m_clientCount;   //accept了多少个客户端套接字
    struct sockaddr_in m_severAddr, m_clientAddr;  //服务端,客户端地址信息

};


#endif
