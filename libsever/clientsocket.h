#ifndef _CLIENTSOCKET_H_
#define _CLIENTSOCKET_H_

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class CClientSocket
{
    public:
    //默认构造函数,初始化服务端socket
    CClientSocket() : m_severSocket(-1) { }

    //severIP:服务端IP地址,severPort:服务端端口号
    CClientSocket(const char *severIp, int severPort);

    ~CClientSocket()
    {
        if(m_severSocket != -1)
        {
            close(m_severSocket);
        }
    }
    
    //重新连接服务器
    bool Connect(const char *severIp, int severPort);

    //发送信息
    int Send(void *buffer, size_t bufferLength);
    //接收信息
    int Recv(void *buffer, size_t bufferLength);

    private:
    int m_severSocket;    //服务端socket
};


#endif