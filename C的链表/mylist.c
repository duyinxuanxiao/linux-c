#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "mylist.h"

typedef struct NODE * PNODE;
struct NODE{
	PNODE next;
	ADT object;
};

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
	//创建原始表头节点，使head,tail同时指向它
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

//向指定位置插入,0代表头节点前,l代表头结点后
void LIInsert(PLIST list, ADT object, unsigned int post)
{
	if(list == NULL)
	{
		printf("链表指针为空，无法向指定点添加元素！\n");
		exit(1);
	}
	if(post > list->count)
	{
		printf("post超过链表长度，插入失败，请用LIAppend()向表尾插入！\n");
		exit(1);
	}
	//插入到尾节点
	if(post == list->count)
	{
		LIAppend(list, object);
		return;
	}
	PNODE node = (PNODE)malloc(sizeof(struct NODE));
	if(node == NULL)
	{
		printf("向指定点插入失败！\n");
		exit(1);
	}
	node->object = object;
	
	//找到待插入节点,以原始的head节点为第0个节点
	int i = 0;
	PNODE p = list->head;
	while(i < post)
	{
		p = p->next;
		i++;
	}
	node->next = p->next;
	p->next = node;
	list->count++;
	return;
}	


//删除指定位置元素,1代表表头第一个元素，list->count为表尾节点
void LIDelete(PLIST list, unsigned int post, DESTROY_OBJECT destroy)
{
	if(list == NULL)
	{
		printf("链表指针为空，无法删除指定点添加元素！\n");
		exit(1);
	}
	if(post > list->count || post == 0)
	{
		printf("post超过链表长度，删除失败,无意义！\n");
		exit(1);
	}
	
	//找到待删除节点的上一个节点
	int i = 0;
	PNODE p = list->head;
	while(i < post-1)
	{
		p = p->next;
		i++;
	}
	//如果要删除的是表为节点则需要更新表尾
	if(p->next == list->tail)
	{
		list->tail = p;
	}
	PNODE t = p->next;
	p->next = p->next->next;
	list->count--;
	
	(*destroy)(t->object);
	free(t);
	return;
}

//清空链表
void LIClear(PLIST list, DESTROY_OBJECT destroy)
{
	if(list == NULL)
	{
		printf("链表指针为空，无法清空链表！\n");
		exit(1);
	}
	PNODE p = list->head->next;
	while(p)
	{
		PNODE t = p;
		p = p->next;
		(*destroy)(t->object);
		free(t);
	}
	list->head->next = NULL;
	list->tail = list->head;
	list->count = 0;
	return;
}

//查找指定元素，有返回节点下标，没有返回NULL,compare()返回值应为-1,0,1，分别代表<,=,>
PNODE LISearch(PLIST list, ADT object, COMPARE_OBJECT compare)
{
	if(list == NULL)
	{
		printf("链表指针为空，无法清空链表！\n");
		exit(1);
	}
	PNODE p = list->head->next;
	while(p)
	{
		if((*compare)(p->object, object) == 0)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}

//链表节点数
unsigned int LIGetCount(PLIST list)
{
	if(list == NULL)
	{
		printf("链表指针为空，无法获得节点数！\n");
		exit(1);
	}
//	printf("list->head = %p, list->head->next= %p,list->tail = %p\n", list->head, list->head->next, list->tail);
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
void LITraverse(PLIST list, MANIPULATE_OBJECT manipulate, ADT tag)
{
	if(list == NULL)
	{
		printf("链表指针为空，无法b遍历链表！\n");
		exit(1);
	}
	PNODE p = list->head->next;
	while(p)
	{
		(*manipulate)(p->object, tag);
		p = p->next;
	}
	return;
}



