#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dynarray.h"

struct DYNINTS
{
	unsigned int capacity;    //容量
	unsigned int count;       //元素数量
	int *items;               //数组项目
//	bool modified;            //是否调整
};

//创建动态数组
PDYNINTS DiCreate(void)
{
	PDYNINTS p = (PDYNINTS)malloc(sizeof(struct DYNINTS));
	if(p == NULL)
	{
		printf("动态数组创建失败!\n");
		exit(1);
	}
	p->items = (int *)malloc(sizeof(int) * 5);
	if(p->items == NULL)
	{
		printf("动态数组创建失败!\n");
		exit(1);
	}
	p->capacity = 5;
	p->count = 0;
	p->modified = false;
	return p;
}

//销毁动态数组
void DiDestroy(PDYNINTS dyArray)
{
	if(dyArray != NULL)
	{
		if(dyArray->items != NULL)
		{
			free(dyArray->items);
		}
		free(dyArray);
	}
	else
	{
		printf("动态数组删除失败!\n");
		exit(1);
	}
}

//清空动态数组
void DiClear(const PDYNINTS dyArray)
{
	if(dyArray != NULL)
	{
		dyArray->count = 0;
	}
	else
	{
		printf("动态数组清空失败!\n");
		exit(1);
	}
}

//数组有多少元素
unsigned DiGetCount(const PDYNINTS dyArray)
{
	if(dyArray != NULL)
	{
		return dyArray->count;
	}
}

//数组的容量
unsigned DiCapacity(const PDYNINTS dyArray)
{
	if(dyArray != NULL)
	{
		return dyArray->capacity;
	}
}

//吧元素追加末尾
void DiAppend(const PDYNINTS dyArray, const int number)
{
	if(dyArray != NULL)
	{
		dyArray->items[dyArray->count] = number;
		dyArray->count++;
		if(dyArray->count == dyArray->capacity)
		{
			int *q = (int *)realloc(dyArray->items, sizeof(int) * dyArray->capacity * 2);
			if(q != NULL)
			{
				dyArray->items = q;
				dyArray->capacity *= 2;
			}
			else
			{
				printf("插入后动态数组已满，重新分配内存失败!\n");
				exit(1);
			}
		}
	}
}

//删除指定元素
void DiDelete(const PDYNINTS dyArray, const int number)
{
	if(dyArray != NULL && dyArray->items != NULL)
	{
		int i;
		for(i = 0; i < dyArray->count; i++)
		{
			if(dyArray->items[i] == number)
			{
				break;
			}
		}
		while(i + 1 < dyArray->count)
		{
			dyArray->items[i] = dyArray->items[i+1];
			i++;
		}
		dyArray->count--;
	}
}

//查找指定元素,没有返回-1
int DiSearch(const PDYNINTS dyArray, const int number)
{
	int index = -1;
	if(dyArray != NULL)
	{
		for(int i = 0; i < dyArray->count; i++)
		{
			if(dyArray->items[i] == number)
			{
				index = i;
				break;
			}
		}
	}
	return index;
}


//返回指定下标的元素
int DiGetNumber(const PDYNINTS dyArray, const unsigned int index)
{
	if(dyArray != NULL && index < dyArray->count)
	{
		return dyArray->items[index];
	}
	else
	{
		exit(1);
	}
}





