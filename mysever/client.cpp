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
	
	if(connect(sockFd, (struct sockaddr*)&severAddr, sizeof(severAddr)) != 0)
	{
		perror("connect");
		close(sockFd);
		exit(-1);
	}
	
	int bufferSize = 1024;
	char buffer[bufferSize];
	for(int i = 0; i < 5; i++)
	{
		memset(buffer, 0, bufferSize);
		sprintf(buffer, "这是第%d条消息!\n", i+1);
		int iret;
		if(iret = send(sockFd, buffer, bufferSize, 0) <= 0)
		{
			perror("send");
			break;
		}
		printf("iret = %d, 发送:%s\n", iret, buffer);
		
		memset(buffer, 0, bufferSize);
		if(iret = recv(sockFd, buffer, bufferSize, 0) <=0)
		{
			perror("recv");
			break;
		}
		printf("iret = %d, 收到:%s\n", iret, buffer);
	}
	
	close(sockFd);
	
	return 0;
}
