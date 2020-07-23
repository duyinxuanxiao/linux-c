#include "seversocket.h"

int main(int argc, char *argv[])
{
	printf("这是主程序PID = %d\n", getpid());
    CSeverSocket socket;

    

    while( 1 )
    {
        socket.Accept();
        int forkId = fork();
        if(forkId > 0)
        {
            printf("Accept了多少个socket = %d\n", socket.GetClientCount());
        }
        else
        {
            printf("在子进程中PID = %d, forkId = %d\n", getpid(), forkId);

            printf("client:");
            socket.PrintClientAddr();
            printf("\n");

            printf("sever:");
            socket.PrintSeverAddr();
            printf("\n");
            socket.CloseSocket();
            int len = 1024;
            char recvBuffer[len];
            char sendBuffer[len] = "OK\n";
            while(1)
            {
                if(socket.Recv(recvBuffer, len) > 0)
                {
                    printf("接收成功!\n");
                    printf("收到:%s\n", recvBuffer);
                }
                else
                {
                    printf("接收失败!\n");
                    break;
                }
                sleep(1);
                
                if(socket.Send(sendBuffer, len) > 0)
                {
                    printf("发送成功!\n");
                }
                else
                {
                    printf("发送失败!\n");
                    break;
                }
                
            }
            return 0;
        }
        
    }

    
    return 0;
}
