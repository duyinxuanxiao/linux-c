#include <stdio.h>
#include <stdlib.h>
#include "mylist.h"

void MyPrint(ADT a, ADT tag)
{
	printf((char*)tag, *((int*)a));
	return;
}

void MyDestory(ADT a)
{
	if(a != NULL)
	{
		free(a);
	}
}

int main(void)
{
	PLIST list = LICreate();
	
	for(int i = 0; i < 10; i++)
	{
		int *p = (int *)malloc(sizeof(int));
		*p = i;
		LIAppend(list, p);
	}
	
	printf("\n输出0~9,count = %d\n", LIGetCount(list));
	LITraverse(list, MyPrint, "%d ");
	printf("\n*******************************************************************\n");
	
	
	int *b = (int *)malloc(sizeof(int));
	*b = 888;
	int *c = (int *)malloc(sizeof(int));
	*c = 999;
	int *d = (int *)malloc(sizeof(int));
	*d = 666;
	
	printf("\n把888插入到表尾count = %d\n", LIGetCount(list));
	LIInsert(list, b, LIGetCount(list));
	printf("插入完成count = %d\n", LIGetCount(list));
	LITraverse(list, MyPrint, "%d ");
	printf("\n*******************************************************************\n");
	
	
	printf("\n把999插入到表头0，count = %d\n", LIGetCount(list));
	LIInsert(list, c, 0);
	printf("插入完成count = %d\n", LIGetCount(list));
	LITraverse(list, MyPrint, "%d ");
	printf("\n*******************************************************************\n");
	
	
	printf("\n把666插入到表尾-1count = %d\n", LIGetCount(list));
	LIInsert(list, d, LIGetCount(list)-1);
	printf("插入完成count = %d\n", LIGetCount(list));
	LITraverse(list, MyPrint, "%d ");
	printf("\n*******************************************************************\n");
	
	
	printf("\n运行删除第一个元素，count = %d\n", LIGetCount(list));
	LIDelete(list, 1, MyDestory);
	printf("删除完成count = %d\n", LIGetCount(list));
	LITraverse(list, MyPrint, "%d ");
	printf("\n*******************************************************************\n");
	
	
	
	printf("\n运行删除第4个元素，count = %d\n", LIGetCount(list));
	LIDelete(list, 4, MyDestory);
	printf("删除完成count = %d\n", LIGetCount(list));
	LITraverse(list, MyPrint, "%d ");
	printf("\n*******************************************************************\n");
	
	
	printf("\n运行删除最后一个元素，count = %d\n", LIGetCount(list));
	LIDelete(list, LIGetCount(list), MyDestory);
	printf("删除完成count = %d\n", LIGetCount(list));
	LITraverse(list, MyPrint, "%d ");
	printf("\n*******************************************************************\n");
	
	
	for(int i = 0; i < 10; i++)
	{
		int *p = (int *)malloc(sizeof(int));
		*p = i;
		LIAppend(list, p);
	}
	
	printf("\n输出0~9,count = %d\n", LIGetCount(list));
	LITraverse(list, MyPrint, "%d ");
	printf("\n*******************************************************************\n");
	
	LIDstroy(list, MyDestory);
	return 0;
}
