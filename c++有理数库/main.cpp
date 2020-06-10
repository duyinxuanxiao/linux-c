#include <iostream>
#include "rational.h"

#define PRINT(a) std::cout << #a << " = " << a << std::endl;


int main(void)
{
	CRational a, b;
	std::cout << "a = ";
	std::cin >> a;
	std::cout << "b = ";
	std::cin >> b;
	
	PRINT(a+b);
	
	PRINT(a-b);
	
	PRINT(a*b);
	
	PRINT(a/b);
	return 0;
}
