#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include <iostream>



class CRational
{
	public:
		CRational(int num = 0, int den = 1): m_num(num), m_den(den)
		{ 
			if(m_den == 0)
		 	{
		 		std::cout << "分母为0！\n"; 
		 		exit(1);
		 	}
		}
		CRational(const CRational &a): m_num(a.m_num), m_den(a.m_den){ }
		~CRational(){};
		
		void Simplify();                                                //化简
		void Display()const;                                            //显示
		
		
		//输入输出操作符重载
		friend std::ostream & operator << (std::ostream &os, const CRational &a);
		friend std::istream & operator >> (std::istream &is, CRational &a);
		
		
		
		//自增自减运算符
		CRational & operator ++ ();                                      //前置自增
		CRational   operator ++ (int);                                   //后置自增
		CRational & operator -- ();                                      //前置自减
		CRational   operator -- (int);                                   //后置自减
			   
		 //赋值运算符      
		CRational & operator =  (const CRational &a);
		CRational & operator += (const CRational &a);
		CRational & operator -= (const CRational &a);
		CRational & operator *= (const CRational &a);
		CRational & operator /= (const CRational &a);
			  
		//四则运算符
		friend CRational operator +  (const CRational &a, const CRational &b);
		friend CRational operator -  (const CRational &a, const CRational &b);
		friend CRational operator *  (const CRational &a, const CRational &b);
		friend CRational operator /  (const CRational &a, const CRational &b);
		
		
		//关系运算符
		friend bool operator <  (const CRational &a, const CRational &b);
		friend bool operator >  (const CRational &a, const CRational &b);
		friend bool operator == (const CRational &a, const CRational &b);
		friend bool operator != (const CRational &a, const CRational &b);
		friend bool operator <= (const CRational &a, const CRational &b);
		friend bool operator >= (const CRational &a, const CRational &b);
		
		
		//逻辑操作符
		friend bool operator && (const CRational &a, const CRational &b);
		friend bool operator || (const CRational &a, const CRational &b);
		       bool operator !  ();
		
	
	
	
    private:
        int  m_num, m_den;   //分子，分母
};

unsigned int Gcd(int a, int b);
unsigned int Mcm(int a, int b);

#endif

