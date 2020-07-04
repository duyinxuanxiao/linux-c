#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd = open("dev/random", O_RDONLY);
	
	long number;
	
	int cont = 0;
	
	printf("请问需要多少随机数:");
	scanf("%d", &cont);
	
	for(int i = 0; i < cont; i++)
	{
		if( read(fd, &number, sizeof(number)) )
		{
			printf("%ld\n", number);
		}
	}
	
	close(fd);
	
	return 0;
}
