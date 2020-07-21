#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<sys/socket.h>
#include<sys/types.h>

#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	//创建客户端socket
	int sockFd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockFd == -1)
	{
		perror("socket");
		exit(-1);
	}
	
	//服务端地址
	struct hostent *h = gethostbyname("192.168.31.105");
	if(h == NULL)
	{
		perror("gethostbyname");
		close(sockFd);
		exit(-1);
	}
	//服务端地址信息数据结构
	struct sockaddr_in severAddr;
	memset(&severAddr, 0, sizeof(severAddr));
	severAddr.sin_family = AF_INET;
	severAddr.sin_port = htons(5051);
	memcpy(&severAddr.sin_addr, h->h_addr, h->h_length);
	
	//向服务端发起连接清求
	if(connect(sockFd, (struct sockaddr*)&severAddr, sizeof(severAddr)) != 0)
	{
		perror("connect");
		close(sockFd);
		exit(-1);
	}
	
	int bufferSize = 1024;
	char buffer[bufferSize];
	while(1)
	{
		scanf("%s", buffer);
		
		int iret;
		if(iret = send(sockFd, buffer, bufferSize, 0) <= 0)
		{
			perror("send");
			break;
		}
		printf("客户端:iret = %d, 发送:%s\n", iret, buffer);
		if(strcmp(buffer, "bye") == 0)
		{
			break;
		}
		
		memset(buffer, 0, bufferSize);
		if(iret = recv(sockFd, buffer, bufferSize, 0) <=0)
		{
			perror("recv");
			break;
		}
		printf("服务端:iret = %d, 收到:%s\n", iret, buffer);
	}
	
	close(sockFd);
	
	return 0;
}
