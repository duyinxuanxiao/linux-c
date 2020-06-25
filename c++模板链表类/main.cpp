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

	list.PrintList();

	return 0;
}
