#ifndef _MYLIST_H_
#define _MYLIST_H_
template <typename T> class CList;

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
    CList() : m_count(0){m_head = new CNode<T>; m_tail = m_head;}
    CList(CList<T> &that);
    ~CList();

    void Clear();
    void Delete(const T &data);
    void DeletePosition(const unsigned int position);
    void Insert(const T &data, const unsigned int  position);
    void EmplaceBack(const T &data);
    void EmplaceFront(const T &data);
    void PrintList();



    private:
    unsigned int m_count;
    CNode<T> *m_head, *m_tail;
};





#endif