#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int WriteToTempfile(char *buffer, size_t lenth);
char* ReadFromTempfile(int fd, size_t *lenth);

int main(int argc, char *argv[])
{
	char buffer[] = "abcdefghiasdlf'\n'jopqweiflskd'\n'fjl;asdfjal;skdfjlksdjfl;aksjfl000000ooooo\n";
	
	//把文件写入临时文件,得到问价描述符
	int fd = WriteToTempfile(buffer, strlen(buffer));
	printf("strlen(buffer) = %ld\n", strlen(buffer));
	
	//从临时文件读取数据
	size_t lenth;
	char *readBuffer = ReadFromTempfile(fd, &lenth);
	printf("lenth = %ld\n", lenth);
	
/*	char line[100];*/
/*	while(fgets(line, 100, readBuffer) != NULL)*/
/*	{*/
/*		printf("%s", line);*/
/*	}*/
/*	free(readBuffer);*/
	
	printf("%s", readBuffer);
	return 0;
}

int WriteToTempfile(char *buffer, size_t lenth)
{
	//创建临时文件名
	char fileName[] = "tmpXXXXXX";
	int fd = mkstemp(fileName);
	
	if(fd == -1)
	{
		printf("创建临时文件名出错!\n");
		exit(1);
	}
	//取消文件链接,不显示文件名;关闭文件描述符后,文件被删除
	unlink(fileName);
	//写入文件大小
	write(fd, &lenth, sizeof(lenth));
	//写入文件
	write(fd, buffer, lenth);
	
	//返回文件描述符
	return fd;
}

//fd文件描述符, lenth带回文件长度
char* ReadFromTempfile(int fd, size_t *lenth)
{
	//重新定位文件描述符的偏移量
	lseek(fd, 0, SEEK_SET);
	//读取文件长度
	read(fd, lenth, sizeof(*lenth));
	//申请文件内存
	char *buffer = (char *)malloc(sizeof(char) * (*lenth));
	//读取文件
	read(fd, buffer, *lenth);
	
	close(fd);
	
	return buffer;
	
}






