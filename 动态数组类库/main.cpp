#include <iostream>
#include "dyarray.h"

int main(void)
{
	CDyArray dyArray;
	
	std::cout << "capacity = " << dyArray.GetCapacity() << "count = " << dyArray.GetCount() << std::endl;
	
	int i;
	for(i = 0; i < 10; i++)
	{
		dyArray.Append(i);
	}
	
	dyArray.Ergodic();
	
	std::cout << "4所在的位置是：" << dyArray.Search(4) << std::endl;
	
	std::cout << "清除掉5\n";
	
	dyArray.Delete(5);
	
	dyArray.Ergodic();
	
	
	return 0;
}
