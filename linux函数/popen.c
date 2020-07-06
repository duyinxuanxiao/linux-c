#include <stdio.h>
#include <stdlib.h>

const unsigned int READ_LINE_CAPACITY = 300;

int main(int argc, char *argv[])
{
	printf("请输入你的shell命令:");
	char command[100];
	scanf("%[^\n]", command);
	
	FILE *file = popen(command, "r");
	if(file == NULL)
	{
		printf("打开命令错误!\n");
		exit(1);
	}
	
	char line[READ_LINE_CAPACITY];
	while(fgets(line, READ_LINE_CAPACITY, file) != NULL)
	{
		printf("%s", line);
	}
	
	pclose(file);
	
	return 0;
}
