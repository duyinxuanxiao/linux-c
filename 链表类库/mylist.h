#ifndef _MYLIST_H_
#define _MYLIST_H_

typedef void * ADT;

typedef int(* COMPARE_OBJECT)(ADT e1, ADT e2);
typedef void(* DESTROY_OBJECT)(ADT a);
typedef void(* MANIPULATE_OBJECT)(ADT a, ADT tag);

/*typedef struct List *PList;*/
typedef struct Node *PNode;

class CMyList
{
	public:
		CMyList();
		~CMyList();
		
		//往表尾添加元素
		void Append(ADT element);
		//往表头添加
		void Apphead(ADT element);
		//指定位置插入0代表头，链表长度代表尾
		void Insert(ADT element, const unsigned int position);
		//是否为空
		bool IsEmpty(void);
		//有多少元素
		unsigned int GetCount() const { return m_count;}
		
		//删除指定元素
		void DeleteElement(ADT element, COMPARE_OBJECT compare, DESTROY_OBJECT destroy);
		//删除指定位置元素1~m_count
		void DeletePosition(const unsigned int position, DESTROY_OBJECT destroy);
		//清空链表
		void Clear(DESTROY_OBJECT destroy);
		//遍历链表并用所提供的函数处理数据
		void Traverse(MANIPULATE_OBJECT manipulate, ADT tag);
	private:
		PNode m_head, m_tail;
		unsigned int m_count;
};


#endif
