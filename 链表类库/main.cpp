#include <iostream>
#include "mylist.h"


void MyPrint(ADT a, ADT tag)
{
	std::cout << *((int *)a) << *((char*)tag);
	return;
}

void MyDestory(ADT a)
{
	if(a != nullptr)
	{
		delete ((int *)a);
	}
}

int MyCompare(ADT a, ADT b)
{
	if(*((int *)a) == *((int *)b))
	{
		return 0;
	}
	else if(*((int *)a) < *((int *)b))
	{
		return -1;
	}
	else
	{
		return 1;
	}
}


int main(void)
{
	CMyList list;
	std::cout << "没有操作,现在有：" << list.GetCount() << "元素" << std::endl;
	
	int i;
	int *tmp;
	char tag[] = "  ";
	
	for(i = 0; i < 10; i++)
	{
		tmp = new int(i);
		if(i < 5)
		{
			list.Apphead(tmp);
		}
		else
		{
			list.Append(tmp);
		}
	}
	std::cout << "插入10个数现在有：" << list.GetCount() << "元素" << std::endl;
	list.Traverse(MyPrint, tag);
	std::cout << std::endl;
	
	int b = 9;
	list.DeleteElement(&b, MyCompare, MyDestory);
	std::cout << "删除掉9现在有：" << list.GetCount() << "元素" << std::endl;
	list.Traverse(MyPrint, tag);
	std::cout << std::endl;
	
	b = 4;
	list.DeleteElement(&b, MyCompare, MyDestory);
	std::cout << "删除掉4现在有：" << list.GetCount() << "元素" << std::endl;
	list.Traverse(MyPrint, tag);
	std::cout << std::endl;
	
	
	
	for(i = 0; i < 10; i++)
	{
		tmp = new int(i);
		if(i > 5)
		{
			list.Apphead(tmp);
		}
		else
		{
			list.Append(tmp);
		}
	}
	std::cout << "再插入10个数现在有：" << list.GetCount() << "元素" << std::endl;
	list.Traverse(MyPrint, tag);
	std::cout << std::endl;
	
	
	list.DeletePosition(1, MyDestory);
	std::cout << "删除掉第一个,现在有：" << list.GetCount() << "元素" << std::endl;
	list.Traverse(MyPrint, tag);
	std::cout << std::endl;
	
	list.DeletePosition(list.GetCount(), MyDestory);
	std::cout << "删除掉最后一个,现在有：" << list.GetCount() << "元素" << std::endl;
	list.Traverse(MyPrint, tag);
	std::cout << std::endl;
	
	list.Clear(MyDestory);
	
	return 0;
}
