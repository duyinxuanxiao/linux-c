#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <csignal>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO
                               (Linux-specific) */
};

int semID;

void Sighandler_SIGCHLD(int sig)
{
	printf("收到了%d信号!\n准备释放二元信号量.\n", sig);
    semctl(semID, 0, IPC_RMID);
}

int main(int argc, char *argv[])
{
    //绑定信号处理函数
	signal(SIGCHLD, Sighandler_SIGCHLD);
	//创建二元进程信号量, IPC_PRIVATE表示为此进程组私有
	semID = semget(IPC_PRIVATE, 1 , 0604 | IPC_CREAT);
	if(semID == -1)
	{
		perror("semget");
		exit(1);
	}
    //初始化信号量
	union semun semUnion;
    semUnion.val = 1;
    if(semctl(semID, 0, SETVAL, semUnion) == -1)
    {
        perror("semctl");
        semctl(semID, 0, IPC_RMID);
        exit(1);
    }
    printf("父进程:已设置好信号灯\n");

    struct sembuf semBuffer;
    semBuffer.sem_flg = SEM_UNDO;
    semBuffer.sem_num = 0;
    semBuffer.sem_op = -1;
	
	for(int j = 0; j < 4; j ++)
    {
        if(fork() == 0)
        {
            printf("进入子进程\n");
            for(int i = 0; i < 3; i++)
            {
                //进入临界区, P : 传递
                semop(semID, &semBuffer, 1);
                printf("子进程%d:等到信号灯,开始使用\n", getpid());
                sleep(3);
                printf("子进程%d:已经使用二元信号量\n", getpid());
                //释放临界区, V : 释放
                semctl(semID, 0, SETVAL, semUnion);
                sleep(5);
            }
            return 0;
        }
    }
    for(int i = 0; i < 3; i++)
    {
        //进入临界区, P : 传递
        semop(semID, &semBuffer, 1);
        printf("父进程:等到信号灯,开始使用\n");
        sleep(3);
        printf("父进程:已经使用二元信号量\n");
        //释放临界区, V : 释放
        semctl(semID, 0, SETVAL, semUnion);
        sleep(5);
    }
    
	sleep(20);
	return 0;
}
