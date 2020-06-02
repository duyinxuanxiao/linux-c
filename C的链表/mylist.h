#ifndef _MYLIST_H_
#define _MYLIST_H_

//链表结构体指针类型
typedef struct LIST * PLIST;

//抽象数据类型
typedef void *ADT;
typedef const void *CADT;

//以下三个为回调函数
typedef int(* COMPARE_OBJECT)(CADT a, CADT b);
typedef void(* DESTROY_OBJECT)(ADT a);
typedef void(* MANIPULATE_OBJECT)(ADT, ADT a);

//创建链表
PLIST LICreate();

//删除链表
void LIDstroy(PLIST list, DESTROY_OBJECT destroy);

//向链表尾添加元素
void LIAppend(PLIST list, ADT object);

//向指定位置插入
void LIInsert(PLIST list, ADT object, unsigned int post);

//删除指定位置元素
void LIDelete(PLIST list, unsigned int post, DESTROY_OBJECT destroy);

//清空链表
void LIClear(PLIST list, DESTROY_OBJECT destroy);

//查找指定元素，有返回节点下标，没有返回NULL
PLIST LISearch(PLIST list, ADT object, COMPARE_OBJECT compare);

//链表节点数
unsigned int LIGetCount(PLIST list);

//链表是否为空
bool LIIsEmpty(PLIST list);

//遍历链表
void LITraverse(PLIST list, MANIPULATE_OBJECT manipulate, ADT tag);


#endif
