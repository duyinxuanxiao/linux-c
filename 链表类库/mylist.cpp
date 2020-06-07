#include <iostream>
#include "mylist.h"

typedef struct Node
{
	PNode next;
	ADT data;
}SNode;


CMyList::CMyList():
	m_count(0)
{
	m_head = new SNode;
	m_head->next = nullptr;
	m_head->data = nullptr;
	m_tail = m_head;
}


CMyList::~CMyList()
{
	std::cout << "执行析构函数\n";
	PNode p = m_head;
	m_head = m_head->next;
	delete p;
	while(m_head)
	{
		p = m_head;
		m_head = m_head->next;
		delete p;
	}
	
}


inline bool CMyList::IsEmpty(void)
{
	if(m_count == 0)
	{
		return true;
	}
	return false;
}


//inline unsigned int CMyList::GetCount(void)
//{
//	return m_count;
//}


void CMyList::Append(ADT element)
{
	PNode p = new SNode;
	p->next = nullptr;
	p->data = element;
	m_tail->next = p;
	m_tail = p;
	m_count++;
}


void CMyList::Apphead(ADT element)
{
	PNode p = new SNode;
	p->data = element;
	p->next = m_head->next;
	m_head->next = p;
	if(m_head == m_tail)
	{
		m_tail = p;
	}
	m_count++;
}


void CMyList::Insert(ADT element, const unsigned int position)
{
	PNode p = new SNode;
	p->data = element;
	if(position == m_count)
	{
		CMyList::Append(element);
		return;
	}
	PNode q = m_head;
	int i = 0;
	while(i < position)
	{
		q = q->next;
		i++;
	}
	p->next = q->next;
	q->next = p;
	m_count++;
}


void CMyList::DeleteElement(ADT element, COMPARE_OBJECT compare, DESTROY_OBJECT destroy)
{
	PNode p = m_head;
	while(p->next)
	{
		if((*compare)(p->next->data, element) == 0)
		{
			if(p->next == m_tail)
			{
				m_tail = p;
				
			}
			PNode tmp = p->next;
			p->next = p->next->next;
			(*destroy)(tmp->data);
			delete tmp;
			m_count--;
			break;
		}
		p = p->next;
	}
}


void CMyList::DeletePosition(const unsigned int position, DESTROY_OBJECT destroy)
{
	if(position > 0 && position <= m_count)
	{
		PNode p = m_head;
		for(int i = 0; i < position-1; i++)
		{
			p = p->next;
		}
		
		if(p->next == m_tail)
		{
			m_tail = p;
			
		}
		PNode tmp = p->next;
		p->next = p->next->next;
		(*destroy)(tmp->data);
		delete tmp;
		m_count--;
	}
}


void CMyList::Clear(DESTROY_OBJECT destroy)
{
	std::cout << "执行清除函数\n";
	PNode p = m_head->next;
	PNode t;
	while(p)
	{
		t = p;
		p = p->next;
		(*destroy)(t->data);
		delete t;
	}
	m_head->next = nullptr;
	m_tail = m_head;
	m_count = 0;
}


void CMyList::Traverse(MANIPULATE_OBJECT manipulate, ADT tag)
{
	PNode p = m_head->next;
	while(p)
	{
		(*manipulate)(p->data, tag);
		p = p->next;
	}
}
