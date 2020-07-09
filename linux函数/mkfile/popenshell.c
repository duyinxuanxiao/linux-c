#include <stdio.h>
#include "popenshell.h"

void PrintShell(const char *shellNmae)
{
	FILE *fp = popen(shellNmae, "r");
	
	if(fp == NULL)
	{
		printf("打开%s失败!\n", shellNmae);
		return;
	}
	
	char buffer[1000];
	while(fgets(buffer, 1000, fp) != NULL)
	{
		printf("%s", buffer);
	}
	
	pclose(fp);
	
	return;
}
