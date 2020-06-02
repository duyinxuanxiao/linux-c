#include <stdlib>
#include <stdbool>
#include "mylist.h"

typedef struct NODE * PNODE;
tyepdef struct NODE{
	PNODE next;
	ADT object;
}NODE;

struct LIST{
	unsigned int count;
	PNODE head, tail;
};


//创建链表
PLIST LICreate()
{
	PLIST p = (PLIST)malloc(sizeof(struct LIST));
	if(p == NULL)
	{
		printf("创建链表失败！\n");
		exit(1);
	}
	p->head = (PNODE)malloc(sizeof(struct NODE));
	if(p->head == NULL)
	{
		free(p);
		printf("创建链表失败！\n");
		exit(1);
	}
	p->head->next = NULL;
	p->head->object = NULL;
	p->tail = p->head;
	p->count = 0;
	return p;
}

//删除链表
void LIDstroy(PLIST list, DESTROY_OBJECT destroy)
{
	if(list != NULL)
	{
		PNODE p = list->head;
		list->head = list->head->next;
		free(p);
		while(list->head)
		{
			p = list->head;
			list->head = list->head->next;
			(*destroy)(p->object);
			free(p);
		}
		free(list);
		return;
	}
}

//向链表尾添加元素
void LIAppend(PLIST list, ADT object)
{
	if(list == NULL)
	{
		printf("链表指针为空，无法添加元素！\n");
		exit(1);
	}
	PNODE node = (PNODE)malloc(sizeof(struct NODE));
	if(node == NULL)
	{
		printf("插入失败！\n");
		exit(1);
	}
	node->object = object;
	node->next = NULL;
	list->tail->next = node;
	list->tail = node;
	list->count++;
	return;
}

//向指定位置插入,0代表头节点
void LIInsert(PLIST list, ADT object, unsigned int post)
{
	if(list == NULL)
	{
		printf("链表指针为空，无法向指定点添加元素！\n");
		exit(1);
	}
	PNODE node = (PNODE)malloc(sizeof(struct NODE));
	if(node == NULL)
	{
		printf("向指定点插入失败！\n");
		exit(1);
	}

	int i = 0;
	PNODE p = list=>tail;
	while(i < post)
	{
		p = p->next;
	}
	node->next = p->next;
	p->next = node;
	return;
}	

//删除指定位置元素
void LIDelete(PLIST list, unsigned int post, DESTROY_OBJECT destroy)
{
	
}

//清空链表
void LIClear(PLIST list, DESTROY_OBJECT destroy);

//查找指定元素，有返回节点下标，没有返回NULL
PLIST LISearch(PLIST list, ADT object, COMPARE_OBJECT compare);

//链表节点数
unsigned int LIGetCount(PLIST list)
{
	if(list == NULL)
	{
		printf("链表指针为空，无法获得节点数！\n");
		exit(1);
	}
	return list->count;
}

//链表是否为空
bool LIIsEmpty(PLIST list)
{
	if(list == NULL)
	{
		printf("链表指针为空，无法判断！\n");
		exit(1);
	}
	if(list->count == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//遍历链表
void LITraverse(PLIST list, MANIPULATE_OBJECT manipulate, ADT tag);



