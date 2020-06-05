#ifndef _DYARRAY_H_
#define _DYARRAY_H_


class CDyArray
{
	public:
		//默认构造函数，默认容量是5
		CDyArray(int capacity = 5);
		//用一个数组初始构造，array：数组名capacity:容量count:内含数据数
		CDyArray(int array[], int capacity, int count);
		//复制构造函数
		CDyArray(const CDyArray &tmp);
		//析构函数
		~CDyArray(void);
		//返回容量
		unsigned int GetCapacity(void);
		//返回有多少数据
		unsigned int GetCount(void);
		//往末尾添加
		void Append(const int number);
		//清空数据
		void Clear(void);
		//删除指定数据
		bool Delete(const int number);
		//得到指定下标上的元素
		int GetValue(const unsigned int index);
		//查找数据，有返回下标，没有返回-1
		int Search(const int number);
		//遍历输出数组
		void Ergodic(void);
		
	private:
		int *m_array;
		unsigned int m_capacity, m_count;
};


#endif



