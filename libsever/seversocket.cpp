#include "seversocket.h"

CSeverSocket::CSeverSocket(int port, int backlog) 
    : m_clientCount(0), m_clientSocket(-1)
{
    m_listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(m_listenSocket == -1)
    {
        perror("socket");
        exit(1);
    }

    m_severAddr.sin_family = AF_INET;
    m_severAddr.sin_port = htons(port);
    m_severAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(m_listenSocket, (struct sockaddr *)&m_severAddr, sizeof(m_severAddr)) == -1)
    {
        perror("bind");
        close(m_listenSocket);
        exit(1);
    }

    if(listen(m_listenSocket, backlog) == -1)
    {
        perror("listen");
        close(m_listenSocket);
        exit(1);
    }
}

CSeverSocket::~CSeverSocket()
{
    if(m_listenSocket != -1)
    {
        close(m_listenSocket);
    }
    if(m_clientSocket != -1)
    {
        close(m_clientSocket);
    }
}

bool CSeverSocket::Accept()
{
    int len = sizeof(m_clientAddr);
    if(m_clientSocket != -1)
    {
        close(m_clientSocket);
    }
    m_clientSocket = accept(m_listenSocket, (struct sockaddr *)&m_clientAddr, (socklen_t *)&len);
    if(m_clientSocket <= 0)
    {
        return false;
    }
    else
    {
        m_clientCount++;
        return true;
    }
    
}

int CSeverSocket::Send(const void *buffer, size_t length)
{
    if(m_clientSocket == -1)
    {
        return -1;
    }
    else
    {
        return send(m_clientSocket, buffer, length, 0);
    }
    
    
}

int CSeverSocket::Recv(void *buffer, size_t length)
{
    if(m_clientSocket == -1)
    {
        return -1;
    }
    else
    {
        return recv(m_clientSocket, buffer, length, 0);
    }
    
}

void CSeverSocket::PrintSeverAddr()
{
    printf("%s:%hu", inet_ntoa(m_severAddr.sin_addr), ntohs(m_severAddr.sin_port));
}

void CSeverSocket::PrintClientAddr()
{
    if(m_clientCount > 0)
    {
        printf("%s:%hu", inet_ntoa(m_clientAddr.sin_addr), ntohs(m_clientAddr.sin_port));
    }
}
