#include "clientsocket.h"
//severIP:服务端IP地址,severPort:服务端端口号
CClientSocket::CClientSocket(const char *severIp, int severPort)
{
    m_severSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(m_severSocket == -1)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in severAddr;
    severAddr.sin_family = AF_INET;
    severAddr.sin_port = htons(severPort);
    severAddr.sin_addr.s_addr = inet_addr(severIp);
    if(connect(m_severSocket, (sockaddr *)&severAddr, sizeof(severAddr)) == -1)
    {
        perror("connect");
        close(m_severSocket);
        exit(1);
    }
}

//重新连接服务器
bool CClientSocket::Connect(const char *severIp, int severPort)
{
    if(m_severSocket == -1)
    {
        if(m_severSocket = socket(AF_INET, SOCK_STREAM, 0) == -1)
        {
            return false;
        }
    }

    struct sockaddr_in severAddr;
    severAddr.sin_family = AF_INET;
    severAddr.sin_port = htons(severPort);
    severAddr.sin_addr.s_addr = inet_addr(severIp);
    if(connect(m_severSocket, (struct sockaddr*)&severAddr, sizeof(m_severSocket)) == -1)
    {
        perror("connect");
        close(m_severSocket);
        m_severSocket = -1;
        return false;
    }
    else
    {
        return true;
    }
    
}

 //发送信息
int CClientSocket::Send(void *buffer, size_t bufferLength)
{
    if(m_severSocket == -1)
    {
        return -1;
    }
    else
    {
        return send(m_severSocket, buffer, bufferLength, 0);
    }
}

//接收信息
int CClientSocket::Recv(void *buffer, size_t bufferLength)
{
    if(m_severSocket == -1)
    {
        return -1;
    }
    else
    {
        return recv(m_severSocket, buffer, bufferLength, 0);
    }
}