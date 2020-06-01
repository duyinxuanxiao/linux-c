#ifndef _DYNARRAY_H_
#define _DYNARRAY_H_

typedef struct DYNINTS* PDYNINTS;

//创建动态数组
PDYNINTS DiCreate(void);

//销毁动态数组
void DiDestroy(PDYNINTS dyArray);

//清空动态数组
void DiClear(const PDYNINTS dyArray);

//数组有多少元素
unsigned DiGetCount(const PDYNINTS dyArray);

//数组的容量
unsigned DiCapacity(const PDYNINTS dyArray);

//吧元素追加末尾
void DiAppend(const PDYNINTS dyArray, const int number);

//删除指定元素
void DiDelete(const PDYNINTS dyArray, const int number);

//查找指定元素
int DiSearch(const PDYNINTS dyArray, const int number);

//返回指定下标的元素
int DiGetNumber(const PDYNINTS dyArray, const unsigned int index);

#endif
