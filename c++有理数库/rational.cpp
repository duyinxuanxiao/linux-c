#include <iostream>
#include "rational.h"

//最大公约数
unsigned int 
Gcd(int a, int b)
{
	if(a == 0 || b == 0){ return 1; }
	
	a = abs(a);
	b = abs(b);
	
	while(a % b)
	{
		unsigned int tmp = a % b;
		a = b;
		b = tmp;
	}
	return b;
}


//最小公倍数
unsigned int 
Mcm(int a, int b)
{
	a = abs(a);
	b = abs(b);
	unsigned int t = Gcd(a, b);
	return abs( (a/t) * (b/t) * t);
}


void 
CRational::Simplify()
{
	int tmp = Gcd(m_num, m_den);
	
	m_num /= tmp;
	m_den /= tmp;
	
	if(m_den < 0) 
	{
		m_den = -m_den;
		m_num = -m_num;
	}
	return;
}


void 
CRational::Display()const
{
	std::cout << m_num <<'/' << m_den;
	return;
}



//输入输出操作符重载,友元函数
std::ostream & 
operator << (std::ostream &os, const CRational &a)
{
	if(a.m_num % a.m_den == 0)
	{
		os << a.m_num / a.m_den;
	}
	else
	{
		os << a.m_num << '/' << a.m_den;
	}
	return os;
}

std::istream & 
operator >> (std::istream &is, CRational &a)
{
    char skip;    //跳过中间的"/"字符
    is >> a.m_num >> skip >> a.m_den;
    while(skip != '/' || a.m_den == 0)
    {
    	std::cout << "输入不合法，请重新输入：\n";
    	is >> a.m_num >> skip >> a.m_den;
    }
    return is;
}



//自增自减运算符
CRational & 
CRational::operator ++ ()                                       //前置自增
{
    this->m_num += this->m_den;
    return *this;
}
CRational   
CRational::operator ++ (int)                                    //后置自增
{
	CRational tmp(*this);
	this->m_num += this->m_den;
	return tmp;
}
CRational & 
CRational::operator -- ()                                       //前置自减
{
	this->m_num -= this->m_den;
    return *this;
}
CRational   
CRational::operator -- (int)                                    //后置自减
{
	CRational tmp(*this);
	this->m_num -= this->m_den;
	return tmp;
}



 //赋值运算符      
CRational & 
CRational::operator =  (const CRational &a)
{
	this->m_num = a.m_num;
	this->m_den = a.m_den;
	return *this;
}

CRational & 
CRational::operator += (const CRational &a)
{
	this->m_den =  Mcm(a.m_den, this->m_den);
	this->m_num = (this->m_den / this->m_den) * this->m_num + (this->m_den / a.m_den) * a.m_num;
	
	return *this;
}

CRational & 
CRational::operator -= (const CRational &a)
{
	this->m_den =  Mcm(a.m_den, this->m_den);
	this->m_num = (this->m_den / this->m_den) * this->m_num - (this->m_den / a.m_den) * a.m_num;
	
	return *this;
}

CRational & 
CRational::operator *= (const CRational &a)
{
	this->m_num *= a.m_num;
	this->m_den *= a.m_den;
	
	return *this;
}

CRational & 
CRational::operator /= (const CRational &a)
{
	if(a.m_num == 0)
	{
		std::cout << "出错了，除数为0！" << std::endl;
		exit(1);
	}
	
	this->m_num *= a.m_den;
	this->m_den *= a.m_num;
	
	return *this;
}

      
//四则运算符,友元函数
CRational 
operator +  (const CRational &a, const CRational &b)
{
	int mcm = Mcm(a.m_den, b.m_den);

	CRational tmp((mcm/a.m_den)*a.m_num + (mcm/b.m_den)*b.m_num, mcm);
	tmp.Simplify();
	
	return tmp;
}


CRational 
operator -  (const CRational &a, const CRational &b)
{
	int mcm = Mcm(a.m_den, b.m_den);

	CRational tmp((mcm/a.m_den)*a.m_num - (mcm/b.m_den)*b.m_num, mcm);
	tmp.Simplify();
	
	return tmp;
}


CRational 
operator *  (const CRational &a, const CRational &b)
{
	CRational tmp(a.m_num * b.m_num, a.m_den * b.m_den);
	tmp.Simplify();
	
	return tmp;
}


CRational 
operator /  (const CRational &a, const CRational &b)
{
	if(b.m_num == 0)
	{
		std::cout << "出错了，除数为0！" << std::endl;
		exit(1);
	}
	else
	{
		CRational tmp(a.m_num * b.m_den, a.m_den * b.m_num);
		tmp.Simplify();
	
		return tmp;
	}
}



//关系运算符，友元函数
bool 
operator <  (const CRational &a, const CRational &b)
{
	int mcm = Mcm(a.m_den, b.m_den);
	
	return (mcm / a.m_den * a.m_num  <  mcm / b.m_den * b.m_num);
}

bool 
operator >  (const CRational &a, const CRational &b)
{
	int mcm = Mcm(a.m_den, b.m_den);
	
	return (mcm / a.m_den * a.m_num  >  mcm / b.m_den * b.m_num);
}

bool 
operator == (const CRational &a, const CRational &b)
{
	int mcm = Mcm(a.m_den, b.m_den);
	
	return (mcm / a.m_den * a.m_num  ==  mcm / b.m_den * b.m_num);
}

bool 
operator != (const CRational &a, const CRational &b)
{
	int mcm = Mcm(a.m_den, b.m_den);
	
	return (mcm / a.m_den * a.m_num  !=  mcm / b.m_den * b.m_num);
}

bool 
operator <= (const CRational &a, const CRational &b)
{
	int mcm = Mcm(a.m_den, b.m_den);
	
	return (mcm / a.m_den * a.m_num  <=  mcm / b.m_den * b.m_num);
}

bool 
operator >= (const CRational &a, const CRational &b)
{
	int mcm = Mcm(a.m_den, b.m_den);
	
	return (mcm / a.m_den * a.m_num  >=  mcm / b.m_den * b.m_num);
}




