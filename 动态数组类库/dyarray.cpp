#include <cstdlib>
#include <iostream>
#include "dyarray.h"

#define MALLOC_ERROR(pointer)  if(pointer == NULL) {std::cout<<"内存分配失败！文件是："<<__FILE__<<"行号是："<<__LINE__<<std::endl; exit(1);} 


CDyArray::CDyArray(int capacity):
	m_capacity(capacity), m_count(0)
{
	m_array = (int *)malloc(sizeof(int) * capacity);
	MALLOC_ERROR(m_array);
}



CDyArray::CDyArray(int array[], int capacity, int count):
	m_capacity(capacity), m_count(count)
{
	MALLOC_ERROR(array);
	m_array = (int *)malloc(sizeof(int) * m_capacity);
	MALLOC_ERROR(m_array);
	
	for(int i = 0; i < count; i++)
	{
		m_array[i] = array[i];
	}
}



CDyArray::CDyArray(const CDyArray &tmp):
	m_capacity(tmp.m_capacity), m_count(tmp.m_count)
{
	m_array = (int *)malloc(sizeof(int) * m_capacity);
	MALLOC_ERROR(m_array);
	
	for(int i = 0; i < m_count; i++)
	{
		m_array[i] = tmp.m_array[i];
	}
}


CDyArray::~CDyArray(void)
{
	if(m_array)
	{
		free(m_array);
	}
}


unsigned int CDyArray::GetCapacity(void)
{
	return m_capacity;
}


unsigned int CDyArray::GetCount(void)
{
	return m_count;
}


void CDyArray::Append(const int number)
{
	if(m_count == m_capacity)
	{
		int *p = (int *)realloc(m_array, sizeof(int) * m_capacity * 2);
		MALLOC_ERROR(p);
		std::cout << "重新分配内存" << std::endl;
		m_array = p;
		m_capacity *= 2;
	}
	
	m_array[m_count] = number;
	m_count++;
}
		
void CDyArray::Clear(void)
{
	m_count = 0;
}

bool CDyArray::Delete(const int number)
{
	int i = Search(number);
	if(i != -1)
	{
		for(i ; i+1 < m_count; i++)
		{
			m_array[i] = m_array[i+1];
		}
		m_count--;
		return true;
	}
	else
	{
		return false;
	}
}

int CDyArray::GetValue(const unsigned int index)
{
	if(index < m_count)
	{
		return m_array[index];
	}
	else
	{
		std::cout << "所要找的下标不存在！";
		exit(1);
	}
}

int CDyArray::Search(const int number)
{
	for(int i = 0; i < m_count; i++)
	{
		if(m_array[i] == number)
		{
			return i;
		}
	}
	
	return -1;
}


void CDyArray::Ergodic(void)
{
	for(int i = 0; i < m_count; i++)
	{
		std::cout << m_array[i];
		if(i == m_count)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << ' ';
		}
	}
}


