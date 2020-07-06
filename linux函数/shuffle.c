#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void Shuffle(int *array, int capacity);

int main(int argc, char *argv[])
{
	int capacity;
	do{
		printf("请问需要多少随机数:");
		scanf("%d", &capacity);
	}while(capacity <= 0 || capacity >100);
	

	int array[capacity];
	Shuffle(array, capacity);
	
	//验证是否有所有随机数
	bool judge[capacity];
	for(int j = 0; j < capacity; j++)
	{
		judge[j] = false;
	}
	for(int j = 0; j < capacity; j++)
	{
		judge[array[j]] = true;
	}
	bool isWin = true;
	for(int j = 0; j < capacity; j++)
	{
		if(!judge[j])
		{
			isWin = false;
		}
	}
	if(isWin)
	{
		printf("所有的数都存在\n");
	}
	else
	{
		printf("失败了\n");
	}
	//验证结束
	
	
	for(int i = 0; i < capacity; i++)
	{
		if(i % 5 == 0)
		{
			printf("\n");
		}
		else
		{
			printf(" ");
		}
		printf("%d", array[i]);
	}
	printf("\n");
	
	return 0;
}

void Shuffle(int *array, int capacity)
{
	int i;
	for(i= 0; i < capacity; i++)
	{
		array[i] = i;
	}
	
	int fd = open("/dev/urandom", O_RDONLY);
	int index, tmp, myError;
	unsigned long number;
	for(int cont = capacity; cont > 1; cont--)
	{
		myError = read(fd, &number, sizeof(unsigned long));
		if(myError == -1)
		{
			printf("打开随机数设备失败!\n");
			exit(1);
		}
		index = number % cont;
		
		tmp = array[cont-1];
		array[cont-1] = array[index];
		array[index] = tmp;
	}
	close(fd);
	return;
}
