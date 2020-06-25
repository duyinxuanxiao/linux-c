#ifndef _MYLIST_H_
#define _MYLIST_H_

#include <iostream>
template <typename T> class CList;                  //前置声明链表类,以便声明为CNode的友元类

template <typename T>
class CNode
{
    public:
    CNode() : next(nullptr) {}
    CNode(T dt) : data(dt), next(nullptr) {}
    ~CNode() = default;

    friend class CList<T>;

    private:
    T data;
    CNode<T> *next;
};


template <typename T>
class CList
{
    public:
    CList() : m_count(0){m_head = new CNode<T>; m_tail = m_head;}	//带有一个头节点的链表
    CList(CList<T> &that);
    ~CList();
	
	unsigned int GetCount() const {return m_count;}
	bool IsEmpty() const { if(m_count == 0){return true;} else {return false;}}
    void Clear();
    void Delete(const T &data);
    void DeletePosition(const unsigned int position);
    void Insert(const T &data, const unsigned int  position);
    void EmplaceBack(const T &data);
    void EmplaceFront(const T &data);
    void PrintList() const;



    private:
    unsigned int m_count;
    CNode<T> *m_head, *m_tail;
};



template <typename T>
CList<T>::CList(CList<T> &that)
    :m_count(that.m_count)
{
    m_head = new CNode<T>;
    CNode<T> *p = that.m_head->next;
    CNode<T> *q = m_head;
    while(p != nullptr)
    {
        q->next = new CNode<T>(*p);
        q = q->next;
        p = p->next; 
    }
    m_tail = q;
}

template <typename T>
CList<T>::~CList()
{
    CNode<T> *p = m_head;
    while(p != nullptr)
    {
        CNode<T> *q = p;
        p = p->next;
        delete q;
    }
}

template <typename T>
void CList<T>::Clear()
{
    CNode<T> *p = m_head->next;
    while(p != nullptr)
    {
        CNode<T> *q = p;
        p = p->next;
        delete q;
    }
    m_head->next = nullptr;
    m_tail = m_head;
    m_count = 0;
}

template <typename T>
void CList<T>::Delete(const T &data)
{
    CNode<T> *p = m_head;
    while(p->next != nullptr)
    {
        if(p->next->data == data)
        {
            CNode<T> *q = p->next;
            if(p->next == m_tail)
            {
                m_tail = p;
            }
            p->next = p->next->next;
            delete q;
            m_count--;
            break;
        }
        p = p->next;
    }
}

template <typename T>
void CList<T>::DeletePosition(const unsigned int position)
{
    int t = 0;
    CNode<T> *p = m_head;
    while(p->next != nullptr)
    {
        if(t == position-1)
        {
            CNode<T> *q = p->next;
            if(p->next == m_tail)
            {
                m_tail = p;
            }
            p->next = p->next->next;
            delete q;
            m_count--;
            break;
        }
        p = p->next;
        t++;
    }
}

template <typename T>
void CList<T>::Insert(const T &data, const unsigned int  position)
{
    if(position == m_count)
    {
        EmplaceBack(data);
    }
    else
    {
        CNode<T> *p = m_head;
        for(int t = 0; t < m_count; t++)
        {
            if(t == position)
            {
                CNode<T> *q = new CNode<T>(data);
                q->next = p->next;
                p->next = q;
                m_count++;
                break;
            }
            p = p->next;
        }
    }
    
}

template <typename T>
void CList<T>::EmplaceBack(const T &data)
{
    m_tail->next = new CNode<T>(data);
    m_tail = m_tail->next;
    m_count++;
}

template <typename T>
void CList<T>::EmplaceFront(const T &data)
{
    CNode<T> *p = new CNode<T>(data);
    p->next = m_head->next;
    m_head->next = p;
    if(m_head == m_tail)
    {
    	m_tail = p;
    }
    m_count++;
}


template <typename T>
void CList<T>::PrintList() const
{
    CNode<T> *p = m_head->next;

    while(p != nullptr)
    {
        std::cout << p->data << ' ';
        p = p->next;
    }
}


#endif
