#include<stdio.h>

void GetInfo(const char *infoName);

int main(int argc, char *argv[])
{
	printf("请输入需要查询的信息,格式(/proc/name):");
	char infoName[50];
	scanf("%s", infoName);
	
	GetInfo(infoName);
	
	return 0;
}

void GetInfo(const char *infoName)
{
	if(infoName == NULL)
	{
		printf("输入信息错误!\n");
		return;
	}
	
	FILE *fp = fopen(infoName, "r");
	if(fp == NULL)
	{
		printf("输入信息错误!\n");
		return;
	}
	char buffer[100];
	while(fgets(buffer, sizeof(buffer), fp))
	{
		printf("%s", buffer);
	}
	fclose(fp);
	
	return;
}
