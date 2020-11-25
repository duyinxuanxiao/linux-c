#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{	
	int cont = 0;
	printf("请问需要多少随机数:");
	scanf("%d", &cont);
	
	int fd = open("/dev/random", O_RDONLY);
	unsigned long number;
	for(int i = 0; i < cont; i++)
	{
		if( read(fd, &number, sizeof(number)) )
		{
			printf("%lu\n", number);
		}
	}
	close(fd);
	
	printf("linux系统函数到此结束\n");
	
	
	unsigned long *num = malloc(sizeof(unsigned long));
	FILE *file = fopen("/dev/random", "r");
	printf("%ld\n", sizeof( unsigned long));
	for(int k = 0; k < cont; k++)
	{
		fread(num, sizeof(unsigned long), 1, file);
		printf("%lu\n", *num);
	}
	fclose(file);
	
	return 0;
}
