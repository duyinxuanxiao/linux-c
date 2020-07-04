#include <stdio.h>

extern char **environ;  //存储环境bianliang
/*在unistd.h中声明environ的地方使用了条件编译，*/
/*编译的条件就是#ifdef __USE_GNU，LinuxC中默认没有定义这个宏，*/
/*所以要在#include <unistd.h>之前加上#define __USE_GNU*/


/*
char * getenv(char *envar);

envar : 环境变量, 
功 能: 从环境中取字符串,获取环境变量的值
头文件: stdlib.h
*/

int main(int argc, char *argv[])
{
	char **var = environ;
	
	while(*var != NULL)
	{
		printf("%s\n", *var);
		var++;
	}
	
	return 0;
}
