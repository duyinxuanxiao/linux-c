#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "procinfo.h"

void PrintProcInfo(const char *procName)
{
	int fd = open(procName, O_RDONLY);
	if(fd == -1)
	{
		printf("打开%s失败!\n", procName);
		return;
	}
	
	char buffer[1000];
	
	while(read(fd, buffer, 1000) != 0)
	{
		printf("%s", buffer);
	}
	close(fd);
	
	return;
}
