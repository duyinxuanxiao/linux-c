#include <iostream>
#include "mylist.h"

// template <typename T>
// CList<T>::CList()

template <typename T>
CList<T>::CList(CList<T> &that)
    :m_count(that.m_count)
{
    m_head = new Node<T>;
    Node<T> *p = that.m_head->next;
    Node<T> *q = m_head;
    while(p != nullptr)
    {
        q->next = new Node<T>(*p);
        q = q->next;
        p = p->next; 
    }
    m_tail = q;
}

template <typename T>
CList<T>::~CList()
{
    Node<T> *p = m_head;
    while(p != nullptr)
    {
        delete p;
    }
}

template <typename T>
void CList<T>::Clear()
{
    Node<T> *p = m_head->next;
    while(p != nullptr)
    {
        Node<T> *q = p;
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
    Node<T> *p = m_head;
    while(p->next != nullptr)
    {
        if(p->next->data == data)
        {
            Node<T> *q = p->next;
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
    Node<T> *p = m_head;
    while(p->next != nullptr)
    {
        if(t == position)
        {
            Node<T> *q = p->next;
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
        Node<T> *p = m_head;
        for(int t = 0; t < m_count; t++)
        {
            if(t == position)
            {
                Node<T> *q = new Node<T>(data);
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
    m_tail->next = new Node<T>(data);
    m_tail = m_tail->next;
    m_count++;
}

template <typename T>
void CList<T>::EmplaceFront(const T &data)
{
    Node<T> *p = new Node<T>(data);
    p->next = m_head->next;
    m_head->next = p;
    m_count++;
}