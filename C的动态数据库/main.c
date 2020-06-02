#include <stdio.h>
#include "dynarray.h"

#define MYDEBUG

#define LOOP(a) printf("Capacity = %d,Count = %d\n", DiCapacity(a), DiGetCount(a));\
for(int i = 0; i < DiGetCount(a); i++)printf("%d ",DiGetNumber(a, i));\
printf("\n*******************************************************\n");

int main(void)
{
	PDYNINTS array = DiCreate();
	
	#ifdef MYDEBUG
	LOOP(array)
	#endif
	
	int j;
	for(j = 0; j < 10; j++)
	{
		DiAppend(array, j);
	}
	
	#ifdef MYDEBUG
	LOOP(array)
	#endif
	
	DiDelete(array, 4);
	
	#ifdef MYDEBUG
	LOOP(array)
	#endif
	
	printf("6的下标是：%d", DiSearch(array, 6));
	
	#ifdef MYDEBUG
	LOOP(array)
	#endif
	
	
	for(j = 10; j < 1000; j++)
	{
		DiAppend(array, j);
	}
	
	#ifdef MYDEBUG
	LOOP(array)
	#endif
	
	DiClear(array);
	
	#ifdef MYDEBUG
	LOOP(array)
	#endif
	
	DiDestroy(array);
	return 0;
}
