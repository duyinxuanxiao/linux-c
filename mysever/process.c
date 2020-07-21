#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>


int main(int argc, char *argv[])
{
	printf("这个进程的进程号是:%d\n", getpid());
	
	if(fork() > 0)
	{
		printf("父进程的PID = %d, PPID = %d\n", getpid(), getppid());
		sleep(20);
		
		return 0;
	}
	else
	{
		printf("子进程的PID = %d, PPID = %d\n", getpid(), getppid());
		sleep(20);
		
		return 0;
	}
	
}
