#include <stdio.h>
#include "procinfo.h"
#include "popenshell.h"

#define PRINT(a) (printf("调用#a"); a;)


int main(int argc, char *argv[])
{
	printf("\n******************************CPU硬件信息1:******************************************\n");
	//printf("调用:PrintProcInfo("/proc/cpuinfo")\n");
	PrintProcInfo("/proc/cpuinfo");
	printf("\n******************************CPU硬件信息2:******************************************\n");
	//printf("调用:PrintShell("lscpu")\n");;
	PrintShell("lscpu");
	
	
	printf("\n******************************内存信息:*********************************************\n");
	//PrintShell("free -m");
	PrintProcInfo("/proc/meminfo");
	
	
	printf("\n******************************系统信息:*********************************************\n");
	PrintProcInfo("/proc/version");
	
	
	
	printf("\n******************************硬盘信息:*********************************************\n");
	PrintShell("lsblk");
	
	
	
	printf("\n******************************网卡信息:*********************************************\n");
	PrintShell("lspci");
	
	
	
	printf("\n******************************网络接口信息:*****************************************\n");
	PrintShell("ip link show");
	
	
	
	printf("\n******************************主板硬件槽(pci)信息:**********************************\n");
	PrintShell("lspci");
	
	return 0;
	
}
