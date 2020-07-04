#include <cstdio>
#include <getopt.h>
#include <iostream>

using namespace std;

extern char *optarg;				//当前选项参数字符串
extern int optind, opterr, optopt;
//optind——argv的当前索引值。当getopt()在while循环中使用时，循环结束后，剩下的字串视为操作数，在argv[optind]至argv[argc-1]中可以找到。
//opterr——这个变量非零时，getopt()函数为“无效选项”和“缺少参数选项，并输出其错误信息。0时函数不输出错误信息
//optopt——当发现无效选项字符之时，getopt()函数或返回'?'字符，或返回':'字符，并且optopt包含了所发现的无效选项字符。

void Help(void)
{
	printf("现在运行的程序是fac,参数为:\n");
	printf("-h or --help : 帮助文件\n");
	printf("-o or --output : 输出文件,后跟文件名\n");
	printf("-v or --verbose : 复杂信息\n");
}

int main(int argc, char *argv[])
{
	//optstring:短选项拼接的字符串
	const char * shortOptions = "ho:v";
	
	//长选项结构体
	
//	struct option 
//	{  
//		 const char *name;  长选项名称
//		 int      has_arg;  是否有可选参数0:没有,1:必须有,2:可选
//		 int        *flag;  NULL时函数返回val值,非NULL时函数返回0,flag指向val
//		 int          val;  函数找到改选项的返回值
//	}; 
	const struct option longOptions[] = 
	{
		{"help", 0, NULL, 'h'},
		{"output", 1, NULL, 'o'},
		{"verbose", 0, NULL, 'v'},
		{NULL, 0, NULL, 0}
	};
	
	char *fileName = NULL;
	int longIndex = -1;      //如果输入参数为长参数,记录找到元素在结构体数组中的下标
	int shortOpt = getopt_long(argc, argv, shortOptions, longOptions, &longIndex);
	
	while(shortOpt != -1)
	{
		switch (shortOpt)
		{
			case 'h': Help();                          break;
			case 'o': printf("输出文件:%s\n", optarg); break;
			case 'v': printf("输出复杂信息.\n");       break;
			case '?': printf("输入命令错误!\n");       break;
			default : exit(1);                         break;
		}
		
		printf("optind = %d, opterr = %d, optopt = %d\n", optind, opterr, optopt);
		if(shortOpt != '?')
		{
			printf("longOptions[longIndex].name = %s\n", longOptions[longIndex].name);
			cout << "longOptions[longIndex].name = " << longOptions[longIndex].name << endl;
		}
		
		shortOpt = getopt_long(argc, argv, shortOptions, longOptions, &longIndex);
	}
	
	return 0;
}
