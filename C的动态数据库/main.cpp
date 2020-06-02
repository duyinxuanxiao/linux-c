#include <iostream>
#include "dynarray.h"

#define MYDEBUG

#define LOOP(a) std::cout << "Capacity = " << DiCapacity(a) << "Count = " << DiGetCount(a) << std::endl;\
for(int i = 0; i < DiGetCount(a); i++) std::cout << DiGetNumber(a, i) << ' '; std::cout << "*****************************************\n";

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
	
	std::cout << "6的下标是：" << DiSearch(array, 6) << std::endl;
	
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
