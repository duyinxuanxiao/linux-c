#include <iostream>
#include "mylist.h"

int main(void)
{
	CList<int> list;

	for(int i = 0; i < 10; i++)
	{
		if(i % 2 == 0)
		{
			list.EmplaceBack(i);
		}
		else
		{
			list.EmplaceFront(i);
		}
	}
	std::cout << "count = " << list.GetCount() << std::endl;
	list.PrintList();
	
	std::cout << "\n现在删除第1个元素后输出:" << std::endl;
	list.DeletePosition(1);
	list.PrintList();
	
	std::cout << "\n现在删除0这个数字后输出:" << std::endl;
	list.Delete(0);
	list.PrintList();
	
	std::cout << "\n现在删除第8个元素,也是最后一个,输出:" << std::endl;
	list.DeletePosition(8);
	list.PrintList();
	
	
	for(int i = 10; i < 20; i++)
	{
		if(i % 2 == 0)
		{
			list.EmplaceBack(i);
		}
		else
		{
			list.EmplaceFront(i);
		}
	}
	std::cout << "count = " << list.GetCount() << std::endl;
	list.PrintList();
	
	

	return 0;
}
